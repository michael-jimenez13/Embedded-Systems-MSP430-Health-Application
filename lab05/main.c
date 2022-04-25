#include <msp430.h>

int numPresses = 0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Stop WDT

    if(CALBC1_1MHZ==0xFF)
    {
        while(1);
    }
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;
    P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 8;                              // 1MHz 115200
    UCA0BR1 = 0;                              // 1MHz 115200
    UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

    P1DIR &= ~BIT3;                           // S2 Button is input

    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled

}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    //while (!(IFG2 & UCA0TXIFG));                 // USCI_A0 TX buffer ready?
    //UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed characte
    numPresses++;
    char number = numPresses + '0';
    //UCA0TXBUF = number;
    char sentence[] = "Button has been pressed ";
    char rest[] = " times.\n";
    int k;
    for (k = 0; k < 24; k++) {
        while (!(IFG2 & UCA0TXIFG));
        UCA0TXBUF = sentence[k];
    }
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = number;
    int i;
    for (i = 0; i < 8; i++) {
        while (!(IFG2 & UCA0TXIFG));
        UCA0TXBUF = rest[i];
    }
    IFG2 &= ~UCA0RXIFG;
}


