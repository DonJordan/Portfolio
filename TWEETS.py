#There are N tweets on the page and each tweet can be opened by clicking on it, 
#to see some statistics related to that tweet. Initially all the tweets are closed. 
#Clicking on an open tweet closes it and clicking on a closed tweet opens it. 
#There is also a button to close all the open tweets. Given a sequence of K clicks by Jack, 
#Evan has to guess the total number of open tweets just after each click. Please help Evan in this game.


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
