//*****************************************************************************
//
// Lab 3 - Compiler Optimization
// 1/6/22
// Jannel Bennett
//
// For this lab; explore the optimization performance of the TI Arm Compiler.
//              write C code to run on the MSP432 system, then experiment with different optimization
//              settings and observe the performance in terms of code size and speed.
//
// ** PIN 2.7 Not Working
//
// Initialize GPIO. Setup inputs and outputs as follows:
//
//  Port pin    in/out  Pullup/down     Connect
//    P2.6      In/Out    N/A             Scope
//    P2.1        Out     N/A             LED2-G
//
//  *********   Nokia LCD interface reference   **************
//
// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// UCA3STE       (SCE, pin 3) connected to P9.4
// Reset         (RST, pin 4) connected to P9.3
// Data/Command  (D/C, pin 5) connected to P9.2
// UCA3SIMO      (DN,  pin 6) connected to P9.7
// UCA3CLK       (SCLK, pin 7) connected to P9.5
// back light    (LED, pin 8) not connected, consists of 4 3.3 V white LEDs which draw ~80mA total

//****************************************************************************

#include <stdint.h>
#include "msp.h"
#include "msoe_lib_all.h" // includes libraries not used


/**
 * main.c
 */

void GPIO_setup(void);
void G_LED1(void); // turn on led
void G_LED0(void); // turn off led
void LCD_setup (); // function never called

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    int time;

	GPIO_setup(); // this is a small function call that could have been put in main

    while(1){

        // toggle LED 10 times with bad delay - nested loop, variable defined in loop, funcitons in loop (LED on/off)
        int j; // reinitialize variable
        for (j=0;j<10;j++){ // overhead
            int i; // define variable in loop
            for (i=0;i<10000;i++){
                // delay of one second
                G_LED0(); // LED off - 1 line function (unchanging loop)
            }
            for (i=0;i<10000;i++){
                // delay of one second
                G_LED1(); // G_LED on - 1 line function (unchanging loop)
            }
        }

        // Unsimplified math, lots of console prints, lots of variable reinitialized / unneeded variables
        int a=1; // reinitialize variable
        int b=2; // reinitialize variable
        int c=3; // reinitialize variable
        int avg; // reinitialize variable

        avg = a;
        avg = avg+b;
        avg = avg + c;
        avg = avg / 3;

        printf("The average of 1 , 2, and 3 is %d.\n", avg); //Spits avg out.

        // switch statement with most common case last

        switch(c){
        case 0:
            LCD_goto_xy(0, 2);  // start at row 2, col 0
            LCD_print_str("MERP");
            break;
        case 1:
            LCD_goto_xy(0, 2);  // start at row 2, col 0
            LCD_print_str("MERP");
            break;
        case 2:
            LCD_goto_xy(0, 2);  // start at row 2, col 0
            LCD_print_str("MERP");
            break;
        default:
            LCD_goto_xy(0, 2);  // start at row 2, col 0
            LCD_print_str("YEY YEY YEY");
            break;
        }

            P2->OUT ^=(BIT6); // P2.7 on - checks time to take to finish while loop using scope

    }
}

// Functions //
void GPIO_setup (void){
    // SET GPIO's
    P2->DIR |= (BIT6);  // P2.7 output
    P2->DIR |= (BIT1);  // G_LED output

}
void G_LED0 (void){
    P2->OUT &= ~(BIT1);  // G_LED off
}
void G_LED1 (void){
    P2->OUT ^=(BIT1);   // G_LED on
}
void LCD_setup (void){
    LCD_Config();
    LCD_clear();
}
