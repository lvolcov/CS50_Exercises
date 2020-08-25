from sys import argv, exit
import csv
import cs50

houses = ('Gryffindor', 'Hufflepuff', 'Ravenclaw', 'Slytherin')

if len(argv) != 2 or argv[1] not in houses:
    print("python roster.py house")
    exit(1)

result = {}

db = open("students.db", "r").close()
db = cs50.SQL("sqlite:///students.db")
result = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

for row in result:
    if row["middle"] == None:
        name = row["first"] + " " + row["last"]
    else:
        name = row["first"] + " " + row["middle"] + " " + row["last"]
    print(name, ", born ", row["birth"], sep="")