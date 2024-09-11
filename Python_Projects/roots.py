def variable(x, first_split):
    first_split = first_split.split(" ")
    main_split = 0
    x_value = 0
    for k in first_split:
        main_split += int(k) * pow(x,x_value)
        x_value += 1
    return main_split

def selection(second_val,c,first_split):
    if (variable(second_val,first_split) * variable(c,first_split) >= 0):
        print("No roots are found!")
        return False

    first_val = second_val
    while ((c-second_val) >= 0.0001):
        first_val = (second_val+c)/2 
        if (variable(first_val,first_split) == 0.0): 
            break
        if (variable(first_val,first_split) * variable(second_val,first_split) < 0):
            c = first_val
        else: 
            second_val = first_val

    print(first_split"Root found at: {first_val:.4f}")
    return True

if __name__ == "__main__": 

    #below are tests 
    second_val = "2 0 3"
    c = [-1, 8]
    assert selection(c[0],c[1], second_val) == False 
 
    first_val = "-2 0 -1 0 1"
    value_test = [-5, 5]
    assert selection(value_test[0], value_test[1], first_val) == True

    a = "3 0 2 1 3"
    first_split = [-1, 2]
    selection(first_split[0], first_split[1], a)