#include <stdint.h>
#include <genericTypeDefs.h>
#include <stdio.h>
#include <stdlib.h>
#include "Buttons.h"

#include "BOARD.h"
static int bounce;
static int back;




void ButtonsInit(void){
    TRISD|=0x00E0;
    TRISF|=0x0002;
}



uint8_t ButtonsCheckEvents(void){
    
    unsigned int b_state=BUTTON_STATES();
    unsigned int final;
    unsigned int back;
    if (bounce<BUTTONS_DEBOUNCE_PERIOD){
        bounce++;
        return BUTTON_EVENT_NONE;
        
    }
    if ((b_state%BUTTON_STATE_1) && (back!=b_state)){
        final=final | BUTTON_EVENT_1DOWN;
    }
    else if (!(b_state & BUTTON_STATE_1) && (back != b_state)){
        final = final | BUTTON_EVENT_1UP;
    }
    if ((b_state%BUTTON_STATE_2) && (back!=b_state)){
        final=final | BUTTON_EVENT_2DOWN;
    }
    else if (!(b_state & BUTTON_STATE_2) && (back != b_state)){
        final = final | BUTTON_EVENT_2UP;
    }
    if ((b_state%BUTTON_STATE_3) && (back!=b_state)){
        final=final | BUTTON_EVENT_3DOWN;
    }
    else if (!(b_state & BUTTON_STATE_3) && (back != b_state)){
        final = final | BUTTON_EVENT_3UP;
    }
    if ((b_state%BUTTON_STATE_4) && (back!=b_state)){
        final=final | BUTTON_EVENT_4DOWN;
    }
    else if (!(b_state & BUTTON_STATE_4) && (back != b_state)){
        final = final | BUTTON_EVENT_4UP;
    }
    back=b_state;
    return final;
    
}