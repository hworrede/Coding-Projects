// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"
#include "stack.h"

int RPN_Evaluate(char * rpn_string, double * result)
{
float first;
float second;
double integer1;
double integer2;
double integer;
char *token = strtok(rpn_string, " ");
    
    while (token != NULL)
    {
        if (token== '+'|| token='/' || token= '-' || token= '*'){
            first= StackPop(&stack, &integer1);
            second= StackPop(&stack, &integer2);
        }
        {
            if (first == STANDARD_ERROR)||(second== STANDARD_ERROR){
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            else{
                if (token=='+'){
                    *result= first + second;
                    StackPush(&stack,*result);
                }
                else if(token=='-'){
                    *result=first - second;
                    StackPush(&stack,*result);
                }
                else if(token=='/'){
                    *result=first / second;
                    StackPush(&stack,*result);
                }
                else if(token=='*'){
                    *result=first * second;
                    StackPush(&stack,*result);
                
            }
        }
        
    }
}
}





int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

