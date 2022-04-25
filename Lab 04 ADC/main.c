#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    
    //adc 10 stuff
    ADC10CTL0 |= ADC10ON ;//enables sampling and conversion
    ADC10AE0 |= 0x02; //analog input
    ADC10CTL0 |= SREF_7; // reference voltage
    ADC10CTL0 |= ADC10IE; //interrupt enabled
    //ADC10CTL0 |= ADC10SC + ENC ;//enables sampling and conversion
    ADC10CTL0 &= ~ADC10IFG; //flag is off

    //led stuff
    P1DIR |= BIT0;
    P1OUT &= ~BIT0; //led off
for(;;){
    ADC10CTL0 |= ADC10SC + ENC ;//enables sampling and conversion
    __bis_SR_register(LPM0+GIE);//enables lower power mode and general interrupt
    if(ADC10MEM > 0){ //voltage greater than 0
        P1OUT |= BIT0; //on
    }
    else{
        P1OUT &= ~BIT0; //off
    }
    //flag is set
}
}
//ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    ADC10CTL0 &= ~ADC10IFG; //flag is off
}



    return 0;
}
