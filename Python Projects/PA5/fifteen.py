# CSE30 PA5
# Hagos Worrede
# fifteen.py
import random

import numpy as np
from random import choice


class Fifteen:

    def __init__(self, size=4):
        self.tiles = np.array([i for i in range(1, size ** 2)] + [0])
        self.size = size

    def update(self, move):
        if self.is_valid_move(move):
            main_none = 0
            main_temp = 0
            for i, j in enumerate(self.tiles):
                if j == 0:
                    main_none = i
                if j == move:
                    main_temp = i
            self.transpose(main_none, main_temp)

    def transpose(self, i, j):
        main_temp = self.tiles[i]
        self.tiles[i] = self.tiles[j]
        self.tiles[j] = main_temp
    
    def get_valid_moves(self):
        check_move = []
        for i, j in enumerate(self.tiles):
            if j == 0:
                main_none = i
    	if main_none > 3:
            check_move.append(self.tiles[main_none - 4])
        if main_none % 4 != 3:
            check_move.append(self.tiles[main_none + 1])
        if main_none % 4 != 0:
            check_move.append(self.tiles[main_none - 1])
        if main_none < 12:
            check_move.append(self.tiles[main_none + 4])
        return check_move

    def shuffle(self, moves=100):
        for i in range(moves):
            self.update(choice(self.get_valid_moves()))

    def is_valid_move(self, move):
        if move in self.get_valid_moves():
            return True
        return False
        
    def is_solved(self):
        if self.tiles.tolist() == [i for i in range(1, self.size ** 2)] + [0]:
            return True
        return False

    def draw(self):
        print('+---+---+---+---+')
        for i in range(4):
            print('|', end='')
            for j in range(4):
                if self.tiles[(i * 4) + j] == 0:
                    print(f'   |', end='')

                elif self.tiles[(i * 4) + j] < 10:
                    print(f' {self.tiles[(i * 4) + j]} |', end='')
                else:
                    print(f'{self.tiles[(i * 4) + j]} |', end='')
            print('\n'
                  '+---+---+---+---+')

    def __str__(self):
        a = ''
        main_temp = []
        check_next = 0
        for m in self.tiles:
            main_temp.append(str(m))
        for k in main_temp:
            if len(k) == 1:
                a += ' '
            if k != '0':
                a += k + ' '
            else:
                a += '  '
            check_next += 1
            if check_next == 4:
                a += '\n'
                check_next = 0
        return a