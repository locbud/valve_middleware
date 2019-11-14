//--------------------------------------------------------------------------
// File Name		: HW_Define.c
// Author			: SunKyung
// Version			: V1.0
// HomePage			: 
// Date				: 11/01/2017
// Description		: Sikhoon J.
//--------------------------------------------------------------------------
#ifndef __UART_H
#define __UART_H
//--------------------------------------------------------------------------
enum {
	BR_1200   = 160,
	BR_2400   = 208,
	BR_4800   = 232,
	BR_9600   = 244,
	BR_14400  = 248,
	BR_19200  = 250,
	BR_28800  = 252,
	BR_38400  = 253,
	BR_57600  = 254,
	BR_115200 = 255
};
//--------------------------------------------------------------------------
#if(Uart1)
//---
extern bit	Tx1_FG;
extern bit	Rx1_FG;
extern bit	Rx1_CP;
//
extern idata unsigned char Tx1_Interval;
extern idata unsigned char Tx1_tCNT;
extern idata unsigned char Tx1_Time;
extern idata unsigned char Tx1_CNT;
extern idata unsigned char Tx1_Len;
extern unsigned char Tx1_Buf[];
extern idata unsigned int  Rx1_Time;
extern idata unsigned char Rx1_tCNT;
extern idata unsigned char Rx1_CNT;
extern idata unsigned char Rx1_Len;
extern unsigned char Rx1_Buf[];
extern unsigned char Rx1_tBuf[];
//--------------------------------------------------------------------------
void Initial_UART0(unsigned char);
void Send_Tx1(char*, char);
//void U0Senddata(char);
//---
#endif
//--------------------------------------------------------------------------
#if(Uart2)
//---
extern bit	Tx2_FG;
extern bit	Rx2_FG;
extern bit	Rx2_CP;
//
extern idata unsigned char Tx2_Interval;
extern idata unsigned char Tx2_tCNT;
extern idata unsigned char Tx2_Time;
extern idata unsigned char Tx2_CNT;
extern idata unsigned char Tx2_Len;
extern unsigned char Tx2_Buf[];
extern idata unsigned int  Rx2_Time;
extern idata unsigned char Rx2_tCNT;
extern idata unsigned char Rx2_CNT;
extern idata unsigned char Rx2_Len;
extern unsigned char Rx2_Buf[];
extern unsigned char Rx2_tBuf[];
//--------------------------------------------------------------------------
void Initial_UART1(unsigned char);
void Send_Tx2(char*, char);
//void U1Senddata(char);
//---
#endif
//--------------------------------------------------------------------------
#endif
// End of File
