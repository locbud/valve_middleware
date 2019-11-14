//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
#include "REG_MG82FG5Bxx.h"
#include "SetDRV.h"
#include "Define.h"
#include "IAP.h"
//--------------------------------------------------------------------------
idata char LED1_FG = 0;
idata char LED2_FG = 0;
//---
unsigned char Mode_Val = 0;
//--------------------------------------------------------------------------
/*
const unsigned char RF_oST = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x57};	// Out 8Byte
const unsigned char RF_oE1 = {0x3A, 0x6F, 0x6E, 0x20, 0x0D};	// ON  5Byte
const unsigned char RF_oE2 = {0x3A, 0x4F, 0x46, 0x46, 0x0D};	// OFF 5Byte
*/
//--------------------------------------------------------------------------
void Ser_OSC(void)
{
	CKCON0 |= (AFS|CKMIS0|ENCKM);	// CKCON0  11.0592MHz
	PageP_Write(0x0040, 0x54);		// 22.1184MHz
	PageP_Write(IAPLB_P, 0x3E);		// IAP Start Address 0x3E00 512Byte
}
/*
//--------------------------------------------------------------------------
void EnableWD(void)
{
	PCON1 |= WDTF; // Clear WDT flag (write ?1?)
	// Enable WDT counter and set WDT period to 248ms
	PageP_Write((unsigned int)WDTCR, WREN|ENW|CLW|PS2);
}
*/
//--------------------------------------------------------------------------
void LED_OnOff(char Ch, char Da)
{
	if(Ch == 1){
		if(Da == 1) LED1 = 0; else LED1 = 1;
	}
	if(Ch == 2){
		if(Da == 1) LED2 = 0; else LED2 = 1;
	}
}
//--------------------------------------------------------------------------
void IO_InOut(unsigned char Da)
{
	if(Da&0x01) P1_MC = 1; else P1_MC = 0;
	if(Da&0x02) P2_MC = 1; else P2_MC = 0;
	if(Da&0x04) P3_MC = 1; else P3_MC = 0;
	if(Da&0x08) P4_MC = 1; else P4_MC = 0;
	if(Da&0x10) P5_MC = 1; else P5_MC = 0;
	if(Da&0x20) P6_MC = 1; else P6_MC = 0;
}
//--------------------------------------------------------------------------
void RF_Set(unsigned char Da)
{
	if(Da&0x01) RF_CH1  = 1; else RF_CH1  = 0;
	if(Da&0x02) RF_CH2  = 1; else RF_CH2  = 0;
	if(Da&0x04) RF_B1B2 = 1; else RF_B1B2 = 0;
	if(Da&0x08) RF_OPT  = 1; else RF_OPT  = 0;	// High
	if(Da&0x10) RF_WUT  = 1; else RF_WUT  = 0;	// High
	if(Da&0x80) RF_REI  = 1; else RF_REI  = 0;
}
//--------------------------------------------------------------------------
/*
void RF_Out(unsigned char Ch, unsigned char Da)
{
	unsigned char i = 0, j = 0, k = 0;
	unsigned char Buf[15] = {0};
	//---
	k = 0;
	for(i = 0; i < 8; i++){
		Buf[k++] = RF_oST[i];
	}
	//---
	Buf[k++] = Ch + 0x30;
	//---
	for(i = 0; i < 5; i++){
		if(Da == 2) Buf[k++] = RF_oE2[i];	// Off
		else          Buf[k++] = RF_oE1[i];	// On
	}
	Send_Tx1(Buf, k);
}
*/
//--------------------------------------------------------------------------
void IO_Map_Init(void)
{
	PUCON0 = 0x40;
	P1M0 |= 0xC0;
	P2M0 |= 0x5C;
	SFRPI = 0x01;
	P6M0 |= 0x03;
	SFRPI = 0x00;
}
//--------------------------------------------------------------------------
void WDT_INIT(void)
{
	PCON1 |= WDTF;								// Clear WDT flag (write “1”)
	WDTCR = (WREN | NSW | CLW | PS2 | PS1| PS0);	// set WDT period to 248ms
	WDTCR |= ENW;								// Enable WDT counter, WDT running.
}
//--------------------------------------------------------------------------
// End of File
