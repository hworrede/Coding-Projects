import turtle

def draw_spiral(t, segments, size, angle):
  t.pendown()
  for i in range(1, segments+1):
    t.fd(size*i)
    t.left(angle)


def draw_spiral_rec(t, segments, size, angle, i):
  if(i == 1):
    t.pendown()
  if(i < segments):
    t.fd(size*i)
    t.left(angle)

    draw_spiral_rec(t, segments, size, angle, i+1)

def draw_spiral_wrapper(t, segments, size, angle):
  draw_spiral_rec(t, segments, size, angle, 1)

s = turtle.Screen()
s.setup(400, 400)
t = turtle.Turtle()
t.pen(pencolor='dark violet', pensize=2, speed=0)
t.penup()
t.home()
draw_spiral_wrapper(t, 80, 2, 92)

  
