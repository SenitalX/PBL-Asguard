n = int(input("Enter your inputs: "))
arr =[]
for i in range(n):
    arr.append(int(input()))
    
left = 0
right = len(arr) - 1
while(left <= right):
    temp = arr[left]
    arr[left] = arr[right]
    arr[right] = temp
    left = left +1
    right = right - 1
print(arr)
