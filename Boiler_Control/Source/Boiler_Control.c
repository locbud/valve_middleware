//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "REG_MG82FG5Bxx.h"
#include "Define.h"
#include "SetDRV.h"
#include "Time2.h"
#include "Uart.h"
#include "Modbus.h"
#include "ADC.h"
#include "IAP.h"
//--------------------------------------------------------------------------
//idata unsigned char  Not_Conn = 0;
//---
Type_Temp	mDB;
//--------------------------------------------------------------------------
code int NTC_Table[] = {
//	  0    1    2    3    4    5    6    7    8    9
//	  5,   5,   5,   5,   5,   5,   5,   5,   5,   5,	//
	 -5,  -4,  -4,  -3,  -3,  -2,  -2,  -1,  -1,   0,	//   0  (마이너스온도)
	  0,   1,   2,   2,   3,   3,   4,   4,   5,   6,	//  10
	  7,   7,   8,   8,   9,   9,  10,  10,  11,  12,	//  20
	 12,  13,  13,  14,  14,  15,  15,  16,  16,  17,	//  30
	 17,  18,  18,  18,  19,  19,  20,  20,  21,  21,	//  40
	 22,  22,  22,  23,  23,  24,  24,  24,  25,  25,	//  50
	 26,  26,  27,  27,  28,  28,  28,  29,  29,  29,	//  60
	 30,  30,  31,  31,  31,  32,  32,  33,  33,  33,	//  70
	 34,  34,  35,  35,  35,  36,  36,  37,  37,  37,	//  80
	 38,  38,  39,  39,  40,  40,  40,  41,  41,  42,	//  90
	 42,  42,  43,  43,  43,  44,  44,  44,  45,  45,	// 100
	 46,  46,  46,  47,  47,  48,  48,  48,  49,  49,	// 110
	 50,  50,  50,  51,  51,  51,  52,  52,  53,  53,	// 120
	 54,  54,  54,  55,  55,  56,  56,  57,  57,  58,	// 130
	 58,  59,  59,  60,  60,  60,  61,  61,  62,  62,	// 140
	 63,  63,  64,  64,  65,  65,  66,  67,  68,  68,	// 150
	 69,  69,  70,  70,  71,  71,  72,  72,  73,  74,	// 160
	 74,  75,  75,  76,  76,  77,  78,  79,  80,  80,	// 170
	 81,  82,  83,  83,  84,  85,  86,  87,  88,  89,	// 180
	 90,  91,  92,  93,  94,  95,  96,  97,  98,  99,	// 190
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109,	// 200
	110, 111, 112, 113, 114, 115, 116, 117, 118, 119,	// 210
	120, 121, 122, 123, 124, 125, 126, 127, 128, 129,	// 220
	130, 131, 132, 133, 134, 135, 136, 137, 138, 139,	// 230
	140, 141, 142, 143, 144, 145, 146, 147, 148, 149	// 240
};
//--------------------------------------------------------------------------
void GetScaleZero(void)
{
	DWORD DW;
	//---
	DW.W[0] = mDB_rMAP[SA_TH]; DW.W[1] = mDB_rMAP[SA_TH+1]; ADC_SCALE[ADC_TH] = DW.F;		
	DW.W[0] = mDB_rMAP[SA_TL]; DW.W[1] = mDB_rMAP[SA_TL+1]; ADC_SCALE[ADC_TL] = DW.F;
	DW.W[0] = mDB_rMAP[SA_VO]; DW.W[1] = mDB_rMAP[SA_VO+1]; ADC_SCALE[ADC_VO] = DW.F;
	DW.W[0] = mDB_rMAP[SA_CU]; DW.W[1] = mDB_rMAP[SA_CU+1]; ADC_SCALE[ADC_CU] = DW.F;
	ADC_ZERO[ADC_TH] = mDB_rMAP[ZA_TH];
	ADC_ZERO[ADC_TL] = mDB_rMAP[ZA_TL];
	ADC_ZERO[ADC_VO] = mDB_rMAP[ZA_VO];
	ADC_ZERO[ADC_CU] = mDB_rMAP[ZA_CU];
}
//--------------------------------------------------------------------------
void SetScaleZero(void)
{
	DWORD DW;
	//---
	DW.F = ADC_SCALE[ADC_TH]; mDB_rMAP[SA_TH] = DW.W[0]; mDB_rMAP[SA_TH+1] = DW.W[1];
	DW.F = ADC_SCALE[ADC_TL]; mDB_rMAP[SA_TL] = DW.W[0]; mDB_rMAP[SA_TL+1] = DW.W[1];
	DW.F = ADC_SCALE[ADC_VO]; mDB_rMAP[SA_VO] = DW.W[0]; mDB_rMAP[SA_VO+1] = DW.W[1];
	DW.F = ADC_SCALE[ADC_CU]; mDB_rMAP[SA_CU] = DW.W[0]; mDB_rMAP[SA_CU+1] = DW.W[1];
	mDB_rMAP[ZA_TH] = ADC_ZERO[ADC_TH];
	mDB_rMAP[ZA_TL] = ADC_ZERO[ADC_TL];
	mDB_rMAP[ZA_VO] = ADC_ZERO[ADC_VO];
	mDB_rMAP[ZA_CU] = ADC_ZERO[ADC_CU];
}
//--------------------------------------------------------------------------
// 1.0 = 00,0C,00,02,04,3F,80,00,00
// 1.2 = 00,0C,00,02,04,3F,99,99,9A
// 1.5 = 00,0C,00,02,04,3F,C0,00,00
// 1.7 = 00,0C,00,02,04,3F,D9,99,9A
void Config_Init(void)
{
	ADC_SCALE[0] = 1.0;
	ADC_SCALE[1] = 1.0;
	ADC_SCALE[2] = 1.0;
	ADC_SCALE[3] = 1.0;
	ADC_ZERO[0] = 0;
	ADC_ZERO[1] = 0;
	ADC_ZERO[2] = 0;
	ADC_ZERO[3] = 0;
	SetScaleZero();
}
//--------------------------------------------------------------------------
int Config_Write(void)
{
	WTYPE WB;
	DWORD DW;
	unsigned int i = 0, j = 0, k = 0;
	unsigned char sDa[50] = {0};
	unsigned char cDa[50] = {0};
	//---
	Erase_IAP(IAP_Addr);
	memset(sDa, 0, 50);
	memset(cDa, 0, 50);
	GetScaleZero();
	j = 2;
	DW.F = ADC_SCALE[ADC_TH]; sDa[j++] = DW.B[3]; sDa[j++] = DW.B[2]; sDa[j++] = DW.B[1]; sDa[j++] = DW.B[0];
	DW.F = ADC_SCALE[ADC_TL]; sDa[j++] = DW.B[3]; sDa[j++] = DW.B[2]; sDa[j++] = DW.B[1]; sDa[j++] = DW.B[0];
	DW.F = ADC_SCALE[ADC_VO]; sDa[j++] = DW.B[3]; sDa[j++] = DW.B[2]; sDa[j++] = DW.B[1]; sDa[j++] = DW.B[0];
	DW.F = ADC_SCALE[ADC_CU]; sDa[j++] = DW.B[3]; sDa[j++] = DW.B[2]; sDa[j++] = DW.B[1]; sDa[j++] = DW.B[0];
	WB.W = ADC_ZERO[ADC_TH];  sDa[j++] = WB.B[1]; sDa[j++] = WB.B[0];
	WB.W = ADC_ZERO[ADC_TL];  sDa[j++] = WB.B[1]; sDa[j++] = WB.B[0];
	WB.W = ADC_ZERO[ADC_VO];  sDa[j++] = WB.B[1]; sDa[j++] = WB.B[0];
	WB.W = ADC_ZERO[ADC_CU];  sDa[j++] = WB.B[1]; sDa[j++] = WB.B[0];
	sDa[0] = 0x5A; sDa[1] = 0xA5;
	for(i = 0; i < j; i++) Write_IAP(IAP_Addr+i, sDa[i]);
	for(i = 0; i < j; i++) cDa[i] =  Read_IAP(IAP_Addr+i);
	//---
	k = 0;
	for(i = 0; i < j; i++) if(cDa[j] != sDa[j]) k++;
	//---
	return(k);
}
//--------------------------------------------------------------------------
void Config_Read(void)
{
	WTYPE WB;
	DWORD DW;
	unsigned int i = 0, j = 0, k = 0;
	unsigned char sDa[50] = {0};
	unsigned char cDa[50] = {0};
	//---
	for(i=0;i<50;i++) sDa[i] = Read_IAP(IAP_Addr+i);
	//
	if((sDa[0] == 0x5A)&&(sDa[1] == 0xA5)){
		j = 2;
		DW.B[3] = sDa[j++]; DW.B[2] = sDa[j++]; DW.B[1] = sDa[j++]; DW.B[0] = sDa[j++]; ADC_SCALE[ADC_TH] = DW.F;
		DW.B[3] = sDa[j++]; DW.B[2] = sDa[j++]; DW.B[1] = sDa[j++]; DW.B[0] = sDa[j++]; ADC_SCALE[ADC_TL] = DW.F;
		DW.B[3] = sDa[j++]; DW.B[2] = sDa[j++]; DW.B[1] = sDa[j++]; DW.B[0] = sDa[j++]; ADC_SCALE[ADC_VO] = DW.F;
		DW.B[3] = sDa[j++]; DW.B[2] = sDa[j++]; DW.B[1] = sDa[j++]; DW.B[0] = sDa[j++]; ADC_SCALE[ADC_CU] = DW.F;
		WB.B[1] = sDa[j++]; WB.B[0] = sDa[j++]; ADC_ZERO[ADC_TH] = WB.W;
		WB.B[1] = sDa[j++]; WB.B[0] = sDa[j++]; ADC_ZERO[ADC_TL] = WB.W;
		WB.B[1] = sDa[j++]; WB.B[0] = sDa[j++]; ADC_ZERO[ADC_VO] = WB.W;
		WB.B[1] = sDa[j++]; WB.B[0] = sDa[j++]; ADC_ZERO[ADC_CU] = WB.W;
		//---
		SetScaleZero();
	} else {
		Config_Init();
		Config_Write();
	}
}
//--------------------------------------------------------------------------
void ADC_Updata(void)
{
	int i = 0;
	DWORD DW;
	//---
	i = (1024 - ADC_BUFF[ADC_TH]) / 4; if(i >=249) i = 249; mDB.TH = (float)NTC_Table[i];
	i = (1024 - ADC_BUFF[ADC_TL]) / 4; if(i >=249) i = 249; mDB.TL = (float)NTC_Table[i];
//	mDB.TH = (ADC_BUFF[ADC_TH] * ADC_SCALE[ADC_TH]) + ADC_ZERO[ADC_TH];
//	mDB.TL = (ADC_BUFF[ADC_TL] * ADC_SCALE[ADC_TL]) + ADC_ZERO[ADC_TL];
	mDB.VO = (ADC_BUFF[ADC_VO] * ADC_SCALE[ADC_VO]) + ADC_ZERO[ADC_VO];
	mDB.CU = (ADC_BUFF[ADC_CU] * ADC_SCALE[ADC_CU]) + ADC_ZERO[ADC_CU];
	//---
	DW.F = mDB.TH; mDB_iMAP[MA_TH] = DW.W[0]; mDB_iMAP[MA_TH+1] = DW.W[1];
	DW.F = mDB.TL; mDB_iMAP[MA_TL] = DW.W[0]; mDB_iMAP[MA_TL+1] = DW.W[1];
	DW.F = mDB.VO; mDB_iMAP[MA_VO] = DW.W[0]; mDB_iMAP[MA_VO+1] = DW.W[1];
	DW.F = mDB.CU; mDB_iMAP[MA_CU] = DW.W[0]; mDB_iMAP[MA_CU+1] = DW.W[1];
}
//--------------------------------------------------------------------------
void main( void )
{
	DWORD DW;
	int i = 0;
	idata Type_ModbusRTU 	DaA;
	//---
	Ser_OSC();
	//---
    Initial_Timer2();
	Initial_UART0(BR_9600);
	IO_Map_Init();
	Initial_ADC(0);
    EA=1;
	LED1_FG = 0;
	LED2_FG = 0;
	LED_OnOff(1, 0);
	LED_OnOff(2, 0);
    //---
	RF_Set(0x98);
	Config_Read();
    Tx1_FG = 0;
	Rx1_FG = 0;
	Rx1_CP = 0;
    //---
#if(MB_MT)
	mDB.TH = 0.0;
	mDB.TL = 0.0;
	mDB.VO = 0.0;
	mDB.CU = 0.0;
	mDB.Do = 0;
#else
	mDB.TH = 70.0;
	mDB.TL = 30.0;
	mDB.VO = 1.5;
	mDB.CU = 0.5;
	mDB.Do = 0x003F;
	mDB.ST = 0x0;
#endif
	//---
	DaA.ID  = RTU_aID;
	DaA.CMD = RTU_CMD;
	DaA.Add = RTU_Addr;
	DaA.No  = RTU_Len;
	//---
	WDT_INIT();
	//---
    while(1){
		//---
        if(Rx1_CP){
        	Rx1_CP = 0;
#if(MB_MT)
			RX_M_MODBUS_RTU(1, Rx1_tBuf, Rx1_tCNT);
			//---
			mDB.ST  = mDB_iMAP[MA_STATE];
			mDB.Do  = mDB_iMAP[MA_SET] = mDB_rMAP[MA_SET];
			DW.W[0] = mDB_iMAP[MA_TH]; DW.W[1] = mDB_iMAP[MA_TH+1]; mDB.TH = DW.F;
			DW.W[0] = mDB_iMAP[MA_TL]; DW.W[1] = mDB_iMAP[MA_TL+1]; mDB.TL = DW.F;
			DW.W[0] = mDB_iMAP[MA_VO]; DW.W[1] = mDB_iMAP[MA_VO+1]; mDB.VO = DW.F;
			DW.W[0] = mDB_iMAP[MA_CU]; DW.W[1] = mDB_iMAP[MA_CU+1]; mDB.CU = DW.F;
#else
			RX_S_MODBUS_RTU(1, Rx1_Buf, Rx1_CNT);
			if(Rx_Addr >= SA_TH) Config_Write();
#endif
//			Conn1_FG = 1;
		}
		//---
		if(FG_T10mS){
			FG_T10mS = 0;
			switch(ADC_SEL){
				case ADC_TH: Select_ADC(ADC_TH); ADC_BUFF[ADC_TH] = Read_ADC(); ADC_SEL = ADC_TL; break;
				case ADC_TL: Select_ADC(ADC_TL); ADC_BUFF[ADC_TL] = Read_ADC(); ADC_SEL = ADC_VO; break;
				case ADC_VO: Select_ADC(ADC_VO); ADC_BUFF[ADC_VO] = Read_ADC(); ADC_SEL = ADC_CU; break;
				case ADC_CU: Select_ADC(ADC_CU); ADC_BUFF[ADC_CU] = Read_ADC(); ADC_SEL = ADC_UD; break;
				case ADC_UD: ADC_Updata(); ADC_SEL = ADC_TH;
					mDB.Do = mDB_rMAP[MA_SET];
					IO_InOut((unsigned char)mDB.Do);
					mDB_iMAP[MA_STATE] = mDB.Do;
					break;
//				default: break;
			}
			//---
		}
		//---
		if(FG_T100mS){
			FG_T100mS = 0;
			//---
			LED1_FG++;
			if(LED1_FG >= 10){
				LED1_FG = 0;
				LED_OnOff(1, 0);
			} else if(LED1_FG == 5){
				LED_OnOff(1, 1);
			}
		}
		//---
		if(FG_T1S){
			FG_T1S = 0;
			//---
#if(MB_MT)
			TX_M_MODBUS_RTU(1, DaA);
#endif
			//---
/*
			Not_Conn++;
			//---
			if(Not_Conn >= 10){
				Not_Conn = 0;
			}
*/
		}
		//---
		WDTCR |= CLW;
    }
}
//--------------------------------------------------------------------------
// End of File
