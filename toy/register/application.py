from flask import Flask, render_template, request

app = Flask(__name__)

REGISTRANTS = {}

SPORTS = [
    "Dodgeball".
    "Swimming",
    "Basketball",
    "Cross_country",
    "Golf"
]

@app.route("/")
def index():
    return render_template("index.html", sports = SPORTS)

@app.route("/register")
def register():
    if not request.form.get("name") or request.form.get("sports") in SPORTS:
        return render_template("failure.html")
    return render_template("success.html")
