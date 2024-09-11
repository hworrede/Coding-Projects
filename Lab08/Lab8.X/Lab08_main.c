// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"



// User libraries
#include "Game.h"
#include "Player.h"

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
char titlelen[GAME_MAX_ROOM_TITLE_LENGTH + 1];
char desclen[GAME_MAX_ROOM_DESC_LENGTH + 1];
char direction;


// **** Declare any function prototypes here ****

int main()
{



    /******************************** Your custom code goes below here ********************************/

    GameInit();
    
    GameGetCurrentRoomTitle(titlelen);
    printf("%s\n", titlelen);
    
    GameGetCurrentRoomDescription(desclen);
    printf("%s\n", desclen);
    
    while(1) {
        printf("Enter the direction: \n");
        direction = getchar();
        while ((getchar()) != '\n');
            if (direction == 'W' || direction == 'w') {
                GameGoWest();
            }
            if (direction == 'E' || direction == 'e') {
                GameGoEast();
            }
            if (direction == 'N' || direction == 'n') {
                GameGoNorth();
            }
            
            if (direction == 'S' || direction == 's') {
                GameGoSouth();
            }
            
        GameGetCurrentRoomTitle(titlelen);
        printf("%s\n", titlelen);
        GameGetCurrentRoomDescription(desclen); 
        printf("%s\n", desclen);
    }
    

    /**************************************************************************************************/
}


