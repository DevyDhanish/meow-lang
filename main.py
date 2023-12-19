def recur(a):
    if a == 0:
        return 0
    
    print("a -> ", a)

    recur( a - 1)

print(recur(10))