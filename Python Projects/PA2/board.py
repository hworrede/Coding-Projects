# author: Hagos Worrede
# date: October 20, 2022
# file: board.py a Python program that implements a tic-tac-toe game
class Board:
	def __init__(self):
            # board is a list of cells that are represented 
            # by strings (" ", "O", and "X")
            # initially it is made of empty cells represented 
            # by " " strings
            self.sign = " "
            self.size = 3
            self.board = { "C1": self.sign, "C2": self.sign, "C3": self.sign,
                           "B1": self.sign, "B2": self.sign, "B3": self.sign,
                           "A1": self.sign, "A2": self.sign, "A3": self.sign }
            # the winner's sign O or X
            self.winner = ""
	def get_size(self): 
            return self.size
	def get_winner(self):
            # return the winner's sign O or X (an instance winner)   
            return self.winner  
	def set(self, index_main, sign):
            # mark the index_main on the board with the sign X or O
            main_pick = ['C1', 'C2', 'C3', 'B1', 'B2', 'B3', 'A1', 'A2', 'A3']
            if index_main in main_pick:
                  self.board[index_main] = sign
	def isempty(self, index_main):
            # return True if the index_main is empty (not marked with X or O)
            if self.board[index_main] == " ":
                  return True
	def isdone(self):
            done = False
            #checking the game if all situations work for O and X 
            if self.board["C1"] == self.board["C2"] == self.board["C3"] != " ":
                  done = True
                  self.winner = self.board["C1"]
            elif self.board["A1"] == self.board["A2"] == self.board["A3"] != " ":
                  done = True
                  self.winner = self.board["A1"]
            elif self.board["B1"] == self.board["B2"] == self.board["B3"] != " ":
                  done = True
                  self.winner = self.board["B1"]
            elif self.board["C1"] == self.board["B1"] == self.board["A1"] != " ":
                  done = True
                  self.winner = self.board["C1"]
            elif self.board["C2"] == self.board["B2"] == self.board["A2"] != " ":
                  done = True
                  self.winner = self.board["C2"]
            elif self.board["C3"] == self.board["B3"] == self.board["A3"] != " ":
                  done = True
                  self.winner = self.board["C3"]
            elif self.board["C3"] == self.board["B2"] == self.board["A1"] != " ":
                  done = True
                  self.winner = self.board["C3"]
            elif self.board["C1"] == self.board["B2"] == self.board["A3"] != " ":
                  done = True
                  self.winner = self.board["C1"]
            
            elif self.board["C1"] != " " and self.board["C2"] != " " and self.board["C3"] != " " and self.board["B1"] != " " and self.board["B2"] != " " and self.board["B3"] != " " and self.board["A1"] != " " and self.board["A2"] != " " and self.board["A3"] != " ":
                  done = True
                  self.winner = " "
            else:
                  done = False
            return done
            
	def show(self):
		#drawing the board and adding the correct points
            print('   A   B   C') 
            print(' +---+---+---+')
            print('1| {} | {} | {} |'.format(self.board["A1"], self.board["B1"], self.board["C1"]))
            print(' +---+---+---+')
            print('2| {} | {} | {} |'.format(self.board["A2"], self.board["B2"], self.board["C2"]))
            print(' +---+---+---+')
            print('3| {} | {} | {} |'.format(self.board["A3"], self.board["B3"], self.board["C3"]))
            print(' +---+---+---+')
            
	def returnCells(self):
            return_empty = []
            for index_main in self.board:
                  if self.board[index_main] == " ":
                        return_empty.append(index_main)
            return return_empty