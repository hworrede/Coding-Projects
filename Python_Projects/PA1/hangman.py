# assignment: programming assignment 1
# author: Hagos Worrede
# date: 10/6/2022

from random import choice

print("Welcome to the Hangman Game!")

#make a dictionary

text_file = open("dictionary.txt", "r")
all_lines = text_file.readlines()
text_file.close()

def import_dictionary():
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

  return word_dict

  def get_game_options():
    return (wordSize, lives)

word_dict = import_dictionary()

#print(word_dict)

#print(all_lines)
# dict = {}

# dict[0] = [];
# dict[0].append(1)

not_allowed = [';', '-', '1', '2', '3', '4', '5', '6', '7', '8', '9']


while(True):
  wordSize = input("Please choose a size of a word to be guessed [3 - 12, default any size]:")
  if not (wordSize):
      wordSize = 5
  print()
  print(f"The word size is set to {wordSize}.")
  # print(wordSize)
  wordSize = int(wordSize)
  word_list = word_dict[wordSize]
  # test = choice(word_list)
  test = "T-SHIRT"

  lives = input("Please choose a number of lives [1 - 10, default 5]:")
  try:
  	lives = int(lives)
  except:
  	lives = 0
  if not (lives):
    lives = 5
  print()
  print(f"You have {lives} lives.")
  print(f"Letters chosen: ")

  lives_visual = "O"*int(lives)

  lives_remaining = int(lives)
  test = test.upper()
  length = len(test)
  s = []
  for i in range(length):
    s.append("__  ")
  # s = "-- "*length
  for i, j in enumerate(test): ##MIGHT BEST TO CHANGE
    if(j == "-"):
      s[i] = test[i]+ "  "

  print(f"{''.join(s)} lives: {lives_remaining} {lives_visual}")

  letters_guessed = []

  while(lives_remaining):
    while(True):
      try:
        guess = input("Please choose a new letter >").upper()
      except:
        pass
      print()
      if guess not in letters_guessed and len(guess) == 1 and guess not in not_allowed:
        break
      elif guess not in not_allowed and len(guess) == 1:
        print("You have already chosen this letter.")
    letters_guessed.append(guess)
    if guess in test:
      print("You guessed right!")
      print(f"Letters chosen: " + ", ".join(str(x) for x in letters_guessed))
      for i, j in enumerate(test):
        if(j == guess):
          # print(test[i])
          s[i] = test[i] + "  "
          #s = s[:new_index] + test[i] + s[new_index+2:]
#         if(guess not in test[i:]):
      print(f"{''.join(s)} lives: {lives_remaining} {lives_visual}")
      if("__  " not in s):
        break
    else:
      lives_remaining -= 1
      print("You guessed wrong, you lost one life.")
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
  print()

  if(continue_game == "Y"):
    continue
  else :#(continue_game == "N"):
    print("Goodbye!")
    break