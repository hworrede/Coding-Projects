// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning Hagos's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed");
    } else {
        printf("failed");
    }
    
    printf("Test for StackPush():\n");
    StackPush(&stack, 7);
    if (stack.currentItemIndex == 7) {
        printf("Pushed 5\n");
    } else {
        printf("ERROR\n");
    }
    
    StackPush(&stack, 3);
    if (stack.currentItemIndex == 3) {
        printf("Pushed 3\n");
    } else {
        printf("ERROR\n");
    }
    
    StackPush(&stack, 2);
    if (stack.currentItemIndex == 2) {
        printf("Pushed 2\n");
    } else {
        printf("ERROR\n");
    }

    BOARD_End();
    //test stackInit:
    while (1);
    return 0;
}


