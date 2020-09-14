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

volatile uint16_t buttonCounter = 0;
uint8_t changeStateFlag = LOW;

void checkButtonState (uint8_t *pState);
uint8_t checkButton ();

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

/*
RC3 = LOW;
RC1 = LOW/
RC0 = LOW;
*/
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
            //changeStateFlag = LOW;
  
            switch(pedalState)
            {
                
                case FX_OFF:
                    GPIO_PHET = HIGH;   
                    __delay_ms(20);
                    pedalState = FX_ON; 
                    GPIO_RELE = HIGH;   
                    GPIO_LED = HIGH;    
                    __delay_ms(20);
                    GPIO_PHET = LOW;
                break;
                
                case FX_ON:
                    GPIO_PHET = HIGH; 
                    __delay_ms(20);
                    pedalState = FX_OFF; 
                    GPIO_RELE = LOW; 
                    GPIO_LED = LOW; 
                    __delay_ms(20);
                    GPIO_PHET = LOW;
                break;
            }
        }
        
     //checkButtonState(&state);
        
    }
}

uint8_t checkButton ()
{   
    //static uint8_t buttonFlag = LOW;
    
    if (GPIO_BUTTON == LOW && changeStateFlag == LOW)
    {
        if (buttonCounter < 2500)
        {
            ++buttonCounter;
            return BUTTON_NOT_PRESSED;
        }
        
        else
        {
           buttonCounter = 0;
           changeStateFlag = HIGH;
           return BUTTON_PRESSED;
        }
    }
    
    else if (GPIO_BUTTON == HIGH)
    {
        if (buttonCounter == 0)
        {
           changeStateFlag = LOW;
           return BUTTON_NOT_PRESSED;
        }
        
        --buttonCounter;
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