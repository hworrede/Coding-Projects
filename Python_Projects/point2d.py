
class Point2D:

	def __init__(self, x, y):
		self.x  = x
		self.y = y
		
	def __add__(self, other):
		if type(other) == type(self):
			x_add = self.x + other.x
			y_add = self.y + other.y
			return Point2D(x_add, y_add)
			
	def __sub__(self, other):
		if type(other) == type(self):
			x_add = self.x - other.x
			y_add = self.y - other.y
			return Point2D(x_add, y_add)
			
	def __mul__(self, other):
		if type(other) == type(self):
			x_add = self.x * other.x
			y_add = self.y * other.y
			return Point2D(x_add, y_add)
			
	def __eq__(self, other):
		if type(other) == type(self):
			if(self.x == other.x and self.y == other.y):
				return True
			else:
				return False
               
				
	def __str__(self):
		return_str = f"({self.x}, {self.y})"
		return return_str
        
    def distance(self, other):
        if type(other) == type(self):
            return ((self.x - other.x)**2 + (self.y - other.y)**2)
        
        
    # def distance(self, other):
        # if type(other) == type(self):
            # return (self.x - other.x)**2 + (self.y - other.y)**2)
		
		
test = Point2D(3,4)
test1 = Point2D(4, 5)
test2 = Point2D(3, 4)


print(f"{test - test1}")
print(f"{test + test1}")
print(f"{test * test1}")

print(f"{test == test2}")

print(test)

# print(f"{distance(test, test1)}")