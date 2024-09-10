for i in range(0, 3):
			if(self.board[i] == self.board[i+3] and self.board[i+3] == self.board[i+6] and self.board[i+6] in ["X", "O"]):
				self.winner = self.board[i]
				done = True
				
		
		for i in range(0, 3):
			if(self.board[i] == self.board[i+1] and self.board[i+1] == self.board[i+2] and self.board[i+2] in ["X", "O"]):
				self.winner = self.board[i]
				done = True
				
		
		if(self.board[2] == self.board[4] and self.board[4] == self.board[6] and self.board[6] in ["X", "O"]):
			winner = self.board[2]
			done = True
			
		if(self.board[0] == self.board[4] and self.board[4] == self.board[8] and self.board[8] in ["X", "O"]):
			winner = self.board[0]
			done = True
		return done