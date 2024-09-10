import turtle

l = 'l'
r = 'r'
original = r
next_move = original
bgcolor = "white"
pencolor = "mediumblue"
measurement = 10
size_dragon = 20
movement = 1
while movement<size_dragon:
	next_move = (original) + (r)
	original = original[::-1]
	for dragon in range(0, len(original)):
		if original[dragon] == r:
			original = (original[:dragon])+ (l) + (original[dragon + 1:])
		elif original[dragon] == l:
			original = (original[:dragon]) + (r) + (original[dragon + 1:])
	next_move = (next_move) + (original)
	original = next_move
	movement = movement + 1

print(next_move)
turtle.ht()
turtle.bgcolor(bgcolor)
turtle.color(pencolor)
turtle.forward(measurement)

for dragon in range(0, len(next_move)):
	if next_move[dragon] == (r):
		turtle.right(90)
		turtle.forward(measurement)
	elif next_move[dragon] == (l):	
		turtle.left(90)
		turtle.forward(measurement)