# CSE30 PA5
# Hagos Worrede
# game.py
from tkinter import *
import tkinter.font as font
from fifteen import Fifteen

def clickButton(button):
    checking_game = str(button)[1:]
    tiles.update(int(checking_game))
    update()
    if tiles.is_solved():
        label.config(text='You Win the game!')


def update():
    checkingfirst_update = 0
    check_update = 0
    for main_tiles in tiles.tiles:
        if main_tiles == 0:
            main_tiles = 16
        buttons[main_tiles - 1].grid(row=checkingfirst_update, column=check_update)
        check_update += 1
        if check_update == 4:
            check_update = 0
            checkingfirst_update += 1

if __name__ == '__main__':
    tiles = Fifteen()
    gui = Tk()
    gui.title("Fifteen")
    font = font.Font(family='Roman', size='25', weight='bold')
    label = Label(gui, text='', font=font)
    label.grid(row=4, column=1, columnspan=4)


    trail_1 = Button(gui, text='1', name=str(1),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_1))
    trail_1.grid(row=0, column=0)

    trail_2 = Button(gui, text='2', name=str(2),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_2))
    trail_2.grid(row=0, column=1)

    trail_3 = Button(gui, text='3', name=str(3),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_3))
    trail_3.grid(row=0, column=2)

    trail_4 = Button(gui, text='4', name=str(4),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_4))
    trail_4.grid(row=0, column=3)

    trail_5 = Button(gui, text='5', name=str(5),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_5))
    trail_5.grid(row=1, column=0)

    trail_6 = Button(gui, text='6', name=str(6),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_6))
    trail_6.grid(row=1, column=1)

    trail_7 = Button(gui, text='7', name=str(7),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_7))
    trail_7.grid(row=1, column=2)

    trail_8 = Button(gui, text='8', name=str(8),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_8))
    trail_8.grid(row=1, column=3)

    trail_9 = Button(gui, text='9', name=str(9),
                     bg='white', fg='black', font=font, height=2, width=5,
                     command=lambda: clickButton(trail_9))
    trail_9.grid(row=2, column=0)

    trail_10 = Button(gui, text='10', name=str(10),
                      bg='white', fg='black', font=font, height=2, width=5,
                      command=lambda: clickButton(trail_10))
    trail_10.grid(row=2, column=1)

    trail_11 = Button(gui, text='11', name=str(11),
                      bg='white', fg='black', font=font, height=2, width=5,
                      command=lambda: clickButton(trail_11))
    trail_11.grid(row=2, column=2)

    trail_12 = Button(gui, text='12', name=str(12),
                      bg='white', fg='black', font=font, height=2, width=5,
                      command=lambda: clickButton(trail_12))
    trail_12.grid(row=2, column=3)

    trail_13 = Button(gui, text='13', name=str(13),
                      bg='white', fg='black', font=font, height=2, width=5,
                      command=lambda: clickButton(trail_13))
    trail_13.grid(row=3, column=0)

    trail_14 = Button(gui, text='14', name=str(14),
                      bg='white', fg='black', font=font, height=2, width=5,
                      command=lambda: clickButton(trail_14))
    trail_14.grid(row=3, column=1)

    trail_15 = Button(gui, text='15', name=str(15),
                      bg='white', fg='black', font=font, height=2, width=5,
                      command=lambda: clickButton(trail_15))
    trail_15.grid(row=3, column=2)

    trail_16 = Button(gui, text=' ', name=str(0),
                      bg='white', fg='black', font=font, height=2, width=5,
                      command=lambda: clickButton(trail_16))
    trail_16.grid(row=3, column=3)

    buttons = [trail_1, trail_2, trail_3, trail_4, trail_5, trail_6, trail_7, trail_8, trail_9, trail_10, trail_11,
               trail_12, trail_13, trail_14, trail_15, trail_16]
    
    tiles.shuffle(100)
    # updating the shuffle button
    trail_17 =  Button(gui, text='Shuffling', name=str(17),
                          bg='white', fg='black', font=font, height=2, width=5,
                            command=lambda: tiles.shuffle() or update())
    trail_17.grid(row=4, column=0)
    gui.mainloop()