from cs50 import get_int
import sys
number = get_int("Number:")
a = 0
b = 0
# convert input(integer) into a string for indexing
stred = str(number)
# apply algorithm to check
for i in range(len(stred) - 2, -1, -2):
    a = 2 * int(stred[i])
    for c in str(a):
        b += int(c)
for j in range(len(stred) - 1, -1, -2):
    b += int(stred[j])

if b % 10 != 0:
    print("INVALID")
    sys.exit(1)
# check which specifc kind of card that is
# American Express has 15 digits, beginning with 34-37
if len(stred) == 15:
    if stred[0] == '3' and 3 < int(stred[1]) < 8:
        print("AMEX")
    else: 
        print("INVALID")
        sys.exit(1)
# Some Visa has 13 digits, beginning with 4
elif len(stred) == 13:
    if stred[0] == '4':
        print("VISA")
    else:
        print("INVALID")
        sys.exit(1)
# other Visas and Mastercard have 16 digits; Mastercard begins with 51-55
elif len(stred) == 16:
    if stred[0] == '5' and 0 < int(stred[1]) < 6:
        print("MASTERCARD")
    elif stred[0] == '4':
        print("VISA")
    else:
        print("INVALID")
        sys.exit(1)
else:
    print("INVALID")
