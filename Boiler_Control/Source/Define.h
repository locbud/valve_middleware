//--------------------------------------------------------------------------
// File Name		: HW_Define.c
// Author			: SunKyung
// Version			: V1.0
// HomePage		: 
// Date				: 11/01/2017
// Description	: Sikhoon J.
//--------------------------------------------------------------------------
#ifndef __DEFINE_H
#define __DEFINE_H
//--------------------------------------------------------------------------
sbit	LED1		= 0xF8^0;	// P6.0 Green
sbit	LED2		= 0xF8^1;	// P6.1 Red
//--- ADC
sbit	AD_TH		= 0x90^0;	// P1.0
sbit	AD_TL		= 0x90^1;	// P1.1
sbit	AD_VB		= 0x90^2;	// P1.2
sbit	AD_CU		= 0x90^3;	// P1.3
//--- MJ447RTX
sbit	RF_REI		= 0xB0^2;	// P3.2
sbit	RF_WUT		= 0xB0^3;	// P3.3
sbit	RF_OPT		= 0xB0^4;	// P3.4
sbit	RF_B1B2		= 0xB0^5;	// P3.5
sbit	RF_CH2		= 0xE8^0;	// P4.0
sbit	RF_CH1		= 0xE8^1;	// P4.1
//---
sbit	P1_MC		= 0x90^6;	// P1.6
sbit	P2_MC		= 0x90^7;	// P1.7
sbit	P3_MC		= 0xA0^2;	// P2.2
sbit	P4_MC		= 0xA0^3;	// P2.3
sbit	P5_MC		= 0xA0^4;	// P2.4
sbit	P6_MC		= 0xA0^6;	// P2.6
//--------------------------------------------------------------------------
#define	Xtal_Freq	22118400	// Unit:Hz In-OSC
#define	T2_Tg_Val	1000		// 100uSec
//---
#define Tx1_Size	38
#define Tx2_Size	38
#define Rx1_Size	38
#define Rx2_Size	38
#define PG_Err		"Err-1.0.0\0"
//--------------------------------------------------------------------------
#define MAP_MAX		50
#define RTU_aID		0x01
#define RTU_CMD		0x04		// 0x04
#define RTU_Addr	0x0000		// 1000
#define RTU_Len		10
//--------------------------------------------------------------------------
#define IAP_Addr		0x3E00		// 512
//--------------------------------------------------------------------------
enum {
	MA_STATE  =  0,		//  State Value
	MA_SET    =  1,		// Output Value
	MA_TH     =  2,		// Hot Temp Value
	MA_TL     =  4,		// Cool Temp Value
	MA_VO     =  6,		// Voltage Value
	MA_CU     =  8,		// Current Value
	//--- Scale
	SA_TH     = 12,		// Hot Temp Value
	SA_TL     = 14,		// Cool Temp Value
	SA_VO     = 16,		// Voltage Value
	SA_CU     = 18,		// Current Value
	//--- Zero
	ZA_TH     = 22,		// Hot Temp Value
	ZA_TL     = 24,		// Cool Temp Value
	ZA_VO     = 26,		// Voltage Value
	ZA_CU     = 28,		// Current Value
};
//---
enum {
	ADC_TH    =  0,		// Hot Temp Value
	ADC_TL    =  1,		// Cool Temp Value
	ADC_VO    =  2,		// Voltage Value
	ADC_CU    =  3,		// Current Value
	ADC_UD    =  9,		// ADC Updata
};
//--------------------------------------------------------------------------
typedef union{
	unsigned char B[2];
    unsigned short W;
} WTYPE;
//---
typedef union{
	unsigned char B[4];
    unsigned short W[2];
	unsigned long L;
	float F;
} DWORD;
//---
typedef struct{
	unsigned char ID;
	unsigned char CMD;
	unsigned int  Add;
	unsigned int  No;
} Type_ModbusRTU;
//---
typedef struct{
	float	TH;	// Hot Temp Value
	float	TL;	// Cool Temp Value
	float	VO;	// Voltage Value
	float	CU;	// Current Value
	short	Do;	// Output Value
	short	ST;	// State Value
} Type_Temp;
//---
typedef struct{
	char	Mode;
	short	ID;	// Chnal ID
	float	TT;	// Tagjet Temp Value
	
} Type_Sys;
//--------------------------------------------------------------------------
#endif
// End of File
