import turtle
# import time
s = turtle.Screen() 
s.setup(800, 800) 
s.bgcolor("White") 
s.title("Turtle Program") 
t = turtle.Turtle() 



def polygon(size, n):
    t.pendown()
    t.begin_fill()
    for i in range(n):
        t.forward(size);
        t.left(360/n);
    t.end_fill()
    
def polygon_recursive(size, n, alpha):
	if alpha:
		t.forward(size)
		t.left(360/n)
		polygon_recursive(size, n, alpha-1)
	else:
		t.end_fill()
		return
	
		
def polygon_wrapper(size, n):
	t.pendown()
	return polygon_recursive(size, n, n)
    
    
def star(size, n, d=2):
    t.pendown()
#     t.begin_fill()
    for i in range(n):
        t.forward(size)
        t.left(180*(1-1/n))
#         t.left((180*(n-1))/n)
		
    t.end_fill()

def star_recursive(size, n, alpha, d=2):
	if alpha:
		t.forward(size)
		t.left(180*(1-1/n))
		star_recursive(size, n, alpha-1, d)
	else:
		t.end_fill()
		return

def star_wrapper(size, n, d=2):
	t.pendown()
	return star_recursive(size, n, n, d)
    
    
    
# polygon(100, 8)  
# polygon_wrapper(15, 10)
# star_wrapper(100, 11)
t.penup()
t.home()
