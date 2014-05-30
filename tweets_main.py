#Problem statement: http://www.codechef.com/problems/TWTCLOSE


input = raw_input().split()
num_tweets,num_clicks = map(int,input)
for i in range(0,num_clicks):
    t = [0]*num_tweets
    for x in range(0,num_clicks):
        click = raw_input()
        if click[len(click)-1] == 'L':
            t = [0]*num_tweets
        else:
            click = int(click[len(click)-1])
            t[click-1] = (not t[click-1])
    print sum(t) 
