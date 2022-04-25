#include <msp430.h>

#define Button BIT3;
#define RedLight BIT0;

int main(void)
{
 WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
 //RedLight Setup
     P1DIR |= RedLight;   //sets pin with LED1 to output
     P1OUT  &= ~RedLight; //turn it off

 // Button setup
     P1DIR &= ~Button;                     // button is an input
     P1OUT = Button;                      // enable pull-up resistor
     P1REN = Button;                      // pulup
     P1IE =  Button;                            // P1.3 interrupt enabled
     P1IES |= Button;                            // P1.3 Hi/lo edge
     P1IFG |= Button;                           //enable flag
     __bis_SR_register(LPM4_bits + GIE); // Enter LPM4 w/interrupt
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    int check = P1IFG & Button;

    if(check){
        P1IFG &= ~Button;                           //disable flag
        P1OUT ^= RedLight; //ON AND OFF
        _delay_cycles(200000);
    }

      /*   int value = P1IN & Button;
       /  if(!(value )) {//is button pressed?
             P1OUT ^= RedLight; //input low turn light on
             _delay_cycles(1000000000);
         }
         else{
             P1OUT &= ~RedLight; //input high -turn led off
         }
*/


   // P1IFG &= ~Button;                           //disable flag

}
