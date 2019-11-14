//--------------------------------------------------------------------------
// File Name		: HW_Define.c
// Author			: SunKyung
// Version			: V1.0
// HomePage			: 
// Date				: 11/01/2017
// Description		: Sikhoon J.
//--------------------------------------------------------------------------
#ifndef __ADC_H
#define __ADC_H
//--------------------------------------------------------------------------
extern idata unsigned char  ADC_SEL;
extern idata unsigned short ADC_BUFF[];
extern idata float ADC_SCALE[];
extern idata char  ADC_ZERO[];
//--------------------------------------------------------------------------
void Initial_ADC(char);
void Start_ADC(void);
//---
unsigned short Read_ADC(void);
void Select_ADC(unsigned char);
//--------------------------------------------------------------------------
#endif
// End of File

