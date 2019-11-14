//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
#include <string.h>
#include "REG_MG82FG5Bxx.h"
#include "Uart.h"
#include "Define.h"
#include "Time2.h"
//--------------------------------------------------------------------------
#if(Uart1)
//---
bit	Tx1_FG = 0;
bit	Rx1_FG = 0;
bit	Rx1_CP = 0;
//
idata unsigned char Tx1_Interval = 0;
idata unsigned char Tx1_tCNT = 0;
idata unsigned char Tx1_Time = 0;
idata unsigned char Tx1_CNT = 0;
idata unsigned char Tx1_Len = 0;
xdata unsigned char Tx1_Buf[Tx1_Size] = {0};
idata unsigned int  Rx1_Time = 0;
idata unsigned char Rx1_tCNT = 0;
idata unsigned char Rx1_CNT = 0;
idata unsigned char Rx1_Len = 0;
xdata unsigned char Rx1_Buf[Rx1_Size] = {0};
xdata unsigned char Rx1_tBuf[Rx1_Size] = {0};
//---
void Initial_UART0(unsigned char BR)
{ 
	TMOD |= 0x20;					//Set Timer1 in Mode2 ( 8 bit ) auto reload mode
	AUXR2 &= !0x08;				//T1X12 =0, clock source = SYSCLK 
    TL1   = BR;
    TH1   = BR;
    S0CON = 0x50;					//SM10=1,SM00=0,
											//REN0=1 Enable reception
	PCON0|= 0x80;					//SMOD1=1;
    //S0CFG|= 0x40;				//SMOD2=1; 
	if(BR <= BR_1200)          Tx1_Interval = 12;
    else if(BR <= BR_4800)   Tx1_Interval = 6;
    else if(BR <= BR_9600)   Tx1_Interval = 3;
	else if(BR <= BR_14400) Tx1_Interval = 2;
    else Tx1_Interval = 1;
    TR1   = 1;
    ES0=1;
}	
//---
void UART0_ISR (void) interrupt 4
{
	idata unsigned char c = 0;
	idata unsigned char  bkSFRPI = 0;
	//---
    if(RI0){    
        RI0 = 0;
		bkSFRPI = SFRPI;
		SFRPI = 0x00;
        c = S0BUF;
		SFRPI = bkSFRPI;
		if(!Rx1_FG){
			memset(Rx1_Buf, 0, Rx1_Size);
			Rx1_CNT = 0;
			Rx1_FG = 1;
		}
        Rx1_Buf[Rx1_CNT++] = c;
        Rx1_Time = 0;
    }
    if(TI0) TI0=0;						//data transmitted 
}
//---
void Send_Tx1(char *Da, char sLen)
{
	Tx1_FG = 0;
//	DIR0 = 1;
	Tx1_CNT = 0;
	Tx1_Len = sLen;
	memcpy(Tx1_Buf, Da, sLen);
	Tx1_FG = 1;
}
//---
/*
void U0Senddata(char c)
{
	TI0 = 0;
    S0BUF = c;
	while(TI0);
}
*/
//---
#endif
//--------------------------------------------------------------------------
#if(Uart2)
//---
bit	Tx2_FG = 0;
bit	Rx2_FG = 0;
bit	Rx2_CP = 0;
//
idata unsigned char Tx2_Interval = 0;
idata unsigned char Tx2_tCNT = 0;
idata unsigned char Tx2_Time = 0;
idata unsigned char Tx2_CNT = 0;
idata unsigned char Tx2_Len = 0;
xdata unsigned char Tx2_Buf[Tx2_Size] = {0};
idata unsigned int  Rx2_Time = 0;
idata unsigned char Rx2_tCNT = 0;
idata unsigned char Rx2_CNT = 0;
idata unsigned char Rx2_Len = 0;
xdata unsigned char Rx2_Buf[Rx2_Size] = {0};
xdata unsigned char Rx2_tBuf[Rx2_Size] = {0};
//---
void Initial_UART1(unsigned char BR)
{
    SFRPI = 0x01;
    S1CON = 0x50;                   //SM11=1, SM01=0,SM21=0,
											//at MODE1: 8-bit UART ,baud rate variable
											//REN1=1 Enable reception
    S1BRT = BR;             			//Baudrate
	S1CFG &= ~S1TX12;			//S1TX12=0
	S1CFG |= S1MOD1;			//S1MOD1=1
	S1CFG |= S1TR;					//S1TR=1
    SFRPI = 0x00;
	if(BR <= BR_1200)          Tx2_Interval = 12;
    else if(BR <= BR_4800)   Tx2_Interval = 3;
    else if(BR <= BR_9600)   Tx2_Interval = 3;
    else if(BR <= BR_14400) Tx2_Interval = 2;
    else                              Tx2_Interval = 1;
    EIE1 |= ES1;
    P1M0 |= 0x08;                   //IO push-pull high
}
//---
void UART1_ISR (void) interrupt 12
{
	idata unsigned char c = 0;
    SFRPI = 0x01;
    if(RI1){    
        RI1=0;
		bkSFRPI = SFRPI;
		SFRPI = 0x01;
        c = S1BUF;
		SFRPI = bkSFRPI;
		if(!Rx2_FG){
			memset(Rx2_Buf, 0, Rx2_Size);
			Rx2_CNT = 0;
			Rx2_FG  = 1;
		}
        Rx2_Buf[Rx2_CNT++] = c;
        Rx2_Time = 0;
    }   
    if(TI1) TI1=0;                  //data transmitted 
    SFRPI = 0x00;   
} 

//---
void Send_Tx2(char *Da, char sLen)
{
	Tx2_FG = 0;
//	DIR1 = 1;
	Tx2_CNT = 0;
	Tx2_Len = sLen;
	memcpy(Tx2_Buf, Da, sLen);
	Tx2_FG = 1;
}
//---
/*
void U1Senddata(char c)
{
    SFRPI = 0x01;
	TI1 = 0;
	S1BUF = c;
	while(TI1);
	SFRPI = 0x00;
}
*/
//---
#endif
//--------------------------------------------------------------------------
// End of File
