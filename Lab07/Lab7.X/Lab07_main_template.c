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
#include "Ascii.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"





// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)


// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    BAKE=1, TOAST=2, BROIL=3
} OvenMode;

typedef struct {
    OvenState state;
    //add more members to this struct
    OvenMode mode;
    uint16_t baseTime;
    uint16_t temperature;
    uint16_t button_press_time;
    uint16_t cooking_time_left;
    uint16_t editingTemp;
    
} OvenData;


// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
static OvenData Oven;
//
//static Event currentEvent;
static uint16_t adc_change;
static uint16_t adc_value;
static int free_running_timer;
static uint16_t button_check_event;
static uint16_t count;
static uint16_t TimerTick;
static uint16_t elapsedTime;
static int minutes;
static int seconds;
static uint16_t currentState;
static int stateNum;

#define LONG_PRESS 5

// **** Put any helper functions here ****


/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData){
    //update OLED here
    char str[80];
    if (ovenData.mode == BAKE & ovenData.state == SETUP) {
        if(ovenData.editingTemp == 1){
            //print edit temp
           sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     |  Time: %d:%.02d\n|-----| >Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF, minutes, seconds, ovenData.temperature, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        } else {
            //print edit time
           sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     | >Time: %d:%.02d\n|-----|  Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF, minutes, seconds, ovenData.temperature, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        }
    }
    if (ovenData.mode == BAKE & ovenData.state == COOKING) {
        //print edit temp
        sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     |  Time: %d:%.02d\n|-----|  Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON, minutes, seconds, ovenData.temperature, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == TOAST & ovenData.state == SETUP) {
        sprintf(str, "|%s%s%s%s%s|  Mode: TOAST\n|     |  Time: %d:%.02d\n|-----|  \n|%s%s%s%s%s|", OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF, minutes, seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    if (ovenData.mode == TOAST & ovenData.state == COOKING) {
        //print edit temp
        sprintf(str, "|%s%s%s%s%s|  Mode: TOAST\n|     |  Time: %d:%.02d\n|-----| \n|%s%s%s%s%s|", OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF, minutes, seconds, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == BROIL & ovenData.state == SETUP) {
        sprintf(str, "|%s%s%s%s%s|  Mode: BROIL\n|     |  Time: %d:%.02d\n|-----|  Temp: 500\n|%s%s%s%s%s|", OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF, minutes, seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    if (ovenData.mode == BROIL & ovenData.state == COOKING) {
        //print edit temp
        sprintf(str, "|%s%s%s%s%s|  Mode: BROIL\n|     |  Time: %d:%.02d\n|-----|  Temp: 500\n|%s%s%s%s%s|", OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON, minutes, seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    if (ovenData.mode == BAKE & ovenData.state == RESET_PENDING) {
        //print edit temp
        sprintf(str, "|%s%s%s%s%s|  Mode: BAKE\n|     |  Time: %d:%.02d\n|-----|  Temp: %d\n|%s%s%s%s%s|", OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON, minutes, seconds, ovenData.temperature, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == TOAST & ovenData.state == RESET_PENDING) {
        //print edit temp
        sprintf(str, "|%s%s%s%s%s|  Mode: TOAST\n|     |  Time: %d:%.02d\n|-----|  \n|%s%s%s%s%s|", OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF,OVEN_TOP_OFF, minutes, seconds, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
    }
    if (ovenData.mode == BROIL & ovenData.state == RESET_PENDING) {
        //print edit temp
        sprintf(str, "|%s%s%s%s%s|  Mode: BROIL\n|     |  Time: %d:%.02d\n|-----|  Temp: 500\n|%s%s%s%s%s|", OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON,OVEN_TOP_ON, minutes, seconds, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
    }
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(str);
    OledUpdate(); 
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    //write your SM logic here.
    //Oven mode
    switch(Oven.state) {
        case SETUP:
            if (Oven.mode == BAKE) {
                if (button_check_event & BUTTON_EVENT_3DOWN) {
                    Oven.button_press_time = free_running_timer;
                    currentState = SETUP;
                    Oven.state = SELECTOR_CHANGE_PENDING;
                }
                if (button_check_event & BUTTON_EVENT_4DOWN) {
                    Oven.button_press_time = free_running_timer; 
                    Oven.state = COOKING;
                    currentState = COOKING;
                }
                if (Oven.editingTemp) {
                    Oven.temperature = (AdcRead()>>2) + 300;
                }
                else {
                    Oven.baseTime = (AdcRead()>>2) + 1;
                    minutes = Oven.baseTime/60;
                    seconds = Oven.baseTime%60;
                }
            }
            else if (Oven.mode == TOAST) {
                if (button_check_event & BUTTON_EVENT_3DOWN) {
                    Oven.button_press_time = free_running_timer;
                    currentState = SETUP;
                    Oven.state = SELECTOR_CHANGE_PENDING;
                }
                if (button_check_event & BUTTON_EVENT_4DOWN) {
                    Oven.button_press_time = free_running_timer; 
                    Oven.state = COOKING;
                    currentState = COOKING;
                }
                Oven.baseTime = (AdcRead()>>2) + 1;
                minutes = Oven.baseTime/60;
                    seconds = Oven.baseTime%60;
            }  
            else if (Oven.mode == BROIL) {
                if (button_check_event & BUTTON_EVENT_3DOWN) {
                    Oven.button_press_time = free_running_timer;
                    currentState = SETUP;
                    Oven.state = SELECTOR_CHANGE_PENDING;
                }
                if (button_check_event & BUTTON_EVENT_4DOWN) {
                    Oven.button_press_time = free_running_timer;                    
                    Oven.state = COOKING;
                    currentState = COOKING;
                }
                Oven.baseTime = (AdcRead()>>2) + 1;
                minutes = Oven.baseTime/60;
                seconds = Oven.baseTime%60;
            }  
            Oven.cooking_time_left = Oven.baseTime;
        //Mediator mode for selector_change_pending
        case SELECTOR_CHANGE_PENDING: {
            if (button_check_event & BUTTON_EVENT_3UP) {
                        elapsedTime = free_running_timer - Oven.button_press_time;
                        if (elapsedTime >= LONG_PRESS) {
                            printf("%d", elapsedTime);
                            printf("hi :)");
                            if (Oven.editingTemp == 0) {
                                Oven.editingTemp = 1;
                            }
                            else {
                                Oven.editingTemp = 0;
                            }
                        }
                        else if (elapsedTime < LONG_PRESS) {
                            if (Oven.mode < 3) {
                                Oven.mode += 1;
                                printf("%d", Oven.mode);
                            }
                            else {
                                Oven.mode = 1;
                            }
                        }
                    }
            Oven.state = currentState;
        }
        //Cooking mode
        case COOKING:     
            if(TimerTick) {              
                }
                if (Oven.cooking_time_left > 0) {
                    Oven.cooking_time_left -= 1;
                    if (((runningtime - Oven.timingleft) % 5) == 0) {
                        if ((interval % Oven.firstTime) == 0) {
                            LEDS_SET(LEDS_GET() << 1);

                        }
                        Oven.timingleft--;
                        interval -= 8;
                    }
                    minutes = Oven.cooking_time_left/60;
                    seconds = Oven.cooking_time_left%60;
                }
                else {
                    Oven.state = SETUP;
                    currentState = Oven.state;
                }
            if (button_check_event & BUTTON_EVENT_4DOWN) {
                    Oven.button_press_time = free_running_timer;                    
                    Oven.state = RESET_PENDING;
                    currentState = COOKING;
                    }
        //Mediator mode for reset_pending
        case RESET_PENDING:
            if (button_check_event & BUTTON_EVENT_4UP) {
                elapsedTime = free_running_timer - Oven.button_press_time;
                if (elapsedTime >= LONG_PRESS) {
                    Oven.state = SETUP;
                    currentState = Oven.state;
                }
                else if (elapsedTime < LONG_PRESS){                    
                    Oven.cooking_time_left = Oven.baseTime;
                    Oven.state = COOKING;
                }
            }
}

            updateOvenOLED(Oven);
}
    
    


int main()
{
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
   
    printf("Welcome to jrpenlan's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    OledInit();
    AdcInit();
    ButtonsInit();
    LEDS_INIT();
    Oven.mode = BAKE;
    Oven.state = SETUP;
    Oven.editingTemp = 1;
    Oven.baseTime = 0;
    Oven.temperature = 0;
    updateOvenOLED(Oven);
    adc_change = FALSE;
    button_check_event = FALSE;
    
    while (1){
        if(TimerTick == TRUE) {
            runOvenSM();
            TimerTick = FALSE;
        }
        if(adc_change == TRUE) {
            runOvenSM();
            adc_change = FALSE;
        }
        if (button_check_event != BUTTON_EVENT_NONE) {
            runOvenSM();
            button_check_event = FALSE;
        }
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
    };
}


/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here
    
    TimerTick = TRUE;
    free_running_timer += 1;
}


/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    count++;
    button_check_event = ButtonsCheckEvents();
    //add event-checking code here
    if (AdcChanged()) {
        adc_change = TRUE;
        adc_value = AdcRead();
    }
}