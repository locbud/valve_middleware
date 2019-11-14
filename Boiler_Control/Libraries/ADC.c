//--------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------
#include <string.h>
#include "REG_MG82FG5Bxx.h"
#include "Define.h"
#include "ADC.h"
//--------------------------------------------------------------------------
idata unsigned char   ADC_SEL = 0;
idata unsigned short  ADC_BUFF[4]  = {0};
idata float ADC_SCALE[4] = {1.0};
idata char  ADC_ZERO[4]  = {0};
//--------------------------------------------------------------------------
void Initial_ADC(char c)
{
	P1AIO = 0x0F;
	ADCFG0 = ADCKS1 | ADCKS0 | ADRJ;
	ADCFG1 = 0;
	ADCON0 = ADCEN;
	if(c) EIE1 |=  EADC;
}
//--------------------------------------------------------------------------
// 타이머 인터럽트 1mSec 마다 timer_cnt 증가
void RD_ADC(void) interrupt 9	// using 2
{
	idata unsigned short  ADC_BUF =  0;
	idata unsigned char c = 0;
	//---
	ADCON0 &= ~ADCS;
	ADC_BUF = ((ADCDH & 0x03) << 8) + ADCDL; 
	//---
	ADC_BUFF[ADC_SEL] = ADC_BUF;
	ADC_SEL++; if(ADC_SEL >= 4) ADC_SEL = 0;
	ADCON0 &= 0xF8; 	ADCON0 |= ADC_SEL;
}
//--------------------------------------------------------------------------
void Start_ADC(void)
{
	ADCON0 |= ADCS;
}
//--------------------------------------------------------------------------
unsigned short Read_ADC(void)
{
	idata unsigned short  ADC_BUF =  0;
	//---
	ADCON0 |= 0x08;
	while(!(ADCON0 & 0x10));			//wait ADC finish conversion
	ADC_BUF = ((ADCDH & 0x03) << 8) + ADCDL; 
	ADCON0 &= 0xEF;						//clear ADC interrupt flag
	//---
	return(ADC_BUF);
}
//--------------------------------------------------------------------------
void Select_ADC(unsigned char c)
{
	unsigned int i = 0;
	//---
	ADCON0 &= 0xF8;
	ADCON0 |= c;
	i = 1000; while(i--);
	ADCON0 |= ADCS;
}
//--------------------------------------------------------------------------
// End of File
