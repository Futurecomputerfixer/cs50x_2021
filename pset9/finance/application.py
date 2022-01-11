# export API_KEY=pk_22b9c5a9b1cf44e888a93f4a5b90af22 
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT * FROM Stocks WHERE user_id = ?", session["user_id"])
    stockTotalValue = 0
    for row in rows:
        row["price"] = lookup(row["stock"])["price"]
        row["price_total"] = row["stock_shares"] * row["price"]
        stockTotalValue += row["price_total"]
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]['cash']
    grandTotal = cash + stockTotalValue
    if db.execute("SELECT * FROM Rankings WHERE user_id = ?", session["user_id"]):
        db.execute("UPDATE Rankings SET assets = ? WHERE user_id = ?", grandTotal, session["user_id"])
    else:
        db.execute("INSERT INTO Rankings(user_id, assets) VALUES(?, ?)", session["user_id"], grandTotal)
    return render_template("index.html", rows=rows, cash=usd(cash), grandTotal=usd(grandTotal), stockTotalValue=usd(stockTotalValue))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Show history of transactions"""
    if request.method == "POST":
        # check for errors
        Stock = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")
        if not Stock or not request.form.get("shares"):
            return apology("Stock or shares not found")
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]['cash']
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)
        if float(shares) <= 0:
            return apology("shares must be a positive integer", 400)
        Total = int(Stock["price"]) * int(shares)
        if cash < Total:
            return apology("No Enough Cash to Make Purchase")
        # process the purchase
        else:
            # update the database
            # check if they already own the stock
            current_shares = db.execute("SELECT stock_shares FROM Stocks WHERE stock = ? AND user_id=?",
                                        Stock["symbol"], session["user_id"])
            if not current_shares:
                # record the stock
                db.execute("INSERT INTO Stocks(user_id, stock, stock_name, stock_shares) VALUES(?, ?, ?, ?)",
                           session["user_id"], Stock["symbol"], Stock["name"], shares)
            else:
                # update the number of shares(the user had already own some shares)
                db.execute("UPDATE Stocks SET stock_shares = ? WHERE user_id =? AND stock=?", 
                           int(current_shares[0]["stock_shares"]) + int(shares), session["user_id"], Stock["symbol"])

            # update the cash remaining
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - Total, session["user_id"])
            # record purchase history
            db.execute("INSERT INTO history(user_id, action, price, symbol, shares)VALUES(?,?,?,?,?)", 
                       session["user_id"], "BOUGHT", Stock["price"], Stock["symbol"], shares)
            flash("BOUGHT")
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history WHERE user_id=?", session["user_id"])
    flash("HISTORY")
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("LOGGED IN")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # stock lookup
    if request.method == "POST":
        flash("STOCK LOOKUP")
        rows = lookup(request.form.get("symbol"))
        # if no stock found
        if not rows:
            return apology("STOCK NOT FOUND")
        return render_template("quoted.html", rows=rows)
    else: 
        return render_template("quote.html")


@app.route("/ranking", methods=["GET", "POST"])
def ranking():
    rows = db.execute("SELECT username, assets FROM users JOIN Rankings ON users.id = Rankings.user_id ORDER BY assets DESC")
    flash("RANKING from the richest to the poorest")
    return render_template("ranking.html", rows=rows)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # error checking

        # check if the username is blank or it already exists
        if not request.form.get("username") or db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username")):
            return apology("The username field is blank or it already exists")
        # check for the passowords fields
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("The passoword fields cannot be blank")
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("The Passwords need to be the same")

        # hash password and create new user account
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUEs(?, ?)", request.form.get("username"), hash)
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = ?", request.form.get("username"))[0]["id"]
        flash("REGISTERED")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Stock or shares not found")
        Stock = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")
        if not Stock or not shares:
            return apology("Stock or shares not found")
        user_shares = db.execute("SELECT stock_shares FROM Stocks WHERE user_id=? AND stock=?", 
                                 session["user_id"], request.form.get("symbol"))

        # check if the user has enough stock to sell
        if user_shares[0]["stock_shares"] < int(shares):
            return apology("Not enough shares to sell")
        # process the transaction
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]['cash']
        Total = int(Stock["price"]) * int(shares)

        current_shares = int(db.execute("SELECT stock_shares FROM Stocks WHERE user_id=? AND stock=?", 
                                        session["user_id"], Stock["symbol"])[0]["stock_shares"]) - int(shares)
        if not current_shares:
            # delete the row recording the stock for the user
            db.execute("DELETE FROM Stocks WHERE stock=?", Stock["symbol"])
        else:
            # update the number of shares(the user had already own some shares)
            db.execute("UPDATE Stocks SET stock_shares = ? WHERE user_id =? AND stock=?", 
                       current_shares, session["user_id"], Stock["symbol"])

        # update the cash remaining
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + Total, session["user_id"])
        # record purchase history
        db.execute("INSERT INTO history(user_id, action, price, symbol, shares)VALUES(?,?,?,?,?)", 
                   session["user_id"], "SOLD", Stock["price"], Stock["symbol"], shares)
        flash("SOLD")
        return redirect("/")
    else:
        stocks = db.execute("SELECT stock FROM Stocks WHERE user_id = ?", session["user_id"])
        rows = []
        for stock in stocks:
            rows.append(stock["stock"])
        return render_template("sell.html", rows=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

