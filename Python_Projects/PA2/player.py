# author: Hagos Worrede
# date: October 20, 2022
# file: player.py a Python program that implements a tic-tac-toe game
import random
class Player:
      def __init__(self, name, sign):
            self.name = name  # player's name
            self.sign = sign  # player's sign O or X
      def get_sign(self):
            # return an instance sign
            return self.sign
      def get_name(self):
            # return an instance name
            return self.name
      def choose(self, board):
            # choosing the correct choice for the board
            main_pick = ['C1', 'C2', 'C3', 'B1', 'B2', 'B3', 'A1', 'A2', 'A3']
            while True: 
                  index_main = input(f'{self.name}, {self.sign}: Enter a cell [A-C][1-3]:\n').upper()
                  if index_main in main_pick:
                        if board.isempty(index_main):
                              board.set(index_main, self.sign)
                              break
                        else:
                              print('You did not choose correctly.')
                        
class AI(Player):
      def __init__(self, name, sign, board):
            super().__init__(name, sign)
            self.board = board
      def choose(self, board):
      		#choosing a random choice and it will show on the board
            main_pick = ['C1', 'C2', 'C3', 'B1', 'B2', 'B3', 'A1', 'A2', 'A3']
            while True:
                  index_main = random.choice(main_pick)
                  if board.isempty(index_main):
                        board.set(index_main, self.sign)
                        break
                  else:
                        continue
      
class MiniMax(Player):
    def choose(self, board):
        print(f"\n{self.name}, {self.sign}: Enter a cell [A-C][1-3]: ")
        index_main = MiniMax.minimax(self, board, True, True)
        print(index_main)
        board.set(index_main, self.sign)
        
    def minimax(self, board, main_opponent, start):
      if board.isdone():
      #outcome will be a win
            if board.get_winner() == self.sign:
                  return 1
            #outcome will become a tie
            elif board.get_winner() == ' ':
                  return 0
            #the outcome is they lose
            else:
                  return -1
      #this makes a move and sees the outcome          
      if main_opponent:
            final_points = -100
            for index_main in board.returnCells():
                  board.set(index_main, self.sign)
                  updated_point = MiniMax.minimax(self, board, False, False)
                  board.set(index_main, ' ')
                  final_points = max(updated_point, final_points)
            if start:
                  return index_main
            else:
                  return final_points
      else:
            final_points = 100
            for index_main in board.returnCells():
                  board.set(index_main, "O" if self.sign == "X" else "X")
                  updated_point = MiniMax.minimax(self, board, True, False)
                  board.set(index_main, ' ')
                  final_points = min(updated_point, final_points)
            return final_points
            

class SmartAI(Player):
      def __init__(self, name, sign, board):
            super().__init__(name, sign)
            self.board = board
            
      def choose(self, board):
      	#choosing a pick and it show on the board, it will also determine if AI wins, blocks
            main_pick = ['C1', 'C2', 'C3', 'B1', 'B2', 'B3', 'A1', 'A2', 'A3']
            while True:
                  if self.finalwin(board):
                        index_main = self.finalwin(board)
                        board.set(index_main, self.sign)
                        break
                  elif self.finalblock(board):
                        index_main = self.finalblock(board)
                        board.set(index_main, self.sign)
                        break
                  else:
                        index_main = random.choice(main_pick)
                        if board.isempty(index_main):
                              board.set(index_main, self.sign)
                              break
                        else:
                              continue
                              
      def finalwin(self, board):
      	#this checks if the AI will win 
            main_pick = ['C1', 'C2', 'C3', 'B1', 'B2', 'B3', 'A1', 'A2', 'A3']
            for index_main in main_pick:
                  if board.isempty(index_main):
                        board.set(index_main, self.sign)
                        if board.isdone():
                              return index_main
                        else:
                              board.set(index_main, ' ')
            return None
            
      def finalblock(self, board):
            #this checks if the AI will block
            main_pick = ['C1', 'C2', 'C3', 'B1', 'B2', 'B3', 'A1', 'A2', 'A3']
            for index_main in main_pick:
                  if board.isempty(index_main):
                        board.set(index_main, self.opposite_pick())
                        if board.isdone():
                              board.set(index_main, ' ')
                              return index_main
                        else:
                              board.set(index_main, ' ')
            return None
      def opposite_pick(self):
            if self.sign == 'X':
                  return 'O'
            else:
                  return 'X'