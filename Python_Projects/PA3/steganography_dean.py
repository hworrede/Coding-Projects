# steganography
import cv2
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from math import ceil
from codec import Codec, CaesarCypher, HuffmanCodes

def applyMessage(binary, imageArray):
    z = 0
    flag = False
    print(f"This is the binary: {binary}")
#           ew_image = np.copy(image)	#create copy of image array (so we aren't modifying image)
    for i, twod_image in enumerate(imageArray):		#loop over the np array to get to the pixel vals
    	if flag:
    		break
    	for j, oned_image in enumerate(twod_image):
        	if flag:
        		break
        	for k, pixel in enumerate(oned_image):
        		if(z == len(binary)):		#if have written the full message
        			flag = True
        			break					#break out of loop and stop overwriting og array
        		else:
        			textz = ''				#str to hold new binary value
        			val = list(format(pixel, "08b"))	#get list of pixel in binary
        			val[len(val)-1] = binary[z]			#write the message bit to the last bit 
        			for x in val:					#create string from array
        				textz += str(x)
        			print(textz)
        			textz = int(textz, 2)	#convert binary string to integar
#         			print(type(text), text)
        			z += 1							#add to message iterator
        			if(imageArray[i][j][k] != textz):
        				imageArray[i][j][k] = textz		#assign new pixel value
        			print(imageArray, z)
    return imageArray

class Steganography():
    
    def __init__(self):
        self.text = ''
        self.binary = ''
        self.delimiter = '#'
        self.codec = None

    def encode(self, filein, fileout, message, codec):
        image = cv2.imread(filein)
        print(image) # for debugging
        
        # calculate available bytes
        max_bytes = image.shape[0] * image.shape[1] * 3 // 8
        print("Maximum bytes available:", max_bytes)

        # convert into binary
        if codec == 'binary':
            self.codec = Codec(delimiter = self.delimiter) 
        elif codec == 'caesar':
            self.codec = CaesarCypher(delimiter = self.delimiter)
        elif codec == 'huffman':
            self.codec = HuffmanCodes(delimiter = self.delimiter)
        binary = self.codec.encode(message + self.delimiter)
        
        # check if possible to encode the message
        num_bytes = ceil(len(binary)//8) + 1 
        if  num_bytes > max_bytes:
            print("Error: Insufficient bytes!")
        else:
            print("Bytes to encode:", num_bytes) 
            self.text = message
            self.binary = binary
            # your code goes here
            image = applyMessage(binary, image)
            			
        didWrite = cv2.imwrite(fileout, image)
        print(didWrite)
        print(f"This is being written {image}")
#         np.save("image.npy", image)
#         new_i = np.load("image.npy")
#         
#         print(f"This is the file being written {new_i}")
#         file1 = open("image.txt", "w")
#         file1.write(str(image))
#         file1.close()
#         file1 = open("image.txt", "r")
#         new_i = file1.readlines()
#         for i in new_i:
#         	print(i)
#         file1.close()


#         print(list(new_i))
       
#         print(didWrite)
#         new_image = cv2.imread(fileout)
#         old_image = cv2.imread(filein)
#         if not (np.array_equal(image, old_image)):
#         	 didWrite = cv2.imwrite(fileout, image)
#         	 print(didWrite)
#         else:
#         	print("they are equal")
        new_image = cv2.imread(fileout)
        print(f"This is new {new_image}")
                   
    def decode(self, filein, codec):
        image = cv2.imread(filein)
        print(image) # for debugging      
        
        # convert into text
        if codec == 'binary':
            self.codec = Codec(delimiter = self.delimiter) 
            flag = True
        elif codec == 'caesar':
            self.codec = CaesarCypher(delimiter = self.delimiter)
            flag = True
        elif codec == 'huffman':
            if self.codec == None or self.codec.name != 'huffman':
                print("A Huffman tree is not set!")
                flag = False
        if flag:
            # your code goes here
            message = ''
            for i, twod_image in enumerate(image):	#loop over image array
            	for j, oned_image in enumerate(twod_image):
            		for k, pixel in enumerate(oned_image):
            			bin = format(image[i][j][k], "08b")		#get binary of pixel
            			message += bin[len(bin)-1]			#append the last bit to the message str
            # you may create an additional method that extract bits from the image array
            binary_data = message
            # update the data attributes:
            self.text = self.codec.decode(binary_data)		#decode binary string
            self.binary = self.codec.encode(self.text)            
        
    def print(self):
        if self.text == '':
            print("The message is not set.")
        else:
            print("Text message:", self.text)
            print("Binary message:", self.binary)          

    def show(self, filename):
        plt.imshow(mpimg.imread(filename))
        plt.show()
        
# if __name__ == '__main__':
#     text = 'hello'
#     #text = 'Casino Royale 10:30 Order martini'
#     print('Original:', text)
# 
# 	s = Stenography()
# 	

