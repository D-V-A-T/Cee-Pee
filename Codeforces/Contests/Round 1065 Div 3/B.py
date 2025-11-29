fruits = ["apple", "banana", "cherry", "banana", "grapes"]
newlist = [x if x != "banana" else "skibidi" for x in fruits]
print(newlist) 