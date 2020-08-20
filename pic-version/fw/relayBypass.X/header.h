/* 
 * File:   header.h
 * Author: yupdi
 *
 * Created on 3 ?????? 2020 ?., 15:06
 */

// CONFIG
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select bit (8 MHz)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR Disabled)

// Define oscillator frequency
#define _XTAL_FREQ 8000000

#define HIGH 1
#define LOW 0

#define BUTTON_PRESSED 0xFF
#define BUTTON_NOT_PRESSED 0x00

#define FX_ON   0xFF
#define FX_OFF  0x00

typedef enum 
{
    PEDAL_ON,
    PEDAL_OFF
}   pedalStatus;