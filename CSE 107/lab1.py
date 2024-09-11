import random

def flip_coin(p): #p is probability of returning heads
  if(random.random() <= p):
    return 0 #heads
  else:
    return 1 #tails

# coin_list = []

# for i in range(100):
#   coin_list.append(flip_coin(0.7))

def print_number_of_heads_tails(coin_list):
  number_of_ones = 0
  number_of_zeros = 0
  for i in coin_list:
    if i == 1:
      number_of_ones += 1
    else:
      number_of_zeros += 1

  print(f"number of tails = {number_of_ones}")
  print(f"number of heads = {number_of_zeros}")
  print()

def get_number_of_heads(coin_list):
  number_of_ones = 0
  number_of_zeros = 0
  for i in coin_list:
    if i == 1:
      number_of_ones += 1
    else:
      number_of_zeros += 1

  return number_of_zeros

def get_number_of_tails(coin_list):
  number_of_ones = 0
  number_of_zeros = 0
  for i in coin_list:
    if i == 1:
      number_of_ones += 1
    else:
      number_of_zeros += 1

  return number_of_ones

#print_number_of_heads_tails(coin_list)

# test = [0, 4, 5, 6, 7]
def average_of_list(list_to_average):
  sum = 0
  for i in list_to_average:
    sum += i
  return sum/len(list_to_average)

# print(f'this is the average {average_of_list(test)}')

n = [5, 10, 50, 100] #101 coins to toss
# n = [10**3]
p = [0.2, 0.3, 0.4, 0.6, 0.7, 0.8]
# p = [0.5]
trials = 1000
for num in n:
  print(f"n = {num}")
  more_heads_per_p = []
  for prob in p:
    print(f"Probability heads = {prob}")
    coins_to_toss = 2*num + 1
    coins_tossed_by_bob = num + 1
    coins_tossed_by_alice = num
    bob_tossed_more_head = 0

    for i in range(trials):
      bob_coin_list = []
      alice_coin_list = []
      for i in range(coins_tossed_by_bob):
        bob_coin_list.append(flip_coin(prob))

      for i in range(coins_tossed_by_alice):
        alice_coin_list.append(flip_coin(prob))


      if(get_number_of_heads(bob_coin_list) > get_number_of_heads(alice_coin_list)):
        bob_tossed_more_head += 1

    print(f"relative frequency given p = {prob}: {bob_tossed_more_head/trials}")

    more_heads_per_p.append(bob_tossed_more_head)

    

    #print(f"How many times did bob toss more heads than alice? --> {bob_tossed_more_head}")
    print()
  print(f"average = {average_of_list(more_heads_per_p)}")
  print(f"relative frequency = {average_of_list(more_heads_per_p)/trials}")
  print()
  print("-"* 50)
  print()