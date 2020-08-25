from sys import argv, exit
import csv
import cs50

if len(argv) != 2:
    print("python import.py characters.csv")
    exit(1)

db = open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (id INTEGER PRIMARY KEY AUTOINCREMENT,first VARCHAR(255),middle VARCHAR(255),last VARCHAR(255),house VARCHAR(10),birth INTEGER);")

with open(argv[1], "r") as f:
    reader = csv.reader(f)
    x = 0
    for row in reader:
        if x == 0:
            x += 1
            continue
        name = row[0].split()
        first = name[0]
        if len(name) == 3:
            middle = name[1]
            last = name[2]
        else:
            middle = None
            last = name[1]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, row[1], row[2])