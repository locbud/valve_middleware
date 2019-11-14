//--------------------------------------------------------------------------
#ifndef __WATERMODBUS_H
#define __WATERMODBUS_H
//--------------------------------------------------------------------------
#include "Define.h"
//--------------------------------------------------------------------------
extern xdata unsigned short mDB_rMAP[];
extern xdata unsigned short mDB_iMAP[];
extern idata unsigned short Tx_Addr;
extern idata unsigned short Rx_Addr;
//--------------------------------------------------------------------------
#if(MB_MT)
int TX_M_MODBUS_RTU(unsigned char, Type_ModbusRTU);
char RX_M_MODBUS_RTU(unsigned char, unsigned char*, unsigned char);
#else
char RX_S_MODBUS_RTU(unsigned char, unsigned char*, unsigned char);
#endif
//--------------------------------------------------------------------------
#endif
// End of File
