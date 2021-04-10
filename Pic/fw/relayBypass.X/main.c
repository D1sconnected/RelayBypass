/* 
 * File:   main.c
 * Author: yupdi
 *
 * Created on 3 ?????? 2020 ?., 15:16
 */

// Supplementary libraries
#include <stdint.h>
#include <xc.h>
// Include configuration bits
#include "header.h"

//#define DEBUG_PLATFORM

#ifdef DEBUG_PLATFORM
#define GPIO_LED    RC3
#define GPIO_RELE   RC1
#define GPIO_BUTTON RC2
#define GPIO_PHET   RA2
#else
#define GPIO_LED    RC5
#define GPIO_RELE   RC3
#define GPIO_BUTTON RC4
#define GPIO_PHET   RA2
#endif

volatile uint16_t   btnSwitchCounter = 0;
volatile uint8_t    changeStateFlag = LOW;

uint8_t checkButton ();

void main ()
{
    //ANSEL = 0; // no analog GPIO
    //ADCON0 = 0; // ADC and DAC converters off
#ifdef DEBUG_PLATFORM
    TRISC3 = 0x00; // set RC3 as output
    TRISC1 = 0x00; // set RC1 as output
    TRISC0 = 0x00; // set RC0 as output
    TRISC2 = 0xFF; // set RC2 as input
    TRISA2 = 0x00; // set RA2 as output
#else
    TRISC5 = 0x00; // set RC5 as output
    TRISC3 = 0x00; // set RC3 as output
    TRISC4 = 0xFF; // set RC4 as input
    TRISA2 = 0x00; // set RA2 as output
#endif

    GPIO_LED    = LOW;
    GPIO_RELE   = LOW;
    GPIO_BUTTON = LOW;
    GPIO_PHET   = LOW;

    uint8_t pedalState  = FX_OFF;
    uint8_t buttonState = BUTTON_NOT_PRESSED;

    while (1)
    {
        buttonState = checkButton();
        
        if (buttonState == BUTTON_PRESSED)
        {
            switch(pedalState)
            {
                case FX_OFF:
                    GPIO_PHET = HIGH;   
                    __delay_ms(7);
                    pedalState = FX_ON; 
                    GPIO_RELE = HIGH;   
                    GPIO_LED = HIGH;    
                    __delay_ms(7);
                    GPIO_PHET = LOW;
                break;
                
                case FX_ON:
                    GPIO_PHET = HIGH; 
                    __delay_ms(7);
                    pedalState = FX_OFF; 
                    GPIO_RELE = LOW; 
                    GPIO_LED = LOW; 
                    __delay_ms(7);
                    GPIO_PHET = LOW;
                break;
            }
        }
    }
}

uint8_t checkButton ()
{   
    if (GPIO_BUTTON == LOW && changeStateFlag == LOW)
    {
        if (btnSwitchCounter < 1750)
        {
            ++btnSwitchCounter;
            return BUTTON_NOT_PRESSED;
        }
        
        else
        {
           btnSwitchCounter = 0;
           changeStateFlag = HIGH;
           return BUTTON_PRESSED;
        }
    }
    
    else if (GPIO_BUTTON == HIGH)
    {
        if (btnSwitchCounter == 0)
        {
           changeStateFlag = LOW;
           return BUTTON_NOT_PRESSED;
        }
        
        --btnSwitchCounter;
    }
}