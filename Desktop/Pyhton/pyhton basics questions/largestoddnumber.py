arr = [12, 7, 18, 25, 9, 14]
largest = arr[0]
found = False
for i in arr :
 if i%2!=0:
        found = 0
        if found == False :
            largest = i
            found = True
        elif i>largest:
         largest =i
if found == True:
    print(f"The largest odd number is {largest}")
else:
     print("Not found")
