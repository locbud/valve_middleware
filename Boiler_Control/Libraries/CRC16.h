//=============================================================================
//
//=============================================================================
#ifndef __CRC16_H
#define __CRC16_H
//-----------------------------------------------------------------------------
//- Private function prototypes
unsigned int CRC16(unsigned char*, unsigned int);
char VerifyCRC(unsigned char*, unsigned int);
unsigned char CheckSUM(char, unsigned char*, unsigned int);
//( 0 = VerifySUM | 1= CreateSUM,  Data, Data Len)
//-----------------------------------------------------------------------------
#endif
//=============================================================================
// End of File
