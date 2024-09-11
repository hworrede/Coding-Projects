// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <math.h>


//CSE013E Support Library
#include "UNIXBOARD.h"

// User libraries
#include "Player.h"



// **** Define any global or external variables here ****
static int finalplayerinventory[INVENTORY_SIZE];
static int finalcurrentinventory = 0;

// **** Function Definitions **** //
int AddToInventory(uint8_t item) {
    if (0 <= finalcurrentinventory < INVENTORY_SIZE) {
        finalplayerinventory[finalcurrentinventory] = item;
        finalcurrentinventory += 1;
        return SUCCESS;
    }
    else {
        return STANDARD_ERROR;
    }
}

int FindInInventory(uint8_t item) {
    int finalitemlist = 0;
    for (int i = 0; i < sizeof(finalplayerinventory); i++) {
        if (finalplayerinventory[i] == item) {
            finalitemlist = 1;
            break;
        }
    }
    if (finalitemlist == 1) {
        return SUCCESS;
    }
    else {
        return STANDARD_ERROR;
    }
}