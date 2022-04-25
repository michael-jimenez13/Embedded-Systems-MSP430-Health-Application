#include <msp430.h>

#define Button BIT3
#define RedLight BIT0
#define GreenLight BIT6


int main(void)
{
        WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

        //RedLight Setup
        P1DIR |= RedLight;   //sets pin with LED1 to output
        P1OUT &= ~RedLight; //turn it ON

        // Button setup
          P1DIR &= ~Button;                     // button is an input
          P1OUT = Button;                      // enable pull-up resistor
          P1REN = Button;                      // pulup

 while (1) // Continuous loop for polling
 {

     P1OUT = RedLight; //on
     /*
     int value = P1IN & Button;
     //_delay_cycles(50000);
     if(!(value )) {//is button pressed?
         P1OUT |= RedLight; //input low turn light on
     }
     else{
         P1OUT &= ~RedLight; //input high -turn led off
     }
*/

 }

}
