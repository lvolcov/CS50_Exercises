from cs50 import get_string

text = get_string("Text: ")
lenght = len(text)

letters = 0
words = 1
sentences = 0

for i in range(lenght):
    if (text[i].isalpha()):
        letters += 1
    elif (text[i].isspace()):
        words += 1
    elif (text[i] in ["!", ".", "?"]):
        sentences += 1

index = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade " + str(index))