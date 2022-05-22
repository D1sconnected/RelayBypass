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
#define DOUBLE_FX

#define GPIO_LED_A    RC5
#define GPIO_RELE_A   RC3
#define GPIO_BUTTON_A RC4
#define GPIO_PHET     RA2

#ifdef DOUBLE_FX
#define GPIO_LED_B    RC0
#define GPIO_RELE_B   RC2
#define GPIO_BUTTON_B RC1
#endif

volatile uint16_t   btnSwitchCounterA = 0;
volatile uint16_t   btnSwitchCounterB = 0;
volatile uint8_t    changeStateFlagA = LOW;
volatile uint8_t    changeStateFlagB = LOW;

uint8_t checkButtonA ();
uint8_t checkButtonB ();

void main ()
{
    //ANSEL = 0; // no analog GPIO
    //ADCON0 = 0; // ADC and DAC converters off
#ifdef DOUBLE_FX
    TRISC1 = 0xFF; // set RC1 as input
    TRISC0 = 0x00; // set RC0 as output
    TRISC2 = 0x00; // set RC2 as output
#endif
    TRISC5 = 0x00; // set RC5 as output
    TRISC3 = 0x00; // set RC3 as output
    TRISC4 = 0xFF; // set RC4 as input
    TRISA2 = 0x00; // set RA2 as output

#ifdef DOUBLE_FX
    GPIO_LED_B    = LOW;
    GPIO_RELE_B   = LOW;
    GPIO_BUTTON_B = LOW;
#endif
    GPIO_LED_A    = LOW;
    GPIO_RELE_A   = LOW;
    GPIO_BUTTON_A = LOW;
    GPIO_PHET     = LOW;

    uint8_t pedalStateA  = FX_OFF;
    uint8_t buttonStateA = BUTTON_NOT_PRESSED;
    uint8_t pedalStateB  = FX_OFF;
    uint8_t buttonStateB = BUTTON_NOT_PRESSED;

    while (1)
    {
        buttonStateA = checkButtonA();
        buttonStateB = checkButtonB();
        
        if (buttonStateA == BUTTON_PRESSED)
        {
            switch(pedalStateA)
            {
                case FX_OFF:
                    GPIO_PHET = HIGH;   
                    __delay_ms(7);
                    pedalStateA = FX_ON; 
                    GPIO_RELE_A = HIGH;
                    GPIO_LED_A = HIGH;
                    __delay_ms(7);
                    GPIO_PHET = LOW;
                break;
                
                case FX_ON:
                    GPIO_PHET = HIGH; 
                    __delay_ms(7);
                    pedalStateA = FX_OFF; 
                    GPIO_RELE_A = LOW;
                    GPIO_LED_A = LOW;
                    __delay_ms(7);
                    GPIO_PHET = LOW;
                break;
            }
        }
        
        if (buttonStateB == BUTTON_PRESSED)
        {
            switch(pedalStateB)
            {
                case FX_OFF:
                    GPIO_PHET = HIGH;   
                    __delay_ms(7);
                    pedalStateB = FX_ON; 
                    GPIO_RELE_B = HIGH;
                    GPIO_LED_B = HIGH;
                    __delay_ms(7);
                    GPIO_PHET = LOW;
                break;
                
                case FX_ON:
                    GPIO_PHET = HIGH; 
                    __delay_ms(7);
                    pedalStateB = FX_OFF; 
                    GPIO_RELE_B = LOW;
                    GPIO_LED_B = LOW;
                    __delay_ms(7);
                    GPIO_PHET = LOW;
                break;
            }
        }
    }
}

uint8_t checkButtonA ()
{   
    if (GPIO_BUTTON_A == LOW && changeStateFlagA == LOW)
    {
        if (btnSwitchCounterA < 1750)
        {
            ++btnSwitchCounterA;
            return BUTTON_NOT_PRESSED;
        }
        
        else
        {
           btnSwitchCounterA = 0;
           changeStateFlagA = HIGH;
           return BUTTON_PRESSED;
        }
    }
    
    else if (GPIO_BUTTON_A == HIGH)
    {
        if (btnSwitchCounterA == 0)
        {
           changeStateFlagA = LOW;
           return BUTTON_NOT_PRESSED;
        }
        
        --btnSwitchCounterA;
    }
}

uint8_t checkButtonB ()
{   
    if (GPIO_BUTTON_B == LOW && changeStateFlagB == LOW)
    {
        if (btnSwitchCounterB < 1750)
        {
            ++btnSwitchCounterB;
            return BUTTON_NOT_PRESSED;
        }
        
        else
        {
           btnSwitchCounterB = 0;
           changeStateFlagB = HIGH;
           return BUTTON_PRESSED;
        }
    }
    
    else if (GPIO_BUTTON_B == HIGH)
    {
        if (btnSwitchCounterB == 0)
        {
           changeStateFlagB = LOW;
           return BUTTON_NOT_PRESSED;
        }
        
        --btnSwitchCounterB;
    }
}