def queens(main_puzzle):
    main_num = list(range(main_puzzle))
    main_end = []
    input_answer = []
    elem = 0
    for k in all_perms(main_num):
        permutation_main = 0
        for m in range(main_puzzle):
            if permutation_main != m * (m-1) / 2:
                break
            for n in range(1, main_puzzle):
                if m >= n:
                    if k[m] == k[m - n] - n or k[m] == k[m-n] + n:
                        permutation_main = 0
                        break
                    else:
                        permutation_main += 1
                else:
                    continue
            if permutation_main == main_puzzle*(main_puzzle-1)/2:
                elem += 1
                for r in range(main_puzzle):
                    main_end.append(k[r]+ 1)
                input_answer.append(main_end)
                main_end = []
            else:
                pass
    print(f"The {main_puzzle}-queens puzzle has {elem} solutions:")
    for i in input_answer:
        print(i)

def all_perms(elements):
    if len(elements) <= 1:
        yield elements
    else:
        for perm in all_perms(elements[1:]):
            for i in range(len(elements)):
                yield perm[:i] + elements[0:1] + perm[i:] 

if __name__ == '__main__':
    main_num = int(input("Enter a number of queens: \n"))
    input_answer = queens(main_num)