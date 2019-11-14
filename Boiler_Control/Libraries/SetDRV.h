//--------------------------------------------------------------------------
// File Name		: HW_Define.c
// Author			: SunKyung
// Version			: V1.0
// HomePage			: 
// Date				: 11/01/2017
// Description		: Sikhoon J.
//--------------------------------------------------------------------------
#ifndef __SET_DRV_H
#define __SET_DRV_H
//--------------------------------------------------------------------------
extern idata char LED1_FG;
extern idata char LED2_FG;
//--------------------------------------------------------------------------
void Ser_OSC(void);
void IO_Map_Init(void);
//void EnableWD(void);
//void LED_Flush(void);
void LED_OnOff(char, char);
void IO_InOut(unsigned char);
void WDT_INIT(void);
void RF_Set(unsigned char);
//--------------------------------------------------------------------------
#endif
// End of File
