fn1 = input("ficheiro 1 ")
fn2 = input("ficheiro 2 ")

f1 = open(fn1)
f2 = open(fn2)

for l in f1:
    if l != f2.readline():
        print("Error")

print("Done")