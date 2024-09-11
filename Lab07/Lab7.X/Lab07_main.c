// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

//User Libraries
#include "Adc.h"
#include "OledDriver.h"
#include "Oled.h"
#include "Ascii.h"
#include "Leds.h"
#include "Buttons.h"






// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)


// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    BAKE = 1, TOAST = 2, BROIL = 3
} OvenMode;

typedef struct {
    OvenState state;
    //add more members to this struct
    OvenMode mode;
    uint16_t timingleft;
    uint16_t finaltemp;
    uint16_t firstTime;
    uint16_t correcttemp;
    uint16_t firstpress;


} OvenData;


// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
static OvenData Oven;
//
//static Event currentEvent;
static uint16_t delayed;
static uint16_t changingadc;
static uint16_t value;
static uint16_t check_button;
static uint16_t Stateremain;
static uint16_t ticking;
static uint16_t interval;
static uint16_t counting;
static int runningtime;
static int stateNum;
static int count_minutes;
static int count_seconds;




#define LONG_PRESS 5

// **** Put any helper functions here ****

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData) {
    //update OLED here
    char str[80];
    if (ovenData.mode == BAKE & ovenData.state == SETUP) {
        if (ovenData.finaltemp == 1) {
            sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     |  Time: %d:%.02d\n|-----| >Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, count_minutes, count_seconds, ovenData.correcttemp, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        } else {
            //editing the temp with the enum
            sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     | >Time: %d:%.02d\n|-----|  Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, count_minutes, count_seconds, ovenData.correcttemp, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        }
    }
    if (ovenData.mode == BAKE & ovenData.state == COOKING) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     |  Time: %d:%.02d\n|-----|  Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, count_minutes, count_seconds, ovenData.correcttemp, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == TOAST & ovenData.state == SETUP) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: TOAST\n|     |  Time: %d:%.02d\n|-----|  \n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, count_minutes, count_seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    if (ovenData.mode == TOAST & ovenData.state == COOKING) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: TOAST\n|     |  Time: %d:%.02d\n|-----| \n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, count_minutes, count_seconds, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == BROIL & ovenData.state == SETUP) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: BROIL\n|     |  Time: %d:%.02d\n|-----|  Temp: 500\n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, count_minutes, count_seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    if (ovenData.mode == BROIL & ovenData.state == COOKING) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: BROIL\n|     |  Time: %d:%.02d\n|-----|  Temp: 500\n|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, count_minutes, count_seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    if (ovenData.mode == BAKE & ovenData.state == RESET_PENDING) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     |  Time: %d:%.02d\n|-----|  Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, count_minutes, count_seconds, ovenData.correcttemp, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == TOAST & ovenData.state == RESET_PENDING) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: TOAST\n|     |  Time: %d:%.02d\n|-----|  \n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, count_minutes, count_seconds, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == BROIL & ovenData.state == RESET_PENDING) {
        //editing the temp with the enum
        sprintf(str, "|%s%s%s%s%s|  Mode: BROIL\n|     |  Time: %d:%.02d\n|-----|  Temp: 500\n|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, count_minutes, count_seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(str);
    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) {
    //The Oven mode code for the instance
    switch (Oven.state) {
        case SETUP:
            if (Oven.mode == BAKE) {
                if (check_button & BUTTON_EVENT_3DOWN) {
                    Oven.firstpress = runningtime;
                    Stateremain = SETUP;
                    Oven.state = SELECTOR_CHANGE_PENDING;
                }
                if (check_button & BUTTON_EVENT_4DOWN) {
                    LEDS_SET(0xff);
                    Oven.timingleft = Oven.firstTime;
                    Oven.firstpress = runningtime;
                    Oven.state = COOKING;
                    Stateremain = COOKING;

                }
                if (Oven.finaltemp) {
                    Oven.correcttemp = (AdcRead() >> 2) + 300;
                } else {
                    Oven.firstTime = (AdcRead() >> 2) + 1;
                    count_minutes = Oven.firstTime / 60;
                    count_seconds = Oven.firstTime % 60;
                }
            } else if (Oven.mode == TOAST) {
                if (check_button & BUTTON_EVENT_3DOWN) {
                    Oven.firstpress = runningtime;
                    Stateremain = SETUP;
                    Oven.state = SELECTOR_CHANGE_PENDING;
                }
                if (check_button & BUTTON_EVENT_4DOWN) {
                    LEDS_SET(0xff);
                    Oven.firstpress = runningtime;
                    Oven.state = COOKING;
                    Stateremain = COOKING;
                }
                Oven.firstTime = (AdcRead() >> 2) + 1;
                count_minutes = Oven.firstTime / 60;
                count_seconds = Oven.firstTime % 60;
            } else if (Oven.mode == BROIL) {
                if (check_button & BUTTON_EVENT_3DOWN) {
                    Oven.firstpress = runningtime;
                    Stateremain = SETUP;
                    Oven.state = SELECTOR_CHANGE_PENDING;
                }
                if (check_button & BUTTON_EVENT_4DOWN) {
                    LEDS_SET(0xff);
                    Oven.firstpress = runningtime;
                    Oven.state = COOKING;
                    Stateremain = COOKING;
                }
                Oven.firstTime = (AdcRead() >> 2) + 1;
                count_minutes = Oven.firstTime / 60;
                count_seconds = Oven.firstTime % 60;
            }
            Oven.timingleft = Oven.firstTime;
            
        case SELECTOR_CHANGE_PENDING:
            //The case for the change in the pending
        {
            if (check_button & BUTTON_EVENT_3UP) {
                delayed = runningtime - Oven.firstpress;
                if (delayed >= LONG_PRESS) {
                    printf("%d", delayed);
                    printf("hi :)");
                    if (Oven.finaltemp == 0) {
                        Oven.finaltemp = 1;
                    } else {
                        Oven.finaltemp = 0;
                    }
                } else if (delayed < LONG_PRESS) {
                    if (Oven.mode < 3) {
                        Oven.mode += 1;
                        printf("%d", Oven.mode);
                    } else {
                        Oven.mode = 1;
                    }
                }
            }
            Oven.state = Stateremain;
        }
            
        case COOKING:
            // case for the cooking mode
            if (ticking) {
                //oven off calculate minutes to seconds, "firsttime". Oven On calculates minutes to seconds, "timingleft"

                if (Oven.timingleft > 0) {
                    Oven.timingleft -= 1;
                    if (((runningtime - Oven.timingleft) % 5) == 0) {
                        if ((interval % Oven.firstTime) == 0) {
                            LEDS_SET(LEDS_GET() << 1);

                        }
                        //Oven.timingleft--;
                        interval -= 8;
                    }
                    count_minutes = Oven.timingleft / 60;
                    count_seconds = Oven.timingleft % 60;

                } else {
                    LEDS_SET(0x00);
                    Oven.state = SETUP;
                    Stateremain = Oven.state;
                    updateOvenOLED(Oven);
                }
            }
            if (check_button & BUTTON_EVENT_4DOWN) {
                Oven.firstpress = runningtime;
                Oven.state = RESET_PENDING;
                Stateremain = COOKING;
            }
            
        case RESET_PENDING:
            //case for the reset of the pending
            if (check_button & BUTTON_EVENT_4UP) {
                delayed = runningtime - Oven.firstpress;
                if (delayed >= LONG_PRESS) {
                    LEDS_SET(0x00);
                    Oven.state = SETUP;
                    Stateremain = Oven.state;
                } else if (delayed < LONG_PRESS) {
                    LEDS_SET(0x00);
                    Oven.timingleft = Oven.firstTime;
                    Oven.state = COOKING;
                }
            }
    }

    updateOvenOLED(Oven);
}

int main() {
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to hworrede's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    OledInit();
    AdcInit();
    ButtonsInit();
    LEDS_INIT();
    Oven.mode = BAKE;
    Oven.state = SETUP;
    Oven.finaltemp = 1;
    Oven.firstTime = 0;
    Oven.correcttemp = 0;
    updateOvenOLED(Oven);
    changingadc = FALSE;
    check_button = FALSE;

    while (1) {
        if (ticking == TRUE) {
            runOvenSM();
            ticking = FALSE;
        }
        if (changingadc == TRUE) {
            runOvenSM();
            changingadc = FALSE;
        }
        if (check_button != BUTTON_EVENT_NONE) {
            runOvenSM();
            check_button = FALSE;
        }
        // running the main
    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // ISR for the 50hz
    IFS0CLR = 1 << 12;

    //add event-checking code here

    ticking = TRUE;
    runningtime += 1;
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // ISR for the 100hz
    IFS0CLR = 1 << 8;

    counting++;
    check_button = ButtonsCheckEvents();
    //add event-checking code here
    if (AdcChanged()) {
        changingadc = TRUE;
        value = AdcRead();
    }
}