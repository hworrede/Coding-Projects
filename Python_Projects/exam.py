import cv2
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import os
from math import ceil
root=os.getcwd()
filein=os.path.join(root, 'PA3/redbox.jpg')
image = cv2.imread(filein)
# print(image)
test = [ [[0, 0,255], [0, 0, 255]],
  [[0, 0, 255], [0, 0, 255]], 
  [[0, 0, 255], [0, 0, 255]] ]
# print(len(test))
# print(len(test[0]))
# print(len(image))
# print(len(image[0]))
test = "011010000110010101101100011011000110111100100011"
z = 0
for i, twod_image in enumerate(image):
	for j, oned_image in enumerate(twod_image):
		for k, pixel in enumerate(oned_image):
			if(z == len(test)):
				break
			text = ''
			val = list(format(pixel, "08b"))
			val[len(val)-1] = test[z]
			for x in val:
				text += str(x)
			text = int(text, 2)
			z += 1
			image[i][j][k] = text			

# print(image)

message = ''
flag = False
for i, twod_image in enumerate(image):
	for j, oned_image in enumerate(twod_image):
		for k, pixel in enumerate(oned_image):
			bin = format(image[i][j][k], "08b")
			message += bin[len(bin)-1]

			
print(message)
binary = []        
for i in range(0,len(message),8):
    byte = message[i: i+8]
    if byte == format(ord('#'), "08b"):
    	break
    binary.append(byte)
    text = ''
    for byte in binary:
        text += chr(int(byte,2))       
print(text) 
        
        
        
			