/*
 * s7s_SPI.c
 *
 *  Created on: Jan 13, 2017
 *      Author: User
 *      Controls a sparkfun 7-segment serial display using UCB1
 */
#include "s7s_SPI.h"
#include <msp430.h>


void spi_Open_s7s(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    /* Select the SPI MOSI MISO on lines P4.1, P4.2; clock on P4.3 */
    P4SEL |= (BIT1 + BIT2);
    P4OUT |= BIT2; // set P4.2 (MISO) HIGH
    P4SEL |= BIT3;
    /* Put state machine in reset */
    UCB1CTL1 |= UCSWRST;
    /* MSB first, Master, SPI, 3-pin, 8 bit */
    UCB1CTL0 = UCMSB + UCMST + UCSYNC + UCCKPH;
    //copied
    UCB1CTL1 = UCSWRST + UCSSEL_2; /* Use SMCLK, keep RESET */

    /* Set SPI clock */
    UCB1BR0 = 0x64; /* in theory, f_UCxCLK = 25MHz/100  = 250KHz*/
    UCB1BR1 = 0;
    /* Finished modifying UCB1CTL1&2 */
    UCB1CTL1 &= ~UCSWRST;
    /* Configure the SPI CS to be on P2.3 and P2.6 */
    P2OUT |= (BIT3 + BIT6);
    P2SEL &= ~(BIT3 + BIT6);
    P2DIR |= (BIT3 + BIT6);

    //_delay_cycles(175);
    /* 50 ms delay */
    //Delay(50);
    //return 0;
}

/*
 * clear both displays in future will want to put in low power mode
 */
void spi_Clear_s7s(void)
{
    //first display
    P2OUT &= ~BIT3;
    // Clear display
    UCB1TXBUF = 0x76;
    _delay_cycles(1000);
    P2OUT |= BIT3;
    //second display
    P2OUT &= ~BIT6;
    // Clear display
    UCB1TXBUF = 0x76;
    _delay_cycles(1000);
    P2OUT |= BIT6;
}
/* In spi_Write delay achieved with
 * delay_cycles which is currently in us so that the following
 * gives a delay of 100 us which is just beyond the transmission
 * time needed. Bus 1 is 75, 2 is 17
 */

void spi_Write_s7s(int displayChar, int busNo)
{
    if(busNo == 1)
    {
        //ASSERT_CS1();
        P2OUT &= ~BIT3;
    }else
    {
        P2OUT &= ~BIT6;
    }

    /*if (!(UCB1IFG&UCTXIFG))
    {*/
    // Clear display
    UCB1TXBUF = displayChar;
    //_delay_cycles(350);
    // write data to display
    //UCB1TXBUF = dc.pos1;
    //_delay_cycles(350);
    //UCB1TXBUF = dc.pos2;
    //_delay_cycles(350);
    //UCB1TXBUF = dc.pos3;
    //_delay_cycles(350);
    //UCB1TXBUF = dc.pos4;
    _delay_cycles(1000);
    /*}else{
        errorState = -1;
    }*/
    if(busNo == 1)
    {
        //DEASSERT_CS1();
        P2OUT |= BIT3;
    }else
    {
        P2OUT |= BIT6;
    }
}

DATA_KEY str2enum (const char *str)
{
    int j;
    for (j = 0; j < sizeof(conversion)/sizeof(conversion[0]); ++j)
    {
        if(!strcmp (str, conversion[j].str))
            return conversion[j].val;
        //trap error here
    }
}

void placeData(char *str, struct displayChars *dcPtr, int busNo, int dataKind)
{
    if(dataKind == 0)
    {
        if(busNo == 1)
        {
            dcPtr->errBus1 = str[0];
        }else
        {
            dcPtr->errBus2 = str[0];
        }
    }else
    {
        if(busNo == 1){
            if(strlen(str) == 1)
            {
                dcPtr->pos1 = 0;
                dcPtr->pos2 = str[0];
            }else
            {
                dcPtr->pos1 = str[0];
                dcPtr->pos2 = str[1];
            }
        }else{
            if(strlen(str) == 1)
            {
                dcPtr->pos3 = 0;
                dcPtr->pos4 = str[0];
            }else
            {
                dcPtr->pos3 = str[0];
                dcPtr->pos4 = str[1];
            }
        }
    }
}
