
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
					


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

// **** Declare any datatypes here ****
struct time{
    uint8_t event;
    int16_t timeRemaining;
    
};

// **** Define global, module-level, or external variables here ****
struct time timer1;
uint8_t first;
uint8_t last;
#define LED8 0x80
#define LED1 0x01
#define right 1
#define left 0 
static uint8_t lists;


// **** Declare function prototypes ****


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
    printf("Welcome to Hagos's lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    LEDS_INIT();
   	timer1.event=TRUE;
    timer1.timeRemaining=38*2;
	while(1){
        last=LEDS_GET();
        if(timer1.event == TRUE){
            if (LED8 != 0x00){
                LEDS_SET(LEDS_GET()>>1);
                
            }
            if (LED1 != 0x00){
                LEDS_SET(LEDS_GET()<<1);   
            }
            if (last==right){
                LEDS_SET(LEDS_GET()<<1);
                
            }
            if (last== left){
                LEDS_SET(LEDS_GET()>>1);
            }
           
        }
        timer1.event =FALSE;
        //poll timer events and react if any occur
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
    lists= SWITCH_STATES();
    if (lists == 0x00){
        timer1.timeRemaining -= timer1.timeRemaining;
        
    }else{
        timer1.timeRemaining += timer1.timeRemaining;
        
    }
    if (timer1.timeRemaining<=0){
        timer1.event=TRUE;
        timer1.timeRemaining=timer1.timeRemaining;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}