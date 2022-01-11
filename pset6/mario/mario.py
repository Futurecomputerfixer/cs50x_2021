from cs50 import get_int

layers = get_int("Height: ")
while layers > 8 or layers < 1:
    layers = get_int("Height: ")
b = layers

for i in range(layers):
    b -= 1
    #
    print(' ' * b, end="")
    print("#" * (i + 1), end="")
    # two space in the middle
    print('  ', end='')
    print("#" * (i + 1), end="")
    print()
    