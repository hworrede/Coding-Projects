# Hagos Worrede
from tkinter import *
import math
import time

def draw_clock():
    w, h = 300, 300  # size of the canvas
    x, y = w/ 2, h / 2  # center of the canvas and the clock
    size = 200  # size of the clock
    circle1 = canvas.create_oval(x - size / 2, y - size / 2,
                                 x + size / 2, y + size / 2,
                                 fill='ivory')
    circle2 = canvas.create_oval(x - size / 2, y - size / 2,
                                 x + size / 2, y + size / 2,
                                 width=3, outline='black')
    ticks1, numbers = [], []
    n = 12
    for i in range(n):
        angle = 2 * math.pi * i / n
        ticks1.append(canvas.create_line(x + 100 * math.cos(angle),
                                         y + 100 * math.sin(angle),
                                         x + 90 * math.cos(angle),
                                         y + 90 * math.sin(angle),
                                         fill='black', width=2))
        numbers.append(canvas.create_text(x + 80 * math.cos(angle),
                                          y + 80 * math.sin(angle), text=str((i + 2) % n + 1)))
    ticks2 = []
    n = 60
    for i in range(n):
        angle = 2 * math.pi * i / n
        ticks1.append(canvas.create_line(x + 100 * math.cos(angle),
                                         y + 100 * math.sin(angle),
                                         x + 95 * math.cos(angle),
                                         y + 95 * math.sin(angle),
                                         fill='black', width=1))

    main_times = time.localtime()
    first_clock = time.strptime(str(main_times.tm_hour), "%H")
    check_hours = int(time.strftime("%I", first_clock)) * 5
    main_times = (check_hours, main_times.tm_min, main_times.tm_sec)

    checking_line = []
    length = 80
    checking_line.append(canvas.create_line(x, y, x + length-55, y + length-55, width=2, fill='black'))
    checking_line.append(canvas.create_line(x, y, x + length-30, y + length-30, width=2.25, fill='red'))
    checking_line.append(canvas.create_line(x, y, x + length, y + length, width=2, fill='green'))

    for k, e in enumerate(main_times):
        x, y = canvas.coords(checking_line[k])[0:2]
        clock_change = [x, y]
        clock_change.append(length * math.cos(math.radians(e * 6) - math.radians(90)) + x)
        clock_change.append(length * math.sin(math.radians(e * 6) - math.radians(90)) + y)
        canvas.coords(checking_line[k], tuple(clock_change))

    gui.after(1000, lambda: draw_clock()) 


if __name__ == "__main__":
    gui = Tk()
    gui.title("Analog Clock")
    canvas = Canvas(gui, height=300, width=300)
    canvas.pack()
    draw_clock()
    gui.mainloop()