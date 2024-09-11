#include <GenericTypeDefs.h>
#include <stdio.h>

#include "BOARD.h"

#include <sys/attribs.h>
#include <xc.h>

#include "Leds_Lab06.h"

void LEDS_INIT(void){
    TRISE = 0x00;
    LATE = 0x00;
}

void LEDS_SET(char newPattern){
    LATE=newPattern;
}

char LEDS_GET(void){
    return LATE;
}