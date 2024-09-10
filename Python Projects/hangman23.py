from random import choice

print("First line")

#make a dictionary
text_file = open("dictionary.txt", "r")
all_lines = text_file.readlines()
text_file.close()

for i, j in enumerate(all_lines):
  all_lines[i] = all_lines[i].strip()

keys = []
word_dict = {}
for i in all_lines:
  if len(i) not in keys:
    word_dict[len(i)] = []
    word_dict[len(i)].append(i)
    keys.append(len(i))
  else:
    word_dict[len(i)].append(i)

print(word_dict)

print(all_lines)
# dict = {}

# dict[0] = [];
# dict[0].append(1)




while(True):
  wordSize = input("Enter number")
  if not (wordSize):
      wordSize = 5
  print(f"Word size is set to {wordSize}")
  # print(wordSize)
  wordSize = int(wordSize)
  word_list = word_dict[wordSize]
  test = choice(word_list)

  lives = input("Please choose a number of lives  ")

  print(f"You have {lives} lives")

  lives_visual = "O"*int(lives)

  lives_remaining = int(lives)
  test = test.upper()
  length = len(test)
  s = []
  for i in range(length):
    s.append("--  ")
  # s = "-- "*length
  for i, j in enumerate(test): ##MIGHT BEET TO CHANGE
    if(j == "_"):
      s[i] = test[i]+ "  "

  print(f"{''.join(s)}")

  letters_guessed = []

  while(lives_remaining):
    while(True):
      guess = input("Please choose a new letter > ").upper()
      if guess not in letters_guessed:
        break
      print("You have already choosen this letter.")
    letters_guessed.append(guess)
    if guess in test:
      print("You got a letter")
      print(f"Letters chosen: " + ", ".join(str(x) for x in letters_guessed))
      for i, j in enumerate(test):
        if(j == guess):
          # print(test[i])
          s[i] = test[i] + "  "
          #s = s[:new_index] + test[i] + s[new_index+2:]

          print(f"{''.join(s)} lives: {lives_remaining} {lives_visual}")
      if("--  " not in s):
        break
    else:
      lives_remaining -= 1
      print("You guessed wrong, you lost a life.")
      print(f"Letters chosen: " + ", ".join(str(x) for x in letters_guessed))
      index = int(lives) - lives_remaining - 1
      lives_visual = lives_visual[:index] + "X" + lives_visual[index + 1:]
      print(f"{''.join(s)} lives: {lives_remaining} {lives_visual}")
    
    # for i in letters_guessed:
    #   print(i)
  if(lives_remaining):
    print(f"Congratulations!!! You won! The word is {test.upper()}!")

  else:
    print(f"You lost! The word is {test.upper()}!")

  continue_game = input("Would you like to play again [Y/N]?").upper()

  if(continue_game == "Y"):
    continue
  elif(continue_game == "N"):
    print("Goodbye!")
    break


