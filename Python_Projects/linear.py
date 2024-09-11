# Hagos Worrede
import pulp as p

main_solve = p.LpProblem('Problem', p.LpMaximize) 

# Creating variables for all
first_main = p.LpVariable("a", lowBound = 0) 
second_main = p.LpVariable("b", lowBound = 0) 
third_main = p.LpVariable("c", lowBound = 0) 

#main function 
main_solve +=(800*first_main+1300*second_main+1800*third_main)

# fixes all problems
main_solve += 122*first_main + 237*second_main + 307*third_main <= 3000 
main_solve += 95*first_main + 130*second_main + 180*third_main <= 2000

status = main_solve.solve()

#final print 
print(f"Trip A: {p.value(first_main)} amount") 
print(f"Trip B: {p.value(second_main)} amount")
print(f"Trip C: {p.value(third_main)} amount")