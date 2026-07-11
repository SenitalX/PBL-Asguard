n = int(input("Enter Array size: "))
arr =[]
for i in range(n):
    arr.append(int(input()))

for i in range(n-1) :
    if arr[i+1] - arr[i] > 1:
        print(f"The missing number is {arr[i] + 1}")
  