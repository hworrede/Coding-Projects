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
#include "Leds_Lab06.h"
#include "OledDriver.h"
#include "Oled.h"


// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct AdcResult {
    uint8_t event;
    int16_t direct_vol;
};
// **** Define global, module-level, or external variables here ****
#define ADCMAX 1023
#define WINDOW 5
// **** Declare function prototypes ****
static int percent;
static struct AdcResult meter;
static double recentvalue;


int main(void)
{
    BOARD_Init();

// Enable interrupts for the ADC
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

    // Set B2 to an input so AN2 can be used by the ADC.
    TRISBbits.TRISB2 = 1;

    // Configure and start the ADC
    AD1CHSbits.CH0SA = 2; // add B2 to the mux
    AD1PCFGbits.PCFG2 = 0; // add b2 to the ADC
     AD1CSSLbits.CSSL2 = 1; // and add b2 to the scanner

    AD1CON1 = 0; // start with 0
    AD1CON1bits.SSRC = 0b111; // auto conversion
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0; // start with 0
    AD1CON2bits.SMPI = 7; // one interrupt per 8 samples

    AD1CON3 = 0; // start with 0
    AD1CON3bits.SAMC = 29; // long sample time
    AD1CON3bits.ADCS = 50; // long conversion time
    
    AD1CON1bits.ADON = 1; // and finally turn it on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
  printf("Welcome to Hagos's lab6 part3 (bounce_adc).  Compiled on %s %s.\n",__TIME__,__DATE__);
  OledInit();
  char list[OLED_DRIVER_BUFFER_SIZE];
  meter.event = TRUE;
  while(1)
  {
      if (meter.event == TRUE){
          OledUpdate();
          sprintf(list, "The Potentiometer value:\n%4d\n%3d%", meter.direct_vol, percent);
          OledDrawString(list);
          OledUpdate();
      }
  }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the ADC1 peripheral. It will trigger whenever a new ADC reading is available
 * in the ADC buffer SFRs, ADC1BUF0 - ADC1BUF7.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_ADC_VECTOR, ipl2auto) AdcHandler(void)
{
    // Clear the interrupt flag.
    IFS1bits.AD1IF = 0;
    recentvalue = (ADC1BUF7 + ADC1BUF6 + ADC1BUF4 + ADC1BUF5 + ADC1BUF3 + ADC1BUF1 + ADC1BUF2 + ADC1BUF0)/8;
    if (recentvalue > ADCMAX - WINDOW || recentvalue < WINDOW){
        meter.direct_vol = recentvalue;
        percent = (recentvalue / 1023)*100;
        meter.event= TRUE;
       
    }
    if (recentvalue <meter.direct_vol - WINDOW || recentvalue > meter.direct_vol + WINDOW){
        meter.direct_vol=recentvalue;
        percent = (recentvalue/1023)*100;
        meter.event = TRUE;
    }


}