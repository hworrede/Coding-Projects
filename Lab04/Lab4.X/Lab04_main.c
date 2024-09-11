// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to Hagos's RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("Enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        
        int err =RPN_Evaluate(rpn_sentence, &result);
        if (err == RPN_ERROR_STACK_OVERFLOW) {
            printf("ERROR: no more on the stack.\n");
        }else if (err==RPN_ERROR_INVALID_TOKEN) {
            printf("ERROR: RPN string had invalid character.\n");
        }else if (err==RPN_ERROR_DIVIDE_BY_ZERO){
            printf("ERROR: can't divide by zero.\n");
        }else if (err==RPN_ERROR_TOO_FEW_ITEMS_REMAIN || err==RPN_ERROR_TOO_MANY_ITEMS_REMAIN ){
            printf("ERROR: Invalid RPN Calculation.\n");
        }else{
            printf("result = %f\n",result);
        }

    }

    while (1);
    
}
