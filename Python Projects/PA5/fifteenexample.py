# Name: Hagos Worrede
# Class, Date: CSE30, 12/1/2022
import numpy as np
from random import choice

class Fifteen:
    def __init__(self, size = 4):
        self.tiles = ([x for x in range(1,size**2) ] + [0])
        # self.tiles = np.array([i for i in range(1, size ** 2)] + [0])
        self.adj = [[1,4],[0,2,5],[1,3,6],[2,7],[0,5,8],[1,4,6,9],[2,5,7,10],[3,6,11],[4,9,12],[5,8,10,13],[6,9,11,14],[7,10,15],[6,13],[9,12,14],[10,13,15],[11,14]]
    def update(self, move):
        if self.is_valid_move(move):
            x=0
            while self.tiles[x] != "  ":
                x += 1
            i = 0
            while self.tiles[i] != move:
                i += 1
            self.tiles[i], self.tiles[x] = self.tiles[x], self.tiles[i]        
        
    def transpose(self, i, j): 
        jt = self.tiles[j]
        self.tiles[j] = self.tiles[i]
        self.tiles[i] = jt
        return self.tiles

    def shuffle(self, steps=30):
        for _ in range(len(self.tiles)):
                if self.tiles[_] == 0:
                    self.tiles[_] = "  "

        if steps == 0:
            pass

        else:
            for x in range(len(self.tiles)):
                if self.tiles[x] == "  " :
                    move_index = choice(self.adj[x])
                    self.tiles[x], self.tiles[move_index] = self.tiles[move_index], self.tiles[x]
                    return self.shuffle(steps-1)
                
        
        
    def is_valid_move(self, move):
        for _ in range(len(self.tiles)):
                if self.tiles[_] == 0 or self.tiles[_] == "  ": 
                    move_index =  (self.adj[_])
        for _ in range(len(move_index)):
            x = move_index[_]
            if move == self.tiles[x]:
                return True
        else:
            return False

        
    def is_solved(self):
        tiles = [x for x in range(1,17)]
        tiles[15] = "  "
        if self.tiles == tiles:
            return True
        else:
            return False

    def draw(self):
        for x in range(len(self.tiles)):
                if self.tiles[x] == 0:
                    self.tiles[x] = "  "
        print("+---+---+---+---+")
        
        print(f"| {self.tiles[0]} | {self.tiles[1]} | {self.tiles[2]} | {self.tiles[3]} |")
        print("+---+---+---+---+")
        print(f"| {self.tiles[4]} | {self.tiles[5]} | {self.tiles[6]} | {self.tiles[7]} |")
        print("+---+---+---+---+")
        print(f"| {self.tiles[8]} | {self.tiles[9]} |{self.tiles[10]} | {self.tiles[11]} |" )
        print("+---+---+---+---+")
        print(f"|{self.tiles[12]} |{self.tiles[13]} |{self.tiles[14]} |{self.tiles[15]} |")
        # print(f"|{self.tiles[12]} |{self.tiles[13]}|{self.tiles[14]}  | {self.tiles[15]} |")
        print("+---+---+---+---+")

    def __str__(self):
        for x in range(len(self.tiles)):
                if self.tiles[x] == 0:
                    self.tiles[x] = "  "
        
        a = (f' {self.tiles[0]}  {self.tiles[1]}  {self.tiles[2]}  {self.tiles[3]} \n {self.tiles[4]}  {self.tiles[5]}  {self.tiles[6]}  {self.tiles[7]} \n {self.tiles[8]} {self.tiles[9]} {self.tiles[10]} {self.tiles[11]} \n{self.tiles[12]} {self.tiles[13]} {self.tiles[14]} {self.tiles[15]} \n')
        return a

if __name__ == '__main__': # Driver / debugging code
    game = Fifteen()
    assert str(game) == ' 1  2  3  4 \n 5  6  7  8 \n 9 10 11 12 \n13 14 15    \n'
    assert game.is_valid_move(15) == True
    assert game.is_valid_move(12) == True
    assert game.is_valid_move(14) == False
    assert game.is_valid_move(1) == False
    game.update(15)
    print(str(game))
    assert str(game) == ' 1  2  3  4 \n 5  6  7  8 \n 9 10 11 12 \n13 14    15 \n'
    game.update(15)
    print(str(game))
    assert str(game) == ' 1  2  3  4 \n 5  6  7  8 \n 9 10 11 12 \n13 14 15    \n'
    assert game.is_solved() == True
    game.shuffle()
    print(str(game))
    assert str(game) != ' 1  2  3  4 \n 5  6  7  8 \n 9 10 11 12 \n13 14 15    \n'
    print(str(game))
    assert game.is_solved() == False
    
    
    # You should be able to play the game if you uncomment the code below'''
    game = Fifteen()
    game.shuffle()
    game.draw()
    while True:
        move = input('Enter your move or q to quit: ')
        if move == 'q':
            break
        elif not move.isdigit():
            continue
        game.update(int(move))
        game.draw()
        if game.is_solved():
            break
    print('Game over!')