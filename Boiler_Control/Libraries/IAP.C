/*--------------------------------------------------------------------------
* File Name          : IAP.c
* Author             : SunKyung
* Version            : V1.0
* HomePage           : http://sunkyung.iptime.org
* Date               : 09/03/2013
* Description        : Sikhoon J.
--------------------------------------------------------------------------*/
#include "REG_MG82FG5Bxx.h"
//#include "Define.H"
#include "IAP.H"
//--------------------------------------------------------------------------
// Flash Erase One page (512 bytes)
//	Function: Erase_IAP()
void Erase_IAP(unsigned int IAP_Address)
{
	IFADRH = IAP_Address >> 8;					//IAP Flash Address High Byte
	IFADRL = IAP_Address & 0xFF;				//IAP Flash Address Low Byte
	IFMT  = 0x03;								//IAP Flash Mode Table (Erase Mode)
	ISPCR = 0x80;								//Enable IAP to change flash
	SCMD  = 0x46;								//Trigger IAP memory
	SCMD  = 0xB9;
}
//--------------------------------------------------------------------------
// Flash Write
//	Function: Write_IAP()
//  Write to IAP address one byte
void Write_IAP(unsigned int IAP_Address, unsigned char Value)
{
	IFADRH = IAP_Address >> 8;                  //IAP Flash Address High Byte
	IFADRL = IAP_Address & 0xFF;             	//IAP Flash Address Low Byte
	IFD = Value ;                               //Flash data buffer
	IFMT = 0x02 ;                               //IAP Flash Mode Table (Write Mode)
	ISPCR = 0x80 ;                              //Enable IAP to change flash
	SCMD = 0x46 ;
	SCMD = 0xB9 ;
}
//--------------------------------------------------------------------------
// Flash Read
//	Function: Read_IAP()
//  Read one byte from IAP address
unsigned char Read_IAP(unsigned int IAP_Address)
{
	IFADRH = IAP_Address >> 8;                  //IAP Flash Address High Byte
	IFADRL = IAP_Address & 0xFF;             	//IAP Flash Address Low Byte
	IFMT = 0x01;                                //IAP Flash Mode Table (Read Mode)
	ISPCR = 0x80;                               //Enable IAP to change flash
	SCMD = 0x46;
	SCMD = 0xB9;
    return(IFD);                                //Return Flash data
}
//--------------------------------------------------------------------------
void PageP_Write(unsigned int ad, unsigned char Dat)
{
	int i = 0;
	//---
	ISPCR	= 0x80;			// ISPEN = 1
	IFMT	= 0x04;			// PAGE P SFR Write
	IFADRH	= (unsigned char)(ad>>8);
	IFADRL	= (unsigned char)ad;
	IFD		= Dat;
	SCMD	= 0x46;
	SCMD	= 0xB9;
	for(i=0;i<0xFFFF;i++);	//wait XTAL circuit Stable
	for(i=0;i<0xFFFF;i++);
	IFMT	= 0x00;			// select SFR Standby Mode
	ISPCR	= 0x00;			// ISPEN = 0
}
//--------------------------------------------------------------------------
// End of File

