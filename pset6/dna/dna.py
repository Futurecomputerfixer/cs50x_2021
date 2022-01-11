import csv
from sys import argv, exit

# check for command-line argument
if not len(argv) == 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open up the database csv file
with open(argv[1], newline='') as f:
    reader = csv.reader(f)
    x = []
    # read the data into a list. Each row in the file 
    # is an item in that list. Each item is also a sublist
    # x is a list of lists
    for row in reader:
        x.append(row)
    
# open up the sequence we are going to examine
with open(argv[2]) as f1:
    sequence = f1.read()
    
# a list (STRR[]) containing the number of consecutive repetition for 
# each STR from the sequence. 
STRR = []
for STR in range(len(x[0]) - 1):
    # temporarily store the STR we are going to examine
    a = x[0][STR + 1]
    # set the initial number to 0 
    counts = 0
    # check the number of number of consecutive repetition for 
    # each STR from the sequence.
    for b in range(len(sequence) - len(a) + 1):
        c = b
        temp = 0
        while sequence[c:c + len(x[0][STR + 1])] == a:
            c += len(x[0][STR + 1])
            temp += 1
        if temp > counts:
            counts = temp
    # record the number in the list.        
    STRR.append(str(counts))
    
# check if there is a person in the databases has the same number of STR in that list.
for i in range(1, len(x)):
    if STRR == x[i][1:len(x[i])]:
        print(x[i][0])
        exit(0)

print("No match")
