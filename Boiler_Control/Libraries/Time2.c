//--------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------
#include <string.h>
#include "REG_MG82FG5Bxx.h"
#include "Define.h"
#include "Time2.h"
#include "Uart.h"
//--------------------------------------------------------------------------
bit FG_T10mS = 0;
bit FG_T100mS = 0;
bit FG_T1S = 0;
//
idata unsigned char T_10mS = 0;
idata unsigned char T_100m = 0;
idata unsigned char  T_Sec  = 0;
//
idata unsigned int  D_10m  = 0;
idata unsigned int  D_100m  = 0;
idata unsigned int  D_1Sec  = 0;
//
#if(Uart1)
	idata unsigned char Tx1_InCNT = 0;
#endif
#if(Uart2)
	idata unsigned char Tx2_InCNT = 0;
#endif
//
idata unsigned int T_delay = 0;

//--------------------------------------------------------------------------
void delay(unsigned int t)
{	   
    T_delay=0;
    while(T_delay<t);
}
//--------------------------------------------------------------------------
void Initial_Timer2(void)
{
	WTYPE	WD;
	T2CON = 0x00;
	T2MOD = 0x00;
	PCON0 |= 0x80;
	WD.W = (unsigned int)(0x10000-((Xtal_Freq/12)/T2_Tg_Val));
	RCAP2H = WD.B[0];
	RCAP2L = WD.B[1];
	TF2  = 0;
	TR2  = 1;							// timer 2 double
	PT2L  = 1;
	ET2  = 1;
}
//--------------------------------------------------------------------------
// 타이머 인터럽트 1mSec 마다 timer_cnt 증가
void Ref_Timer(void) interrupt 5 using 2
{
	idata unsigned char c = 0;
	idata unsigned char  bkSFRPI = 0;
	//---
	TF2 = 0;
    T_delay++;
    //--- 
#if(Uart1)
    if(Tx1_FG){
        Tx1_InCNT++;
        if(Tx1_InCNT >= Tx1_Interval){
            Tx1_InCNT = 0;
            if(Tx1_CNT < Tx1_Len){
        		c = Tx1_Buf[Tx1_CNT];
				bkSFRPI = SFRPI;
				SFRPI = 0x00;
        		S0BUF = c;
				SFRPI = bkSFRPI;
				Tx1_CNT++;
    		} else {
    			Tx1_FG = 0;
//    			DIR0 = 0;
    		}
        }
    }
	//---
    if(Rx1_FG){
    	Rx1_Time++;
    	if(Rx1_Time > 6){	// 6mSec
    		Rx1_FG = 0;
			Rx1_tCNT = Rx1_CNT;
			memcpy(Rx1_tBuf, Rx1_Buf, Rx1_tCNT);
    		Rx1_CP = 1;
    	}
    }
#endif
    //---
#if(Uart2)
    if(Tx2_FG){
        Tx2_InCNT++;
        if(Tx2_InCNT >= Tx2_Interval){
            Tx2_InCNT = 0;
			if(Tx2_CNT < Tx2_Len){
				c = Tx2_Buf[Tx2_CNT];
				bkSFRPI = SFRPI;
				SFRPI = 0x01;
				S1BUF = c;
				SFRPI = bkSFRPI;
				Tx2_CNT++;
			} else {
				Tx2_FG = 0;
//				DIR1 = 0;
			}
		}
    }
	//---
    if(Rx2_FG){
    	Rx2_Time++;
    	if(Rx2_Time > 6){
    		Rx2_FG = 0;
			Rx2_tCNT = Rx2_CNT;
			memcpy(Rx2_tBuf, Rx2_Buf, Rx2_tCNT);
    		Rx2_CP = 1;
    	}
    }
#endif
    //---
    T_10mS++;
	if(T_10mS >= 10){
		T_10mS = 0;
		D_10m--;
		FG_T10mS = 1;
		T_100m++;
		if(T_100m >= 10){
			T_100m = 0;
			D_100m--;
			FG_T100mS = 1;
			T_Sec++;
			if(T_Sec >= 10){
				T_Sec = 0;
				D_1Sec--;
				FG_T1S = 1;
			}
		}
	}
}
//--------------------------------------------------------------------------
// End of File
