import time
def calculate_time(func):
	def findtime(*args, **kwargs):

		start = time.time()
		final = func(*args, **kwargs)
		finish = time.time()
		finaltime = finish - start
		print(f'It took {finaltime} sec.')
		return final
	return findtime

# Given Code

def sum1(n):
	final = 0
	for i in range(1, n + 1):
		final += i
	return final
	

@calculate_time
def sum1(n):
	final = 0
	for i in range(1, n + 1):
		final += i
	return final
	
if __name__ == '__main__':
	firstone = 1000000
	secondone = sum1(1000000)
	print(f'The sum of numbers from 1 to {firstone} is {secondone}.')