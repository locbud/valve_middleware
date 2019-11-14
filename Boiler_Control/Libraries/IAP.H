/*--------------------------------------------------------------------------
* File Name          : IAP.c
* Author             : SunKyung
* Version            : V1.0
* HomePage           : http://sunkyung.iptime.org
* Date               : 09/03/2013
* Description        : Sikhoon J.
--------------------------------------------------------------------------*/
#ifndef __IAP_H
#define __IAP_H
//--------------------------------------------------------------------------
void Erase_IAP(unsigned int);
void Write_IAP(unsigned int, unsigned char);
unsigned char Read_IAP(unsigned int);
void PageP_Write(unsigned int, unsigned char);
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
// End of File

