/*--------------------------------------------------------------------------
* File Name          : isr.c
* Author             : SunKyung
* Version            : V1.0
* HomePage           : http://sunkyung.iptime.org
* Date               : 09/03/2013
* Description        : Sikhoon J.
--------------------------------------------------------------------------*/
// Master/Slave
#include "REG_MG82FG5Bxx.h"
#include <string.h>
#include <stdio.h>
#include "SPI.h"
#include "SetDRV.h"
#include "Time2.h"
//--------------------------------------------------------------------------
#define Mode_Master		0
//--------------------------------------------------------------------------
//void Dir_SPI(char i);
//---
//unsigned char SPI_ID = 0;
bit SPI_Rx_FG = 0;
//bit SPI_Rx_CP = 0;
bit SPI_Tx_FG = 0;
bit SPI_Tx_CP = 0;	// transmit_completed
bit SPI_Tx_m1CP = 0;	// transmit_completed
bit SPI_Tx_m2CP = 0;	// transmit_completed
idata char SPI_C_Code = 0;
idata char SPI_RxCNT = 0;
idata char SPI_TxCNT = 0;
idata unsigned char CH_Code;
idata unsigned char CMD_Code;
idata unsigned char SPI_tBUF_SIZE = 0;
//idata unsigned char SPI_tBUF_NO = 0;
unsigned char SPI_rBuff[SPI_rBUF_SIZE];
unsigned char SPI_taBuff[SPI_taBUF_NO][SPI_taBUF_SIZE];
unsigned char SPI_tbBuff[SPI_tbBUF_NO][SPI_tbBUF_SIZE];
//--------------------------------------------------------------------------
#if(uGAS)
	extern idata bit  C2_cgRun_FG;
	extern idata bit  C2_Run_FG;
#endif
#if(uWater)
	extern idata bit  C1_Run_FG;
	extern idata bit  C1_Pump_FG;
	extern idata bit  C1_Moni_FG;
	extern idata bit  C2_Run_FG;
	extern idata bit  C2_Pump_FG;
	extern idata bit  C2_Moni_FG;
#endif
//--------------------------------------------------------------------------
void it_SPI(void) interrupt 8 using 1	// interrupt address is 0x004B
{
    idata unsigned char i = 0, j = 0;
	idata unsigned char c = 0;
	//---
//	CPU = ~CPU;
	if(SPSTAT & SPIF){
		SPI_Tx_CP = 1;
		c = SPDAT;
//		SPSTAT |= SPIF;
		//---
		if(c == 0x28){
			memset(SPI_rBuff, 0, SPI_rBUF_SIZE);
			SPI_Tx_FG = 0;
			SPI_Rx_FG = 1;
			SPI_RxCNT = 0;
			SPI_rBuff[SPI_RxCNT++] = c;
		} else if((c == 0x29) && SPI_Rx_FG){
			SPI_rBuff[SPI_RxCNT++] = c;
			SPI_Rx_FG = 0;
#if(uGAS)
			if(SPI_rBuff[2] == '1'){
				if(SPI_rBuff[1] & 0x20){
					SPI_rBuff[1] &= 0xDF;
					if(SPI_rBuff[1] == SPI_UART2_ID){
						if(C2_Run_FG == 0) C2_cgRun_FG = 1;
						C2_Run_FG = 1;	// Run
					}
					CPU = 1;
				} else {
					if(SPI_rBuff[1] == SPI_UART2_ID){
						if(C2_Run_FG == 1) C2_cgRun_FG = 1;
						C2_Run_FG = 0;	// Stop
					}
					CPU = 0;
				}
			}
#endif
//---
#if(uWater)
			if(SPI_rBuff[2] == '1'){
				if(SPI_rBuff[1] & 0x20){
					SPI_rBuff[1] &= 0xDF;
					if(SPI_rBuff[1] == SPI_UART1_ID){
//						if(C1_Pump_FG == 0) C1_Run_FG = 1;
						if(C1_Moni_FG == 0) C1_Run_FG = 1;
						C1_Pump_FG = 1;		// Run
					} else if(SPI_rBuff[1] == SPI_UART2_ID){
//						if(C2_Pump_FG == 0) C2_Run_FG = 1;
						if(C2_Moni_FG == 0) C2_Run_FG = 1;
						C2_Pump_FG = 1;		// Run
					}
					CPU = 1;
				} else {
					if(SPI_rBuff[1] == SPI_UART1_ID){
//						if(C1_Pump_FG) C1_Run_FG = 1;
						if(C1_Moni_FG) C1_Run_FG = 1;
						C1_Pump_FG = 0;		// Stop
					} else if(SPI_rBuff[1] == SPI_UART2_ID){
//						if(C2_Pump_FG) C2_Run_FG = 1;
						if(C2_Moni_FG) C2_Run_FG = 1;
						C2_Pump_FG = 0;		// Stop
					}
					CPU = 0;
				}
			}
#endif
			if((SPI_rBuff[1] == SPI_UART1_ID) || (SPI_rBuff[1] == SPI_UART2_ID)){
				SPI_tCNT = 0;
					CH_Code  = SPI_rBuff[1];
					CMD_Code = SPI_rBuff[2] - 0x31;
//					P1M0 |= 0x40;
					if(CH_Code == SPI_UART1_ID){
						SPI_tBUF_SIZE = SPI_taBUF_SIZE;
//						SPI_tBUF_NO = SPI_taBUF_NO - 1;
						SPI_Tx_m1CP = 0;
					} else {
						SPI_tBUF_SIZE = SPI_tbBUF_SIZE;
//						SPI_tBUF_NO = SPI_tbBUF_NO - 1;
						SPI_Tx_m2CP = 0;
					}
					SPI_Tx_CP = 0;
					SPI_TxCNT = 0;
					SPI_Tx_FG = 1;
					goto Loop_SPI1;
		//		}
			} else {
				SPI_Rx_FG = 0;
				SPI_Tx_FG = 0;
			}
		} else {
			if(SPI_Tx_FG){
Loop_SPI1:		if(CH_Code == SPI_UART1_ID)
					c = SPI_taBuff[CMD_Code][SPI_TxCNT];
				else 
					c = SPI_tbBuff[CMD_Code][SPI_TxCNT];
				SPDAT = c;
				SPI_TxCNT++;
				if(CMD_Code == 1){
					i++;
				}
				//---
				if((c == 0x0A)||(SPI_TxCNT >= SPI_tBUF_SIZE)) {
	//				P1M0 &= 0xBF;
	//				SPSTAT |= SPIF;
//					SPI_tCNT = 0;
					SPI_Tx_FG = 0;
					if(c == 0x0A){
						SPI_Tx_CP = 1;
						if((CH_Code == SPI_UART1_ID)&&(CMD_Code == (SPI_taBUF_NO - 1))){
							SPI_Tx_m1CP = 1;
						} else if((CH_Code == SPI_UART2_ID)&&(CMD_Code == (SPI_tbBUF_NO - 1))){
							SPI_Tx_m2CP = 1;
						}
					}
				}
			} else if(SPI_Rx_FG){
				if(SPI_RxCNT >= SPI_rBUF_SIZE) SPI_Rx_FG = 0;
				else SPI_rBuff[SPI_RxCNT++] = c;
			} // else P1M0 &= 0xBF;
		}
	} // else 
	SPSTAT |= SPIF;
//	SPI_tCNT = 0;
}
//--------------------------------------------------------------------------
void init_SPI(void)
{
#if (Mode_Master)
//	SPCON = (SPEN | MSTR);	//  | SPR1 | SPR0
//	P1M0 |= 0xA0;
//	P2M0 |= 0x0F;
//	SPI_SELECTOR(0x0F);
#else
	AUXR1 &= ~0x20;
	SPCON = (SPEN | CPOL);
//	SPCON = SPEN;
//	SPSTAT |= 0x01;
//	P1M0 &= 0x0F;
	EIE1 |=  ESPI;
	//---
//	SPI_Rx_FG = 0;
//	SPI_Tx_FG = 0;
//	SPI_Tx_CP = 0;
#endif
	P1M0 &= 0xBF;
	CPU = 1;
}
//--------------------------------------------------------------------------
// End of File
