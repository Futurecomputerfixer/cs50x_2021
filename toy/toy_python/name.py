import csv

with open('name.csv',newline='') as f:
    readername = csv.reader(f)
    x = []
    for roww in readername:
        x.append(roww)
    print(x[0][0])