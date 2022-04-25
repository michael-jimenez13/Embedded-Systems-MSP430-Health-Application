#include <msp430.h> 


int main(void) {

    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    if(CALBC1_1MHZ == 0xFF)           //if calibration constant erased
    DCOCTL= 0;                          //set DC0
    BCSCTL1=CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1SEL  = BIT1 + BIT2;                // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;

   // ADC setup
    ADC10CTL0 |=  ADC10ON + ADC10IE ;     // ADC10ON, interrupt enabled and AD10 on and Vo
    ADC10CTL0 |= SREF_0;                 // reference voltage mean VR+ = VCC an Vr-= Vss
    ADC10CTL1 |= INCH_4;                 // input A4 --pin 4 of msp
    ADC10AE0 |= BIT4;                    // PA.1  enable register 9



    // UART setup
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 8;                              // 1MHz 115200
    UCA0BR1 = 0;                              // 1MHz 115200
    UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

    while(!(UCA0RXBUF == 'a'));

    CCTL0 == CCIE  ;                            //CCR0 interupt enabled

    TA0CTL = TASSEL_1 +ID_3 + MC_1;         //divide 32768 by divider number a
    CCR0 =1;    //sampling rate

        //IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
            //while(1){
            //ADC10CTL0 |= ADC10SC + ENC;
            //delay(2000)

        __bis_SR_register(GIE+LPM0_bits);

}

    // AC10 ISR
    #pragma vector=ADC10_VECTOR
    __interrupt void ADC10_ISR(void)
    {
        ADC10CTL0 &= ~ADC10IFG;
        while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
            UCA0TXBUF = ADC10MEM >> 8;                        // TX -> MSB

        while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
        UCA0TXBUF = ADC10MEM ;                        // TX -> LSB
        __bis_SR_register(CPUOFF);

    }
    //timer
    #pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer0_A0(void){
        while(!(IFG2&UCA0TXIFG));

        ADC10CTL0 |= ENC + ADC10SC; //enable conversion

        __bis_SR_register(GIE+CPUOFF);
    }

