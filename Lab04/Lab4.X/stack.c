// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "stack.h"

void StackInit(struct Stack *stack)
{
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackPush(struct Stack *stack, double value)
{
    if (stack->initialized == FALSE || stack->currentItemIndex == STACK_SIZE){
        return STANDARD_ERROR;
       
    }
    else {
        stack->currentItemIndex += 1;
        stack->stackItems[stack->currentItemIndex]=value;
        return SUCCESS;
}
}

int StackPop(struct Stack *stack, double *value)
{
    if (stack->currentItemIndex != -1){
        *value = stack->stackItems[stack->currentItemIndex];
        stack->currentItemIndex -= 1;
        return SUCCESS;
    }
    else{
        return STANDARD_ERROR;
    }
}

int StackIsEmpty(const struct Stack *stack)
{
    if (stack->initialized == TRUE && stack->currentItemIndex == -1){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int StackIsFull(const struct Stack *stack)
{
    if (stack->currentItemIndex == STACK_SIZE - 1 && stack->initialized == TRUE){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized == FALSE){
        return SIZE_ERROR;
    }
    else{
        return stack->currentItemIndex;
    }
}


