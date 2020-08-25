from cs50 import get_int

credit_int = 0
while credit_int < 1:
    credit_int = get_int("Number: ")

credit_str = str(credit_int)
size = len(credit_str)
sum_final = 0

for i in range(size - 2, -1, -2):
    soma = int(credit_str[i]) * 2
    sum_final += (int(soma / 10 % 10)) + (soma % 10)
    soma = 0

for i in range(size - 1, -1, -2):
    sum_final += int(credit_str[i])

begin = credit_str[0] + credit_str[1]
valid = (sum_final % 10) == 0

if (valid and size == 15 and int(begin) in [34, 37]):
    print("AMEX")
elif (valid and size == 16 and int(begin) in range(51, 55 + 1)):
    print("MASTERCARD")
elif (valid and size in [13, 16] and int(begin[0]) == 4):
    print("VISA")
else:
    print("INVALID")