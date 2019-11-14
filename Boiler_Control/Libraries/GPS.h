//============================================================================
// File Name          : GPS.h
// Author             : SunKyung
// Version            : V1.0
// HomePage           : http://sunkyung.iptime.org
// Date               : 11/02/2017
// Description        : Sikhoon J.
//============================================================================
#ifndef _GPS_H
#define _GPS_H
//--------------------------------------------------------------------------
#include "NMEA.h"
//--------------------------------------------------------------------------
extern bit rRMC_FG;
extern bit rZDA_FG;
//--------------------------------------------------------------------------
extern TypeGGA rGGA;
extern TypeGSA rGSA;
extern TypeGSV rGSV;
extern TypeRMC rRMC;
extern TypeVTG rVTG;
extern TypeZDA rZDA;
//--------------------------------------------------------------------------
int GPS_NMEA_Conver(char*, int);
//--------------------------------------------------------------------------
#endif
//============================================================================
// End of File
