//--------------------------------------------------------------------------
// File Name		: HW_Define.c
// Author			: SunKyung
// Version			: V1.0
// HomePage			: 
// Date				: 11/01/2017
// Description		: Sikhoon J.
//--------------------------------------------------------------------------
#ifndef __TIME2_H
#define __TIME2_H
//--------------------------------------------------------------------------
extern bit FG_T10mS;
extern bit FG_T100mS;
extern bit FG_T1S;
//
extern idata unsigned int  D_10m;
extern idata unsigned int  D_100m;
extern idata unsigned int  D_1Sec;
//
extern idata  unsigned int T_delay;
//--------------------------------------------------------------------------
void delay(unsigned int);
void Initial_Timer2(void);
//--------------------------------------------------------------------------
#endif
// End of File

