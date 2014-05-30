#This function determines if two squares overlap each other, and if they do, then the overlapping area is calculated.
#The input is the lower left corner coordinate of each square and the length of the sides.


square1 = raw_input("Enter Parameters for Square 1 (x y l): ")
square2 = raw_input("Enter Parameters for Square 2 (x y l): ")

sq1 = {'x1': 1, 'y1': 2,'x2':1, 'y2':1, 'len': 1}
sq2 = {'x1': 1, 'y1': 2,'x2':1, 'y2':1, 'len': 1}

def coordinates():
    ## Square 1
    i = 0
    if square1[0] == '-':
        sq1['x1'] = int(square1[:2])
        i += 3
    else:
        sq1['x1'] = int(square1[0])
        i += 2
    if square1[i] == '-':
        sq1['y1'] = int(square1[i:i+2])
        i += 3
    else:
        sq1['y1'] = int(square1[i])
        i += 2
    sq1['len'] = int(square1[i])
    
    ## Square 2
    i = 0
    if square2[0] == '-':
        sq2['x1'] = int(square2[:2])
        i += 3
    else:
        sq2['x1'] = int(square2[0])
        i += 2
        
    if square2[i] == '-':
        sq2['y1'] = int(square2[i:i+2])
        i += 3
    else:
        sq2['y1'] = int(square2[i])
        i += 2
    sq2['len'] = int(square2[i])
    
def normalize():
    # Move all coordinates to the first quadrant
    if (sq2['x1'] < 0):
        sq1['x1'] = sq1['x1'] + abs(sq2['x1'])
        sq2['x1'] = sq2['x1'] + abs(sq2['x1'])
    if (sq2['y1'] < 0):
        sq1['y1'] = sq1['y1'] + abs(sq2['y1'])
        sq2['y1'] = sq2['y1'] + abs(sq2['y1'])
    if (sq1['x1'] < 0):
        sq2['x1'] = sq2['x1'] + abs(sq1['x1'])
        sq1['x1'] = sq1['x1'] + abs(sq1['x1'])
    if (sq1['y1'] < 0):
        sq2['y1'] = sq2['y1'] + abs(sq1['y1'])
        sq1['y1'] = sq1['y1'] + abs(sq1['y1'])
    
    if (sq1['x1'] < sq2['x1']):
        sq2['x1'] -= sq1['x1']
        sq1['x1'] = 0
    if (sq2['x1'] < sq1['x1']):
        sq1['x1'] -= sq2['x1']
        sq2['x1'] = 0
    
    sq1['x2'] = sq1['x1'] + sq1['len']
    sq1['y2'] = sq1['y1'] + sq1['len']
    sq2['x2'] = sq2['x1'] + sq2['len']
    sq2['y2'] = sq2['y1'] + sq2['len']

def overlap():
    #Do the squares overlap?
    if sq1['x1'] == 0:
        if (sq1['y2'] > sq2['y1']) and (sq1['x2'] > sq2['x1']):
            return True
        else:
            return False
    if sq2['x1'] == 0:
        if (sq2['y2'] > sq1['y1']) and (sq2['x2'] > sq1['x1']):
            return True
        else:
            return False

def calculate_area(a,b):
    # Calculate area of overlap
    if (a['x1'] >= b['x1'] and a['x2'] <= b['x2']) and a['y1'] < b['y2'] and a['y2'] > b['y2']:
        y = b['y2'] - a['y1']
        x = b['x2'] - a['x1']
        return y*x
    if (a['y1'] < b['y2'] and a['y2'] > b['y2'] and a['x1'] < b['x2'] and a['x2'] > b['x2']):
        x = b['x2'] - a['x1']
        y = b['y2'] - a['y1']
        return y*x
    if (a['y1'] >= b['y1'] and a['y2'] <= b['y2']) and a['x1'] < b['x2'] and a['x2'] > b['x2']:
        y = a['y2'] - a['y1']
        x = b['x2'] - a['x1']
        return x*y
    if (a['y1'] < b['y1'] and a['y2'] > b['y1'] and a['x1'] < b['x2'] and a['x2'] > b['x2']):
        y = a['y2'] - b['y1']
        x = b['x2'] - a['x1']
        return y*x
    if (a['x1'] == b['x1'] or a['x2'] == b['x2']) and a['y1'] < b['y1']:
        y = a['y2'] - b['y1']
        x = a['x2'] - a['x1']
        return y*x
    if (a['x2'] <= b['x2'] and a['x1'] >= b['x1'] and a['y2'] <= b['y2'] and a['y1'] >= b['y1']):
        y = a['y2'] - a['y1']
        x = a['x2'] - a['x1']
        return y*x
    
coordinates()
normalize()
if overlap():
    if sq1['x1'] < sq2['x1']:
        print calculate_area(sq2,sq1)
    if sq2['x1'] < sq1['x1']:
        print calculate_area(sq1,sq2)
else:
    print 'no overlap!'
