// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"
#include "Leds_Lab06.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Ascii.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
#define Atime 2*38
#define Btime 3*38
#define Ctime 5*38
// **** Declare function prototypes ****
static struct Timer firstTime;
static struct Timer secondTime;
static struct Timer thirdTime;
int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to Hagos's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);
    LEDS_INIT();
    firstTime.timeRemaining=Atime;
    firstTime.event = FALSE;
    secondTime.timeRemaining=Btime;
    secondTime.event = FALSE;
    thirdTime.timeRemaining=Ctime;
    thirdTime.event = FALSE;
    

    while (1) {
        if (firstTime.event) {
            firstTime.event =FALSE;
            printf("A");
            LEDS_SET(0x01);
        }
        if (secondTime.event) {
            secondTime.event =FALSE;
            printf("B");
            LEDS_SET(0x02);
        }
        if (thirdTime.event) {
            thirdTime.event =FALSE;
            printf("C");
            LEDS_SET(0x04);
        }
        
        
        //poll timer A
            //react to timer A events
            //clear timer A event flag
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    firstTime.timeRemaining--;
    secondTime.timeRemaining--;
    thirdTime.timeRemaining--;
    
    //update timerA
    //if timerA has counted down,
    if (firstTime.timeRemaining==0){
        firstTime.event=TRUE;
        firstTime.timeRemaining=Atime;
    }
        //generate timerA event
        //reset timerA
    if (secondTime.timeRemaining==0){
        secondTime.event=TRUE;
        secondTime.timeRemaining=Btime;
    }
    
    if (thirdTime.timeRemaining==0){
        thirdTime.event=TRUE;
        thirdTime.timeRemaining=Ctime;
    }
    
    
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}