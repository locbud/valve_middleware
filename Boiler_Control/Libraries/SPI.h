/*--------------------------------------------------------------------------
* File Name          : SPI.h
* Author             : SunKyung
* Version            : V1.0
* HomePage           : http://sunkyung.iptime.org
* Date               : 09/03/2015
* Description        : Sikhoon J.
--------------------------------------------------------------------------*/
#ifndef __SPI_H
#define __SPI_H
//#define __SPI_Hunsigned char SPI_ID = 0;
//--------------------------------------------------------------------------
#include "Define.H"
//--------------------------------------------------------------------------
#define SPI_MASTER_MODE		0
//
extern bit SPI_Rx_FG;
extern bit SPI_Rx_CP;
extern bit SPI_Tx_FG;
extern bit SPI_Tx_CP;
extern bit SPI_Tx_m1CP;
extern bit SPI_Tx_m2CP;
//---
extern idata unsigned char CH_Code;
//---
extern unsigned char SPI_rBuff[];
extern unsigned char SPI_taBuff[][SPI_taBUF_SIZE];
extern unsigned char SPI_tbBuff[][SPI_tbBUF_SIZE];
//--------------------------------------------------------------------------
void init_SPI(void);
//--------------------------------------------------------------------------
#endif
// End of File
