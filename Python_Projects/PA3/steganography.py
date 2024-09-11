# steganography
import cv2
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from math import ceil
from codec import Codec, CaesarCypher, HuffmanCodes

# def applyMessage(binary, imageArray):
#     z = 0
#     flag = False
#     print(f"This is the binary: {binary}")
# #           ew_image = np.copy(image)	#create copy of image array (so we aren't modifying image)
#     for i, twod_image in enumerate(imageArray):		#loop over the np array to get to the pixel vals
#     	if flag:
#     		break
#     	for j, oned_image in enumerate(twod_image):
#         	if flag:
#         		break
#         	for k, pixel in enumerate(oned_image):
#         		if(z == len(binary)):		#if have written the full message
#         			flag = True
#         			break					#break out of loop and stop overwriting og array
#         		else:
#         			textz = ''				#str to hold new binary value
#         			val = list(format(pixel, "08b"))	#get list of pixel in binary
#         			val[len(val)-1] = binary[z]			#write the message bit to the last bit 
#         			for x in val:					#create string from array
#         				textz += str(x)
#         			print(textz)
#         			textz = int(textz, 2)	#convert binary string to integar
# #         			print(type(text), text)
#         			z += 1							#add to message iterator
#         			if(imageArray[i][j][k] != textz):
#         				imageArray[i][j][k] = textz		#assign new pixel value
#         			print(imageArray, z)
#     return imageArray

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
            a = 0
            for j in range(len(image)):
            	for n in range(len(image[j])):
            		for i in range(len(image[j,n])):
            			if a < len(self.binary):
            				if str(self.binary[a]) == str(0):
            					if image[j,n,i]%2==1:
            						image[j,n,i]=image[j,n,i]-1
            					else:
            						pass
            				elif str(self.binary[a])==str(1):
            					if image[j,n,i]%2 ==0:
            						image[j,n,i]=image[j,n,i]+1
            					else:
            						pass
            				a+=1
            
            cv2.imwrite(fileout, image)
                   
#             
#             image_display=image.reshape(-1)
#             list=[x for x in self.binary]
#             for numone in range(len(list)):
#             	if int(list[numone])==1 and (image_display[numone] % 2)==0:
#             		image_display[numone]=image_display[numone]-1
#             	if int(list[numone])==0 and (image_display[numone] % 2)!= 0:
#             		image_display[numone]=[image_display[numone]+1
#             image=np.reshape(image_display, image.shape)
#             print(image)
#             # your code goes here
#             # you may create an additional method that modifies the image array
#             cv2.imwrite(fileout, image)
                   
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
            binary_data=""
            for j in np.nditer(image):
            	if j%2==0:
            		binary_data +="0"
            	elif j%2==1:
            		binary_data +="1"
            self.text = self.codec.decode(binary_data)		#decode binary string
            self.binary = self.codec.encode(self.text + self.delimiter)  
            
            
            
#             
#             message = ''
#             for j, twod_image in enumerate(image):	#loop over image array
#             	for n, oned_image in enumerate(twod_image):
#             		for i, pixel in enumerate(oned_image):
#             			bin = format(image[j][n][i], "08b")		#get binary of pixel
#             			message += bin[len(bin)-1]			#append the last bit to the message str
#             # you may create an additional method that extract bits from the image array
#             binary_data = message
#             # update the data attributes:
#             self.text = self.codec.decode(binary_data)		#decode binary string
#             self.binary = self.codec.encode(self.text)            
        
    def print(self):
        if self.text == '':
            print("The message is not set.")
        else:
            print("Text message:", self.text)
            print("Binary message:", self.binary)          

    def show(self, filename):
        plt.imshow(mpimg.imread(filename))
        plt.show()

