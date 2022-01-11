# A List uses square brackets [];
# A Tuple uses parentheses ();
# A Dictionary uses curly brackets {};

# tuples inside a list
presidents = [
    ("George Washington", 1789),
    ("John Adams", 1797),
    ("Thomas Jefferson", 1801),
    ("James Madison", 1809)
]

for prez, year in presidents:
    print("In {}, {} took office".format(year, prez))

print("Enter two numbers to get their average: ")
form = list()
for i in range(2):
    num = int(input("Input: "))
    form.append(num)
print(sum(form) / len(form))

pizzas = {
    "Cheese": 9,
    "Pepperoni": 10,
    "Pineapple": 11,
    "Mushroom": 12
}
pizzas["Bacon"]: 15
print("Menu: ")
for name in pizzas:
    print(f"{name}: {pizzas[name]}$ ")
    
    
# python does not have a main function; if you want to use one, 
# you have to explicitly write this at the very end of your code
# if __name__ = "__main__":
#   main()
# you just have to memorize it