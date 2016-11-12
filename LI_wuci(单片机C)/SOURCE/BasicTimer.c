/*
 * BasicTimer.c
 *
 *  Created on: 2015-3-4
 *      Author: Administrator
 */

#include "BasicTimer.h"

void BT_Init(void)
{
	BTCTL	|=	BT_ADLY_500;					   /* 500ms      " */
	BTCNT1	=	0x00;
	BTCNT2	=	0x00;
	IE2		|=	0x80;
	IFG2		=	0x00;
}
/*
#pragma vector=BASICTIMER_VECTOR
__interrupt void BT_IRQ(void)
{
	P6OUT ^= BIT0;
}
*/

