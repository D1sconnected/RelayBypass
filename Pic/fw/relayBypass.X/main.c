// Supplementary libraries
#include <stdint.h>
#include <xc.h>
// Include configuration bits
#include "header.h"

#define DOUBLE_FX                                   // comment this line to use singe fx version
#define PHET_DELAY_TOTAL    14                      // total time in ms between phet activation and deactivation
#define PHET_DELAY_HALF     PHET_DELAY_TOTAL / 2    // half  time in ms, first half takes place before switch routine, second takes after
#define RATLLE_SENSITIVITY  1750                    // from 0 to 65535, btnSwCounter's max value to sense button pressed event

#define GPIO_LED_A    RC5
#define GPIO_RELE_A   RC3
#define GPIO_BUTTON_A RC4
#define GPIO_PHET     RA2

#ifdef DOUBLE_FX
#define GPIO_LED_B    RC0
#define GPIO_RELE_B   RC2
#define GPIO_BUTTON_B RC1
#endif

volatile uint16_t   btnSwCounterA   = 0;            // rattle counter for button A
volatile uint16_t   btnSwCounterB   = 0;            // rattle counter for button B
volatile uint8_t    swStateFlagA    = LOW;          // switch flag    for FX     A (keeped untill button released)
volatile uint8_t    swStateFlagB    = LOW;          // switch flag    for FX     B (keeped untill button released)

uint8_t checkButtonA ();
uint8_t checkButtonB ();

void main ()
{
    /* PICF616
    ANSEL = 0; // no analog GPIO
    ADCON0 = 0; // ADC and DAC converters off
    */ 
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

    /* 1. Check buttonState's -> update btnSwCounter's and update swStateFlag's -> return buttonState's
     * 2. If detected BUTTON_PRESSED -> do routine based on pedalState
     * 3. Switch routine sequence:
     *    3.1 Activate PHET to supress noise & wait PHET_DELAY_HALF
     *    3.2 Change relay state & led state & wait PHET_DELAY_HALF
     *    3.3 Change pedal state in programm
     *    3.4 Deactivate PHET to release sound path
     * 4. Repeat 1-2 in loop
     */
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
                    __delay_ms(PHET_DELAY_HALF);
                    GPIO_RELE_A = HIGH;
                    GPIO_LED_A = HIGH;
                    pedalStateA = FX_ON; 
                    __delay_ms(PHET_DELAY_HALF);
                    GPIO_PHET = LOW;
                break;
                
                case FX_ON:
                    GPIO_PHET = HIGH; 
                    __delay_ms(PHET_DELAY_HALF);
                    GPIO_RELE_A = LOW;
                    GPIO_LED_A = LOW;
                    pedalStateA = FX_OFF; 
                    __delay_ms(PHET_DELAY_HALF);
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
                    __delay_ms(PHET_DELAY_HALF);
                    GPIO_RELE_B = HIGH;
                    GPIO_LED_B = HIGH;
                    pedalStateB = FX_ON; 
                    __delay_ms(PHET_DELAY_HALF);
                    GPIO_PHET = LOW;
                break;
                
                case FX_ON:
                    GPIO_PHET = HIGH; 
                    __delay_ms(PHET_DELAY_HALF);
                    GPIO_RELE_B = LOW;
                    GPIO_LED_B = LOW;
                    pedalStateB = FX_OFF; 
                    __delay_ms(PHET_DELAY_HALF);
                    GPIO_PHET = LOW;
                break;
            }
        }
    }
}

/* 1. If button was pressed (low state) and switch did not occured, we need to deal with rattle. 
 *    So increment counter on each enter until max value, then set swStateFlag, which will be keeped untill button released.
 * 2. When button released  (high state) keep lowering counter, untill it's 0. Then update swStateFlag.
 *    This force pedal to switch only once on actual real-time button press.
 */
uint8_t checkButtonA ()
{   
    if (GPIO_BUTTON_A == LOW && swStateFlagA == LOW)
    {
        if (btnSwCounterA < RATLLE_SENSITIVITY)
        {
            ++btnSwCounterA;
            return BUTTON_NOT_PRESSED;
        }
        
        else
        {
           btnSwCounterA = 0;
           swStateFlagA = HIGH;
           return BUTTON_PRESSED;
        }
    }
    
    else if (GPIO_BUTTON_A == HIGH) // swStateFlagA not important
    {
        if (btnSwCounterA == 0)
        {
           swStateFlagA = LOW;
           return BUTTON_NOT_PRESSED;
        }
        
        --btnSwCounterA;
    }
    
    return BUTTON_NOT_PRESSED;
}

uint8_t checkButtonB ()
{   
    if (GPIO_BUTTON_B == LOW && swStateFlagB == LOW)
    {
        if (btnSwCounterB < RATLLE_SENSITIVITY)
        {
            ++btnSwCounterB;
            return BUTTON_NOT_PRESSED;
        }
        
        else
        {
           btnSwCounterB = 0;
           swStateFlagB = HIGH;
           return BUTTON_PRESSED;
        }
    }
    
    else if (GPIO_BUTTON_B == HIGH) // swStateFlagB not important
    {
        if (btnSwCounterB == 0)
        {
           swStateFlagB = LOW;
           return BUTTON_NOT_PRESSED;
        }
        
        --btnSwCounterB;
    }
    
    return BUTTON_NOT_PRESSED;
}