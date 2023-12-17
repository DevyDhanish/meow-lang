def show(msg):
    print(msg)

def isEven(num):
    if num % 2 == 0:
        show("Even")
    else:
        show("Odd")

isEven(10)