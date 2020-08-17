/* 
 * File:   main.c
 * Author: yupdi
 *
 * Created on 3 ?????? 2020 ?., 15:16
 */

#include <stdio.h>
#include <stdlib.h>

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

void checkButtonState (uint8_t *pState);

void main ()
{
    
ANSEL = 0; // no analog GPIO
ADCON0 = 0; // ADC and DAC converters off
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

pedalStatus pedalState = PEDAL_OFF;
buttonStatus buttonState = BUTTON_RELEASED;
/*
RC3 = LOW;
RC1 = LOW;
RC0 = LOW;
*/
GPIO_LED    = LOW;
GPIO_RELE   = LOW;
GPIO_BUTTON = LOW;
GPIO_PHET   = LOW;

uint8_t state = 0;

    while (1)
    {
     checkButtonState(&state);
        
        /*
        if (GPIO_BUTTON == LOW)
        {
            buttonState = BUTTON_PRESSED;
        }
        
        switch(pedalState)
        {
            case PEDAL_OFF:
                if (GPIO_BUTTON == HIGH && buttonState == BUTTON_PRESSED)
                {
                    pedalState = PEDAL_ON;
                    //RC3 = HIGH; // enable led
                    GPIO_LED = HIGH;
                    //RC1 = HIGH; // enable rele
                    GPIO_RELE = HIGH;
                    buttonState = BUTTON_RELEASED;
                }  
            break;
            case PEDAL_ON:
                if (GPIO_BUTTON == HIGH && buttonState == BUTTON_PRESSED)
                {
                    pedalState = PEDAL_OFF;
                    GPIO_LED = LOW; // disable led
                    GPIO_RELE = LOW; // disable rele
                    buttonState = BUTTON_RELEASED;
                }  
            break;
        }
        */
        
        
    }
}

void checkButtonState (uint8_t *pState)
{
        if (GPIO_BUTTON == 0x00) 
        {
            __delay_ms(15); // debounce
            if (GPIO_BUTTON == 0x00)
            {
                __delay_ms(200);
                
                if (GPIO_BUTTON == 1)
                {
                    
                    if (*pState == 1) // pedal is on
                    {
                        GPIO_PHET = 1; // activate phet
                        //__delay_ms(100);
                        *pState = 0; // turn off
                        GPIO_RELE = 0x00; // turn on rele
                        GPIO_LED = 0x00; // turn led off
                        //__delay_ms(100);
                        GPIO_PHET = 0;
                    }

                    else // pedal is off
                    {
                        GPIO_PHET = 1; // activate phet
                        //__delay_ms(100);
                        *pState = 1; // turn on
                        GPIO_RELE = 0xFF; // turn on rele
                        GPIO_LED = 0xFF; // turn led on
                        //__delay_ms(100);
                        GPIO_PHET = 0;
                    }
                }
            }
        }
}