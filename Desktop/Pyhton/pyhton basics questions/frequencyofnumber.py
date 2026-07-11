n = int(input("Enter array size: "))
arr =[]
for i in range(n):
    arr.append(int(input()))
r = int(input("Enter numbe to search: "))
count  =0 
for i in range(n):
    if arr[i] == r:
        count = count + 1
print(f"{r} appears {count} times")

