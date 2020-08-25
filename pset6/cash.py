from cs50 import get_float

change = 0.00

while change <= 0:
    change = get_float("Change owed: ") * 100

coin = 0

while change != 0:
    if change >= 25:
        coin += 1
        change -= 25
    elif change >= 10:
        coin += 1
        change -= 10
    elif change >= 5:
        coin += 1
        change -= 5
    else:
        coin += 1
        change -= 1
print(coin)