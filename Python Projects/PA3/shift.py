test = "type"
test = "abcdefghijklmnopqrstuvwxyz"
test = "hello#"
n = -3
data = ''
for i in test:
	uni = int(format(ord(i)))
	norm = uni - 97
#	new = norm % 26
	cipher = (norm + n) % 26
	cipher_final = cipher + 97
#	print(format(ord(i), "08b"), format(cipher_final, "08b"))
	a = format(cipher_final, "08b")
	data += str(format(cipher_final, "08b"))

print(data)


