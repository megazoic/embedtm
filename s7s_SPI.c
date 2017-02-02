/*
 * s7s_SPI.c
 *
 *  Created on: Jan 13, 2017
 *      Author: User
 *      Controls a sparkfun 7-segment serial display using UCB1
 */
#include "s7s_SPI.h"
#include <msp430.h>


void spi_Open_s7s()
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
    /* Configure the SPI CS to be on P2.3 */
    P2OUT |= BIT3;
    P2SEL &= ~BIT3;
    P2DIR |= BIT3;

    //_delay_cycles(175);
    /* 50 ms delay */
    //Delay(50);
    //return 0;
}

/* In spi_Write delay achieved with
 * delay_cycles which is currently in us so that the following
 * gives a delay of 100 us which is just beyond the transmission
 * time needed
 */

void spi_Write_s7s(int displayChar)
{
    //ASSERT_CS1();
    P2OUT &= ~BIT3;

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
    //DEASSERT_CS1();
    P2OUT |= BIT3;
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

/*
DATA_KEY str2enum(const char *str)
{
    int j;
    for (j = 0; j < sizeof(conversion) / sizeof (conversion[0]); ++j)
        if(!strcmp(str, conversion[j].str))
            return conversion[j].val;
    return compErr;
}
*/
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

/*
void placeData(char *str, struct displayChars *dcPtr, VALUE dataDescriptor)
{
    switch(dataDescriptor){
    case _75Ea:
        dcPtr->err12 = str[0];
        break;
    case _75Eb:
        dcPtr->err34 = str[0];
        break;
    case _75a:
        if(strlen(str) == 1)
        {
            dcPtr->pos2 = str[0];
        }else{
            dcPtr->pos1 = str[0];
            dcPtr->pos2 = str[1];
        }
        break;
    case _75b:
        if(strlen(str) == 1)
        {
            dcPtr->pos4 = str[0];
        }else{
            dcPtr->pos3 = str[0];
            dcPtr->pos4 = str[1];
        }
        break;
    case Time:
        /* leave this out for now
        if(strlen(str) == 3)
        {
            dcPtr->pos2 = str[0];
            dcPtr->pos3 = str[1];
            dcPtr->pos4 = str[2];
        }else{
            dcPtr->pos1 = str[0];
            dcPtr->pos2 = str[1];
            dcPtr->pos3 = str[2];
            dcPtr->pos4 = str[3];
        }
        dcPtr->timeColon = 1;
        * /
        break;
    default:
        //error
        break;
    }
}*/
