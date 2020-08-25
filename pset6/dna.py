from sys import argv, exit
import csv

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

database = {}

i = 0
with open(argv[1], "r") as f:
    reader = csv.reader(f)
    for word in reader:
        if i == 0:
            dna = word[1:]
            i += 1
        else:
            database[str(word[:1]).strip("'[]'")] = list(int(n) for n in word[1:])

file = open(argv[2], "r").read()

j = 0
count = [0] * len(dna)

for search in dna:
    s = len(search)
    cursor = repeats = final_repeats = 0
    while cursor < len(file):
        strip = file[cursor: cursor + s]
        if strip == search:
            repeats += 1
            final_repeats = max(final_repeats, repeats)
            cursor += s
        else:
            repeats = 0
            cursor += 1
    count[j] += final_repeats
    j += 1

for key in database:
    if count == database[key]:
        print(key)
        exit()

print("No match")