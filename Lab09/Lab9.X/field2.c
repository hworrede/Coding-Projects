// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

//CE13 standard libraries:
#include "Buttons.h"
#include "Uart1.h"
#include "Oled.h"

// Battleboats Libraries:
#include "BattleBoats.h"
#include "Agent.h"
#include "Negotiation.h"
#include "Message.h"
#include "Field.h"


// Define functions

/**
 * FieldInit() will initialize two passed field structs for the beginning of play.
 * Each field's grid should be filled with the appropriate SquareStatus (
 * FIELD_SQUARE_EMPTY for your own field, FIELD_SQUARE_UNKNOWN for opponent's).
 * Additionally, your opponent's field's boatLives parameters should be filled
 *  (your own field's boatLives will be filled when boats are added)
 * 
 * FieldAI_PlaceAllBoats() should NOT be called in this function.
 * 
 * @param own_field     //A field representing the agents own ships
 * @param opp_field     //A field representing the opponent's ships
 */
void FieldInit(Field *own_field, Field * opp_field) {
    int own_row, own_col;
    for (own_row = 0; own_row < FIELD_ROWS - 1; own_row++) {
        for (own_col = 0; own_col < FIELD_COLS - 1; own_col++) {
            own_field->grid[own_row][own_col] = FIELD_SQUARE_EMPTY;
        }
    }

    int opp_row, opp_col;
    for (opp_row = 0; opp_row < FIELD_ROWS - 1; opp_row++) {
        for (opp_col = 0; opp_col < FIELD_COLS - 1; opp_col++) {
            opp_field->grid[opp_row][opp_col] = FIELD_SQUARE_UNKNOWN;
        }
    }
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE; //I did this because it says that each boat's size is the how many lives the boat has
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;

    own_field->hugeBoatLives = 0;
    own_field->largeBoatLives = 0;
    own_field->mediumBoatLives = 0;
    own_field->smallBoatLives = 0;
}

/**
 * Retrieves the value at the specified field position.
 * @param f     //The Field being referenced
 * @param row   //The row-component of the location to retrieve
 * @param col   //The column-component of the location to retrieve
 * @return  FIELD_SQUARE_INVALID if row and col are not valid field locations
 *          Otherwise, return the status of the referenced square 
 */
SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col) {
    if ((row < 0) || (row > FIELD_ROWS - 1)) {
        return FIELD_SQUARE_INVALID;
    }
    if ((col < 0 || col > FIELD_ROWS - 1)) {
        return FIELD_SQUARE_INVALID;
    }

    return f->grid[row][col];
}

/**
 * This function provides an interface for setting individual locations within a Field struct. This
 * is useful when FieldAddBoat() doesn't do exactly what you need. For example, if you'd like to use
 * FIELD_SQUARE_CURSOR, this is the function to use.
 * 
 * @param f The Field to modify.
 * @param row The row-component of the location to modify
 * @param col The column-component of the location to modify
 * @param p The new value of the field location
 * @return The old value at that field location
 */
SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p) {
    SquareStatus old_val = f->grid[row][col];
    f->grid[row][col] = p;
    return old_val;
}
/**
 * FieldAddBoat() places a single ship on the player's field based on arguments 2-5. Arguments 2, 3
 * represent the x, y coordinates of the pivot point of the ship.  Argument 4 represents the
 * direction of the ship, and argument 5 is the length of the ship being placed. 
 * 
 * All spaces that
 * the boat would occupy are checked to be clear before the field is modified so that if the boat
 * can fit in the desired position, the field is modified as SUCCESS is returned. Otherwise the
 * field is unmodified and STANDARD_ERROR is returned. There is no hard-coded limit to how many
 * times a boat can be added to a field within this function.
 * 
 * In addition, this function should update the appropriate boatLives parameter of the field.
 *
 * So this is valid test code:
 * {
 *   Field myField;
 *   FieldInit(&myField,FIELD_SQUARE_EMPTY);
 *   FieldAddBoat(&myField, 0, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_SMALL);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_MEDIUM);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_HUGE);
 *   FieldAddBoat(&myField, 0, 6, FIELD_BOAT_DIRECTION_SOUTH, FIELD_BOAT_TYPE_SMALL);
 * }
 *
 * should result in a field like:
 *      0 1 2 3 4 5 6 7 8 9
 *     ---------------------
 *  0 [ 3 3 3 . . . 3 . . . ]
 *  1 [ 4 4 4 4 . . 3 . . . ]
 *  2 [ . . . . . . 3 . . . ]
 *  3 [ . . . . . . . . . . ]
 *  4 [ . . . . . . . . . . ]
 *  5 [ . . . . . . . . . . ]
 *     
 * @param f The field to grab data from.
 * @param row The row that the boat will start from, valid range is from 0 and to FIELD_ROWS - 1.
 * @param col The column that the boat will start from, valid range is from 0 and to FIELD_COLS - 1.
 * @param dir The direction that the boat will face once places, from the BoatDirection enum.
 * @param boatType The type of boat to place. Relies on the FIELD_SQUARE_*_BOAT values from the
 * SquareStatus enum.
 * @return SUCCESS for success, STANDARD_ERROR for failure
 */
uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type) {

    if ((dir != FIELD_DIR_SOUTH) && (dir != FIELD_DIR_EAST)) {
        return STANDARD_ERROR;
    }
    if ((boat_type != FIELD_BOAT_TYPE_SMALL) && (boat_type != FIELD_BOAT_TYPE_MEDIUM) &&
            (boat_type != FIELD_BOAT_TYPE_LARGE) && (boat_type != FIELD_BOAT_TYPE_HUGE)) {
        return STANDARD_ERROR;
    }

    //make check to make sure not on bottom if row is not last row or row not 

    // base it off direction if south use columns or rows   
    int small_row;
    if (boat_type == FIELD_BOAT_TYPE_SMALL) {
        if (dir == FIELD_DIR_EAST) {
            for (small_row = 0; small_row < 3; small_row++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row][col + small_row] = FIELD_SQUARE_SMALL_BOAT;
                    own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                }
            }
        }
    }
    int small_col;
    if (boat_type == FIELD_BOAT_TYPE_SMALL) {
        if (dir == FIELD_DIR_SOUTH) {
            for (small_col = 0; small_col < 3; small_col++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row + small_col][col] = FIELD_SQUARE_SMALL_BOAT;
                    own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                }
            }
        }
    }

    int medium_row;
    if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
        if (dir == FIELD_DIR_EAST) {
            for (medium_row = 0; medium_row < 4; medium_row++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row][col + small_row] = FIELD_SQUARE_MEDIUM_BOAT;
                    own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                }
            }
        }
    }
    int medium_col;
    if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
        if (dir == FIELD_DIR_SOUTH) {
            for (medium_col = 0; medium_col < 4; medium_col++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row + small_col][col] = FIELD_SQUARE_MEDIUM_BOAT;
                    own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                }
            }
        }
    }

    int large_row;
    if (boat_type == FIELD_BOAT_TYPE_LARGE) {
        if (dir == FIELD_DIR_EAST) {
            for (large_row = 0; large_row < 5; large_row++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row][col + small_row] = FIELD_SQUARE_LARGE_BOAT;
                    own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
                }
            }
        }
    }
    int large_col;
    if (boat_type == FIELD_BOAT_TYPE_LARGE) {
        if (dir == FIELD_DIR_SOUTH) {
            for (large_col = 0; large_col < 5; large_col++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row + small_col][col] = FIELD_SQUARE_LARGE_BOAT;
                    own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
                }
            }
        }
    }

    int huge_row;
    if (boat_type == FIELD_BOAT_TYPE_HUGE) {
        if (dir == FIELD_DIR_EAST) {
            for (huge_row = 0; huge_row < 6; huge_row++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row][col + small_row] = FIELD_SQUARE_HUGE_BOAT;
                    own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
                }
            }
        }
    }
    int huge_col;
    if (boat_type == FIELD_BOAT_TYPE_HUGE) {
        if (dir == FIELD_DIR_SOUTH) {
            for (huge_col = 0; huge_col < 6; huge_col++) {
                if (FieldGetSquareStatus(own_field, row, col) == FIELD_SQUARE_INVALID) {
                    return STANDARD_ERROR;
                }
                if (own_field->grid[row][col] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } else {
                    own_field->grid[row + small_col][col] = FIELD_SQUARE_HUGE_BOAT;
                    own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
                }
            }
        }
    }

    return SUCCESS;
}

/**
 * This function registers an attack at the gData coordinates on the provided field. This means that
 * 'f' is updated with a FIELD_SQUARE_HIT or FIELD_SQUARE_MISS depending on what was at the
 * coordinates indicated in 'gData'. 'gData' is also updated with the proper HitStatus value
 * depending on what happened AND the value of that field position BEFORE it was attacked. Finally
 * this function also reduces the lives for any boat that was hit from this attack.
 * @param f The field to check against and update.
 * @param gData The coordinates that were guessed. The result is stored in gData->result as an
 *               output.  The result can be a RESULT_HIT, RESULT_MISS, or RESULT_***_SUNK.
 * @return The data that was stored at the field position indicated by gData before this attack.
 */
SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess) {

    SquareStatus opp_square_stat = FieldGetSquareStatus(own_field, opp_guess->row, opp_guess->col);

    if ((opp_square_stat == FIELD_SQUARE_SMALL_BOAT)) {
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_MISS) {
            return RESULT_MISS;
        }
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_HIT) {
            if (own_field->smallBoatLives == 0) {
                return RESULT_SMALL_BOAT_SUNK;
            } else {
                own_field->smallBoatLives--;
                return RESULT_HIT;
            }
        }
    }

    if ((opp_square_stat == FIELD_SQUARE_MEDIUM_BOAT)) {
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_MISS) {
            return RESULT_MISS;
        }
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_HIT) {
            if (own_field->mediumBoatLives == 0) {
                return RESULT_MEDIUM_BOAT_SUNK;
            } else {
                own_field->mediumBoatLives--;
                return RESULT_HIT;
            }
        }
    }

    if ((opp_square_stat == FIELD_SQUARE_LARGE_BOAT)) {
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_MISS) {
            return RESULT_MISS;
        }
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_HIT) {
            if (own_field->largeBoatLives == 0) {
                return RESULT_LARGE_BOAT_SUNK;
            } else {
                own_field->largeBoatLives--;
                return RESULT_HIT;
            }
        }
    }

    if ((opp_square_stat == FIELD_SQUARE_HUGE_BOAT)) {
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_MISS) {
            return RESULT_MISS;
        }
        if (own_field->grid[opp_guess->row][opp_guess->col] == RESULT_HIT) {
            if (own_field->hugeBoatLives == 0) {
                return RESULT_HUGE_BOAT_SUNK;
            } else {
                own_field->hugeBoatLives--;
                return RESULT_HIT;
            }
        }
    }
    return own_field->grid[opp_guess->row][opp_guess->col];
}

/**
 * This function updates the FieldState representing the opponent's game board with whether the
 * guess indicated within gData was a hit or not. If it was a hit, then the field is updated with a
 * FIELD_SQUARE_HIT at that position. If it was a miss, display a FIELD_SQUARE_EMPTY instead, as
 * it is now known that there was no boat there. The FieldState struct also contains data on how
 * many lives each ship has. Each hit only reports if it was a hit on any boat or if a specific boat
 * was sunk, this function also clears a boats lives if it detects that the hit was a
 * RESULT_*_BOAT_SUNK.
 * @param f The field to grab data from.
 * @param gData The coordinates that were guessed along with their HitStatus.
 * @return The previous value of that coordinate position in the field before the hit/miss was
 * registered.
 */


SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess){
    
    
    SquareStatus own_square_stat = FieldGetSquareStatus(opp_field, own_guess->row, own_guess->col);


    if ((own_square_stat == FIELD_SQUARE_SMALL_BOAT)) {
        if (opp_field->smallBoatLives == 0) {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_SMALL_BOAT_SUNK;
        } else {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_HIT;
        }
    } else {
        opp_field->grid[own_guess->row][own_guess->col] = RESULT_MISS;
    }
    
    if ((own_square_stat == FIELD_SQUARE_MEDIUM_BOAT)) {
        if (opp_field->mediumBoatLives == 0) {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_MEDIUM_BOAT_SUNK;
        } else {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_HIT;
        }
    } else {
        opp_field->grid[own_guess->row][own_guess->col] = RESULT_MISS;
    }
    
    if ((own_square_stat == FIELD_SQUARE_LARGE_BOAT)) {
        if (opp_field->largeBoatLives == 0) {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_LARGE_BOAT_SUNK;
        } else {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_HIT;
        }
    } else {
        opp_field->grid[own_guess->row][own_guess->col] = RESULT_MISS;
    }
    
    if ((own_square_stat == FIELD_SQUARE_HUGE_BOAT)) {
        if (opp_field->hugeBoatLives == 0) {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_HUGE_BOAT_SUNK;
        } else {
            opp_field->grid[own_guess->row][own_guess->col] = RESULT_HIT;
        }
    } else {
        opp_field->grid[own_guess->row][own_guess->col] = RESULT_MISS;
    }
    
    return own_square_stat;
}


/////////////////////////////////////////////////////////


uint8_t FieldGetBoatStates(const Field *f){
    
    if((f->smallBoatLives > 0) && (f->mediumBoatLives > 0) && (f->largeBoatLives) && (f->hugeBoatLives)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_MEDIUM | FIELD_BOAT_STATUS_LARGE | FIELD_BOAT_STATUS_HUGE;
    }else if((f->smallBoatLives > 0) && (f->mediumBoatLives > 0) && (f->largeBoatLives)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_MEDIUM | FIELD_BOAT_STATUS_LARGE;
    }else if((f->smallBoatLives > 0) && (f->mediumBoatLives > 0) && (f->hugeBoatLives)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_MEDIUM | FIELD_BOAT_STATUS_HUGE;
    }else if((f->smallBoatLives > 0) && (f->largeBoatLives > 0) && (f->hugeBoatLives)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_LARGE | FIELD_BOAT_STATUS_HUGE;
    }else if((f->mediumBoatLives > 0) && (f->largeBoatLives > 0) && (f->hugeBoatLives)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_LARGE | FIELD_BOAT_STATUS_HUGE;
    }else if((f->smallBoatLives > 0) && (f->mediumBoatLives > 0)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_MEDIUM;
    }else if((f->smallBoatLives > 0) && (f->largeBoatLives > 0)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_LARGE;
    }else if((f->smallBoatLives > 0) && (f->hugeBoatLives > 0)){
        return FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_HUGE;
    }else if((f->mediumBoatLives > 0) && (f->largeBoatLives > 0)){
        return FIELD_BOAT_STATUS_MEDIUM | FIELD_BOAT_STATUS_LARGE;
    }else if((f->mediumBoatLives > 0) && (f->hugeBoatLives > 0)){
        return FIELD_BOAT_STATUS_MEDIUM | FIELD_BOAT_STATUS_HUGE;
    }else if((f->largeBoatLives > 0) && (f->hugeBoatLives > 0)){
        return FIELD_BOAT_STATUS_LARGE | FIELD_BOAT_STATUS_HUGE;
    }else if(f->smallBoatLives > 0){
        return FIELD_BOAT_STATUS_SMALL;
    }else if(f->mediumBoatLives > 0){
        return FIELD_BOAT_STATUS_MEDIUM;
    }else if(f->largeBoatLives > 0){
        return FIELD_BOAT_STATUS_LARGE;
    }else if(f->hugeBoatLives > 0){
        return FIELD_BOAT_STATUS_HUGE;
    }
    return 0x00;
}


/**
 * This function is responsible for placing all four of the boats on a field.
 * 
 * @param f         //agent's own field, to be modified in place.
 * @return SUCCESS if all boats could be placed, STANDARD_ERROR otherwise.
 * 
 * This function should never fail when passed a properly initialized field!
 */
uint8_t FieldAIPlaceAllBoats(Field *own_field){
    int boat_count = 0;
    int own_row_small = rand() % FIELD_ROWS;
    int own_col_small = rand() % FIELD_COLS;
    int own_dir_small;
    if (FIELD_DIR_SOUTH^FIELD_DIR_EAST) {
        own_dir_small = FIELD_DIR_SOUTH;
    }else {
        own_dir_small = FIELD_DIR_EAST;
    }
    FieldAddBoat(own_field,own_row_small, own_col_small, own_dir_small, FIELD_BOAT_TYPE_SMALL);
    boat_count++;
    int own_row_medium = rand() % FIELD_ROWS;
    int own_col_medium = rand() % FIELD_COLS;
    int own_dir_medium;
    if (FIELD_DIR_SOUTH^FIELD_DIR_EAST) {
        own_dir_medium = FIELD_DIR_SOUTH;
    }else {
        own_dir_medium = FIELD_DIR_EAST;
    }
    FieldAddBoat(own_field,own_row_medium, own_col_medium, own_dir_medium, FIELD_BOAT_TYPE_MEDIUM);
    boat_count++;
    int own_row_large = rand() % FIELD_ROWS;
    int own_col_large = rand() % FIELD_COLS;
    int own_dir_large;
    if (FIELD_DIR_SOUTH^FIELD_DIR_EAST) {
        own_dir_large = FIELD_DIR_SOUTH;
    }else {
        own_dir_large = FIELD_DIR_EAST;
    }
    FieldAddBoat(own_field,own_row_large, own_col_large, own_dir_large, FIELD_BOAT_TYPE_LARGE);
    boat_count++;
    int own_row_huge = rand() % FIELD_ROWS;
    int own_col_huge = rand() % FIELD_COLS;
    int own_dir_huge;
    if (FIELD_DIR_SOUTH^FIELD_DIR_EAST) {
       own_dir_huge = FIELD_DIR_SOUTH;
    }else {
       own_dir_huge = FIELD_DIR_EAST;
    }
    FieldAddBoat(own_field,own_row_huge, own_col_huge, own_dir_huge, FIELD_BOAT_TYPE_HUGE);
    boat_count++;
    if(boat_count == 4){
        return SUCCESS;
    }
    else{
        return STANDARD_ERROR;
    }
    
}

/**
 * Given a field, decide the next guess.
 *
 * This function should not attempt to shoot a square which has already been guessed.
 *
 * You may wish to give this function static variables.  If so, that data should be
 * reset when FieldInit() is called.
 * 
 * @param f an opponent's field.
 * @return a GuessData struct whose row and col parameters are the coordinates of the guess.  The 
 *           result parameter is irrelevant.
 */
GuessData FieldAIDecideGuess(const Field *opp_field){
    
    GuessData guess; 
    guess.row = rand() % FIELD_ROWS;
    guess.col = rand() % FIELD_COLS;

    SquareStatus opp_square_stat = FieldGetSquareStatus(opp_field, guess.row, guess.col);
    
    if((opp_square_stat == FIELD_SQUARE_MISS) || (opp_square_stat == FIELD_SQUARE_HIT)){
        FieldAIDecideGuess(opp_field);
    }
    else{
        return guess;
    }
    
    
    
    GuessData FieldAIDecideGuess(const Field *opp_field){
    
    GuessData finalguess; 
    finalguess.col = rand() % FIELD_COLS;
    finalguess.row = rand() % FIELD_ROWS;
    

    SquareStatus statusofenemy = FieldGetSquareStatus(opp_field, finalguess.row, finalguess.col);
    
    if((statusofenemy == FIELD_SQUARE_HIT) || (statusofenemy == FIELD_SQUARE_MISS)){
        FieldAIDecideGuess(opp_field);
    }
    else
    {
        return finalguess;
    }
}