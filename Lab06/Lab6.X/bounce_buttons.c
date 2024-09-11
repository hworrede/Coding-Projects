// **** Include libraries here ****
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

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Button{
    uint8_t firstevent;
    uint16_t backevent;
};

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
// **** Define global, module-level, or external variables here ****
static struct Button button2;
static struct Timer switch2;

uint8_t buttonstate;
uint8_t replace;
uint8_t figure;



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
    printf("Welcome to Hagos's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    LEDS_INIT();
    ButtonsInit();
    while(1) {
        if (button2.firstevent==TRUE){
            replace = SWITCH_STATES();
            if (replace & SWITCH_STATE_SW1){
            if (buttonstate & BUTTON_EVENT_4UP){
                LEDS_SET(192^LEDS_GET());
            }
            if (buttonstate & BUTTON_EVENT_3UP){
                LEDS_SET(48^LEDS_GET());
            }
            if (buttonstate & BUTTON_EVENT_2UP){
                LEDS_SET(12^LEDS_GET());
            }
            if (buttonstate & BUTTON_EVENT_1UP){
                LEDS_SET(3^LEDS_GET());
            }
            
            
            
            
        }else {
            if (buttonstate & BUTTON_EVENT_1DOWN){
                LEDS_SET(3^LEDS_GET());
            }
            if (buttonstate & BUTTON_EVENT_2DOWN){
                LEDS_SET(12^LEDS_GET());
            }
            if (buttonstate & BUTTON_EVENT_3DOWN){
                LEDS_SET(48^LEDS_GET());
            }
            if (buttonstate & BUTTON_EVENT_4DOWN){
                LEDS_SET(192^LEDS_GET());
            }
        }
            button2.firstevent==FALSE;
        }
    }
    


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    buttonstate = ButtonsCheckEvents();
    if (button2.backevent != buttonstate){
        button2.backevent = buttonstate;
        button2.firstevent = TRUE;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}