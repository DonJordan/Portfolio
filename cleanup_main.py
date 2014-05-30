#Problem statement: http://www.codechef.com/problems/CLEANUP

t_cases = int(raw_input())

for x in range(0,t_cases):
    c = []
    a = []
    n,m = map(int, raw_input().split())
    d = map(int, raw_input().split())
    flag = 1
    for x in range(1,n+1):
        if x not in d:
            if flag == 1:
                c.append(x)
                flag = 0
            else:
                a.append(x)
                flag = 1
    str1 = ''
    str2 = ''
    
    for y in range(0,len(c)):
        str1 = str1 + str(c[y]) + " "
    for z in range(0,len(a)):
        str2 = str2 + str(a[z]) + " "
        
    print str1
    print str2
