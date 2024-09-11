// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <math.h>


//CSE013E Support Library
#include "UNIXBOARD.h"

// User libraries
#include "Game.h"
#include "Player.h"



// **** Define any global or external variables here ****
typedef struct {
    uint16_t itemReq;
    uint16_t itemCont;
    uint16_t West_exit;
    uint16_t East_exit;
    uint16_t North_exit;
    uint16_t South_exit;
   
    char thetitle_game[GAME_MAX_ROOM_TITLE_LENGTH];
    char thedesc_game[GAME_MAX_ROOM_DESC_LENGTH];
} GameInfo;

static GameInfo final_game;

int parseNewRoom(int roomNumber) {
    char str[80];
    uint8_t list = 1;
    sprintf(str, "RoomFiles/room%d.txt", roomNumber);
    FILE * second = fopen(str, "rb");
    fseek(second, 3, SEEK_SET);
    
    int measurement;
    
    measurement = fgetc(second);
    fread(final_game.thetitle_game, measurement, 1, second);
    final_game.thetitle_game[measurement] = '0';
    
    if(list == 1) {
        int item_measure = fgetc(second);
        for (int i = 0; i < item_measure; i++) {
            if(FindInInventory(fgetc(second)) != 1) {
                list = 0;
            }
        }
        int Length_desc_first = fgetc(second);
        fread(final_game.thedesc_game, Length_desc_first, 1, second);
        final_game.thedesc_game[Length_desc_first] = '\0';
        int item_Length_sec = fgetc(second);
        
        for (int j = 0; j < item_Length_sec; j++) {
            uint8_t next_list = fgetc(second);
            if(FindInInventory(next_list) != 1) {
                if(AddToInventory(next_list)  != 1) {
                    return STANDARD_ERROR;
                }
            }
        }
        final_game.West_exit = fgetc(second);
        final_game.East_exit = fgetc(second);
        final_game.North_exit = fgetc(second);
        final_game.South_exit = fgetc(second);
        
        
       
    }
    else if (list==0){
        int item_measure = fgetc(second);
        for (int i = 0; i < item_measure; i++) {
            if(FindInInventory(fgetc(second)) != 1) {
                return STANDARD_ERROR;
            }
        }
        int Length_desc_first = fgetc(second);
        fread(final_game.thedesc_game, Length_desc_first, 1, second);
        final_game.thedesc_game[Length_desc_first]='\0';
        int item_Length_sec = fgetc(second);
        
        for (int j = 0; j < item_Length_sec; j++) {
            uint8_t next_list = fgetc(second);
            if(FindInInventory(next_list) != 1) {
                if(AddToInventory(next_list)  != 1) {
                    return STANDARD_ERROR;
                }
            }
        }
        final_game.North_exit = fgetc(second);
        final_game.East_exit = fgetc(second);
        final_game.South_exit = fgetc(second);
        final_game.West_exit = fgetc(second);
    }
    
}

// ***West, East, North, South***/

int GameGoWest(void) {
    if (parseNewRoom(final_game.West_exit) == STANDARD_ERROR) {
        return STANDARD_ERROR;
    }
    else 
    {
        return SUCCESS;
    }
}

int GameGoEast(void) {
    if (parseNewRoom(final_game.East_exit) == STANDARD_ERROR) {
            return STANDARD_ERROR;
        }
        else 
        {
            return SUCCESS;
        }
}

int GameGoNorth(void){
    if (parseNewRoom(final_game.North_exit) == STANDARD_ERROR) {
        return STANDARD_ERROR;
    }
    else 
    {
        return SUCCESS;
    }
}

int GameGoSouth(void){
    if (parseNewRoom(final_game.South_exit) == STANDARD_ERROR) {
        return STANDARD_ERROR;
    }
    else 
    {
        return SUCCESS;
    }
}




/**
 * GameInit function
 */
int GameInit(void) {
    if (parseNewRoom(STARTING_ROOM) == STANDARD_ERROR) {
        return STANDARD_ERROR;
    }
    else 
    {
        return SUCCESS;
    }
}

/**
 * GameGetCurrentRoomTitle function
 */
int GameGetCurrentRoomTitle(char *title) {
    strcpy(title,final_game.thetitle_game);
    return (strlen(title) + 1);
}

/**
 * GameGetCurrentRoomDescription function
 */
int GameGetCurrentRoomDescription(char *desc) {
    strcpy(desc,final_game.thedesc_game);;
    return (strlen(desc) + 1);
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void) {
    uint8_t direction = 0;
    if(final_game.West_exit) {
        direction += GAME_ROOM_EXIT_WEST_EXISTS;
    }
    if (final_game.East_exit) {
        direction += GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (final_game.North_exit) {
        direction += GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    
    if (final_game.South_exit) {
        direction += GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    
    return direction;
}