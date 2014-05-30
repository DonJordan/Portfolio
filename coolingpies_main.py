t = int(input())
     
for g in range(0, t):
number_of_pies = int(raw_input())
weights = []
limits = []
weights = raw_input().split()
limits = raw_input().split()
weights = map(int, weights)
limits = map(int, limits)
weights.sort()
limits.sort()
count = 0
for y in range(len(weights)):
for z in range(len(limits)):
if int(weights[y]) <= int(limits[z]):
limits[z] = 0
count += 1
break
print count 
