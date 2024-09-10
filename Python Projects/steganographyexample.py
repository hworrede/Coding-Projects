#import heappush, heappop, heapify methods from heapq module
from heapq import heappush, heappop, heapify
import collections

class HuffmanDataCompression()
	def huffman_encode(self,frequencyCount):
		# create a heap
		requiredHeap = [[eachweight, [eachsymbol, ""]] for eachsymbol, eachweight in frequencyCount.items()]
		#call heapify method with parameter
		heapify(requiredHeap)
		# Iterate the lowValue and build a tree

		while len(requiredHeap) > 1:
			lowValue = heappop(requiredHeap)
			highValue = heappop(requiredHeap)

			#Iterate the list lowValue
			for eachPair in lowValue[1:]:
				eachPair[1] = '0' + eachPair[1]

			#Iterate the list highValue
			for eachPair in highValue[1:]:
				eachPair[1] = '1' + eachPair[1]
			#call heappush method with parameters
			heappush(requiredHeap, [lowValue[0] + highValue[0]] + lowValue[1:] + highValue[1:])

			#return sorted method with parameters
		return sorted(heappop(requiredHeap)[1:], key=lambda m: (len(m[-1]), m))

#Implementation of main method
def main():
	#create an object for HuffmanDataCompression class
	huffmanObject = HuffmanDataCompression()
	inputFile = input("Enter the File name:");

	# read the input file
	with open(inputFile) as fileop:
		#read the characters from file
		content = fileop.read()
	# count the number of character in the file
	frequencyCount = collections.Counter(content)
	# call the huffman_encode function with frequency count
	huffmanValues = huffmanObject.huffman_encode(frequencyCount)
	#Display statement
	print("Each Character\t frequencyCount \t Huffman Code")
	#Iterate the loop
	for eachValue in huffmanValues:
		#Display statement
		print("{0}\t\t\t{1}\t\t\t{2}".format(eachValue[0], frequencyCount[eachValue[0]], eachValue[1]))

if __name__ == "__main__":
	#call main method
	main()