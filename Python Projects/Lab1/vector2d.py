# Vector2D class for operating with vector objects
import math

class Vector2D():
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
        self.thresh = 0.000001
        
    def __add__(self, other):
        return Vector2D(other.x + self.x,other.y + self.y)

    def __sub__(self, other):
        return Vector2D(other.x - self.x,other.y - self.y)

    def __neg__(self):
        return Vector2D(self.x*(-1),self.y*(-1))

    def __mul__(self, scalar):
        return Vector2D(self.x*scalar,self.y*scalar)

    def __div__(self, scalar):
        if scalar != 0:
            x=self.x/scalar
            y=self.y/scalar
            return Vector2D(x,y)
        else:
            return None
        
    def __truediv__(self, scalar):
        return self.__div__(scalar)

    def __eq__(self, other):
        if abs(self.x - other.x) < self.thresh:
            if abs(self.y - other.y) < self.thresh:
                return True
        return False

    def __ge__(self, other):
        if self.magnitude() >= other.magnitude:
            return True
        else:
            return False
        

    def __lt__(self, other):
        if self.magnitude() < other.magnitude:
            return True
        else:
            return False

    def __hash__(self):
        return id(self)

    def __str__(self):
        return "<" + str(self.x) + ", " + str(self.y) + ">"

    def magnitudeSquared(self):
        finalmag=self.x^2+self.y^2
        return finalmag

    def magnitude(self):
        return sqrt(self.magnitudeSquared())

    def normalize(self):
        norm = self.magnitude()
        if norm != 0:
            return 
        return None
    
    def dot(self, other):
        return Vector2D(self.x * other.x,self.y * other.y)

    def copy(self):
        return Vector2D(x,y)
            
if __name__ == '__main__':
    v1 = Vector2D(2, 3)
    v2 = Vector2D(0.5, -1.5)
    print(f'The sum of {v1} and {v2} is {v1+v2}')
    print(f'The dot product of {v1} and {v2} is {v1.dot(v2)}')