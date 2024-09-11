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
struct Stack stack = {}; 
StackInit(&stack);
float first;
float second;
double integer1;
double integer2;
double integer;
char *token = strtok(rpn_string, " ");
    
    while (token != NULL)
    {
        
        if (*token == '+' || ((token[0] == '-') && (token[1] == '\0')) || *token == '/' || *token == '*' || *token == '-'){
            StackPop(&stack, &integer1);
            first = integer1;
            StackPop(&stack, &integer2);
            second=integer2;
        
            if ((first == STANDARD_ERROR)||(second== STANDARD_ERROR)){
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            else {
                if (*token=='*'){
                    *result= first * second;
                    StackPush(&stack,*result);
                }
                else if(*token=='-'){
                    *result=second - first;
                    StackPush(&stack,*result);
                }
                else if(*token=='/'){
                    *result=second / first;
                    StackPush(&stack,*result);
                }
                else if(*token=='+'){
                    *result=first + second;
                    StackPush(&stack,*result);
                
            }
            
        }
        }
        else if (atof(token) != 0) {
            integer = StackPush(&stack, atof(token));
            
            if (integer==STANDARD_ERROR){
                return RPN_ERROR_STACK_OVERFLOW;
        }
    }
    else{
       return RPN_ERROR_INVALID_TOKEN;
                                                                         
    }  
    token= strtok(NULL, " ");
        }
StackPop(&stack, &integer);
integer=*result;
return RPN_NO_ERROR;       
}


int ProcessBackspaces(char *rpn_sentence){
    struct Stack stack = {};
    char *token; 
    double simple;
    StackInit(&stack);
    token = strtok(rpn_sentence, "\b");
    while (token != NULL){
        if (strcmp(token, "\b") ==0){
            StackPop(&stack, &simple);
        }else{
            StackPush(&stack, atof(token));
            
        }
        return sizeof(&stack);
    }
}








