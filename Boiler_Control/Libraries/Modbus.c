//--------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------
#include <string.h>
#include "Modbus.h"
#include "Uart.h"
#include "crc16.h"
//--------------------------------------------------------------------------
xdata unsigned short mDB_rMAP[MAP_MAX];
xdata unsigned short mDB_iMAP[MAP_MAX];
idata unsigned short Tx_Addr  = 0;
idata unsigned short Rx_Addr = 0;
//---
#if(MB_MT)
//--------------------------------------------------------------------------
int TX_M_MODBUS_RTU(unsigned char Ch, Type_ModbusRTU Da)
{
	int j = 0;
	WTYPE	WD;
	unsigned char Buf[20] = {0};
	//
	j = 0;
	Buf[j++] = Da.ID;
	Buf[j++] = Da.CMD;
//	WD.W = Da.Add-1;
	if(Ch == 2) Tx_Addr = Da.Add;
	WD.W = Da.Add;
	Buf[j++] = WD.B[0];
	Buf[j++] = WD.B[1];
	WD.W = Da.No;
	Buf[j++] = WD.B[0];
	Buf[j++] = WD.B[1];
	WD.W = CRC16(Buf, j);
	Buf[j++] = WD.B[0];
	Buf[j++] = WD.B[1];
	//---
	if(Ch == 2){
#if(Uart2)
		Tx2_Len = (unsigned char)j;
		memset(Tx2_Buf, 0, Tx2_Size);
		memcpy(Tx2_Buf, Buf, Tx2_Len);
		Tx2_CNT = 0;
//		DIR1 = 1;
		Tx2_FG = 1;
#endif
	} else {
#if(Uart1)
		Tx1_Len = (unsigned char)j;
		memset(Tx1_Buf, 0, Tx1_Size);
		memcpy(Tx1_Buf, Buf, Tx1_Len);
		Tx1_CNT = 0;
//		DIR0 = 1;
		Tx1_FG = 1;
#endif
	}
	return j;
}
//--------------------------------------------------------------------------
char RX_M_MODBUS_RTU(unsigned char Ch, unsigned char *Da, unsigned char sLen)
{
	WTYPE WB;
//	DWORD DW;
	idata unsigned int  i = 0, k = 0;
	idata unsigned char j = 0;
	idata unsigned char rID  = 0;
	idata unsigned char CMD  = 0;
	idata unsigned int  rADD = 0;
	idata unsigned char rLEN = 0;
	//---
	if(Ch == 2) rID = RTU_aID; else rID = RTU_aID;
	//---
	i = VerifyCRC(Da, sLen);
	if(i && (Da[0] == rID)){
		j = 1;
		CMD = Da[j++];
		//
		i = 0;
		switch(CMD){
			//--- Bit
			case 0x01:
				
				break;
			case 0x02:
				
				break;
			case 0x05:
				
				break;
			//--- Word
			case 0x03:
				rLEN = Da[j++]/2;
				for(i=0; i<rLEN; i++){
					WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; mDB_rMAP[i + Tx_Addr] = WB.W;
				}
				break;
			case 0x04:
				rLEN = Da[j++]/2;
				for(i=0; i<rLEN; i++){
					WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; mDB_iMAP[i + Tx_Addr] = WB.W;
				}
				break;
			case 0x06:
				WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; rADD = WB.W;	// Address
				WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; rLEN = WB.W;	// Len
				mDB_rMAP[rADD] = rLEN;
				break;
			case 0x10:
				WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; rADD = WB.W;	// Address
				WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; rLEN = WB.W;	// Len
				break;
			default: i = 0; break;
		}
	} else j = -1;
	return (j);
}
#else
//--------------------------------------------------------------------------
char RX_S_MODBUS_RTU(unsigned char Ch, unsigned char *Da, unsigned char sLen)
{
	WTYPE WB;
	idata unsigned int  i = 0, k = 0;
	idata unsigned char j = 0;
	idata unsigned char CMD  = 0;
	idata unsigned char rID  = 0;
	idata unsigned int  rADD = 0;
	idata unsigned char rLEN = 0;
	xdata unsigned char Buf[40] = {0};
	//---
	if(Ch == 2) rID = RTU_aID; else rID = RTU_aID;
	//---
	i = VerifyCRC(Da, sLen);
	if(i && (Da[0] == rID)){
		memset(Buf, 0, 40);
		j = 1;
		Buf[0] = rID;
		CMD = Da[j++];
		Buf[1] = CMD;
		WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; Rx_Addr = rADD = WB.W;	// Address
		WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; rLEN = WB.W;	// Len
		//
		k = 2;
		switch(CMD){
			case 0x01:
				
				break;
			case 0x02:
				
				break;
			case 0x05:
				
				break;
			case 0x03:
				Buf[k++] = rLEN * 2;
				for(i=0;i<rLEN;i++){
					WB.W = mDB_rMAP[i + rADD]; Buf[k++] = WB.B[0]; Buf[k++] = WB.B[1];
				}
				break;
			case 0x04:
				Buf[k++] = rLEN * 2;
				for(i=0;i<rLEN;i++){
					WB.W = mDB_iMAP[i + rADD]; Buf[k++] = WB.B[0]; Buf[k++] = WB.B[1];
				}
				break;
			case 0x06:
				mDB_rMAP[rADD] = rLEN;
				WB.W = rADD; Buf[k++] = WB.B[0]; Buf[k++] = WB.B[1];
				WB.W = rLEN; Buf[k++] = WB.B[0]; Buf[k++] = WB.B[1];
				break;
			case 0x10:
				j++;
				for(i=0;i<rLEN;i++){
					WB.B[0] = Da[j++]; WB.B[1] = Da[j++]; mDB_rMAP[i + rADD] = WB.W;
				}
				WB.W = rADD; Buf[k++] = WB.B[0]; Buf[k++] = WB.B[1];
				WB.W = rLEN; Buf[k++] = WB.B[0]; Buf[k++] = WB.B[1];
				break;
			default: Buf[1] = CMD + 0x80; break;
		}
		//---
		WB.W = CRC16(Buf, k);
		Buf[k++] = WB.B[0];
		Buf[k++] = WB.B[1];
		//---
		if(Ch == 2){
#if(Uart2)
			Tx2_Len = (unsigned char)k;
			memset(Tx2_Buf, 0, Tx2_Size);
			memcpy(Tx2_Buf, Buf, Tx2_Len);
			Tx2_CNT = 0;
//			DIR1 = 1;
			Tx2_FG = 1;
#endif
		} else {
#if(Uart1)
			Tx1_Len = (unsigned char)k;
			memset(Tx1_Buf, 0, Tx1_Size);
			memcpy(Tx1_Buf, Buf, Tx1_Len);
			Tx1_CNT = 0;
//			DIR0 = 1;
			Tx1_FG = 1;
#endif
		}
	} else j = -1;
	return (j);
}
#endif
//--------------------------------------------------------------------------
// End of File
