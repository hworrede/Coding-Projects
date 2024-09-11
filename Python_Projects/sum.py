def sum_list_helper(test, i, curr_sum):
  if len(test) == 0:
    return None
  if i < len(test):
    curr_sum += test[i]
    x = sum_list_helper(test, i+1, curr_sum)
    return x
  else:
    return curr_sum


def sum_list(test_list):
  return sum_list_helper(test_list, 0, 0)










