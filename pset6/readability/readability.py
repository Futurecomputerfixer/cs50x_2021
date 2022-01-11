from cs50 import get_string

# get text for checking 
text = get_string("Text: ")
# initiate variables
letter = 0
word = 1
sentence = 0
# iterate over each character in text
for c in text:
    # check for letters
    if c.isalpha() == True:
        letter += 1
    # check for words(for consideration of this practice problem,
    # each string seperated by space is considered as a word)
    elif c == ' ':
        word += 1
    # to the matter of this problem, every time a period/question mark/exclamation mark appears 
    elif c == '.' or c == '?' or c == '!':
        sentence += 1
# apply the algorithm 
L = letter / (word / 100)
S = sentence / (word / 100)
index = round(0.0588 * L - 0.296 * S - 15.8)
# print out the grade
if index > 15:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(index))

