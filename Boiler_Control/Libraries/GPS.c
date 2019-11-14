//============================================================================
// File Name          : GPS.h
// Author             : SunKyung
// Version            : V1.0
// HomePage           : http://sunkyung.iptime.org
// Date               : 11/02/2017
// Description        : Sikhoon J.
//============================================================================
#include <string.h>
#include <stdlib.h>
#include "GPS.h"
//--------------------------------------------------------------------------
// NMEA Output Sentence ($GP)
char *NMEA_CMD[] ={
	"GGA\0", // Time, position and fix type data.
	"GSA\0", // GPS receiver operating mode, active satellites used in the position solution and DOP values.
	"GSV\0", // The number of GPS satellites in view satellite ID numbers, elevation, azimuth, and SNR values.
	"RMC\0", // Time, date, position, course and speed data. Recommended Minimum Navigation Information.
	"VTG\0", // Course and speed information relative to the ground.
	"ZDA\0", // Time & Date Information.
	"End\0"
};
//--------------------------------------------------------------------------
#define Buf_Size		15
bit rRMC_FG = 0;
bit rZDA_FG = 0;
//--------------------------------------------------------------------------
TypeGGA rGGA;
TypeGSA rGSA;
TypeGSV rGSV;
TypeRMC rRMC;
TypeVTG rVTG;
TypeZDA rZDA;
//--------------------------------------------------------------------------
// $GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65
void CMD_GGA_Conver(char *Da, int slen)
{
	int len = 0;
	int i = 0, j = 0, k = 0, ii = 0;
	char Buf[Buf_Size] = {0};
	//
	k = 0;
	//
	memset(Buf, 0, Buf_Size);
	for(i=0;i<slen;){
		memset(Buf, 0, Buf_Size);
		ii = 1;
		j = 0;
		while(ii){
			if(Da[i] == ','){ii = 0; k++;}
			if(Da[i] == '*'){ii = 0; i = slen;}
			if(i >= slen){ii = 0;}
			if(ii) Buf[j++] = Da[i];
			i++;
		}
		if(j>0){
			len = strlen(Buf);
			switch(k){
				case  1: memset(rGGA.UTC_Time, 0, 10); memcpy(rGGA.UTC_Time, Buf, len); break;
				case  2: rGGA.Latitude = atof(Buf); break;
				case  3: rGGA.NS_Indicator = Buf[0]; break;
				case  4: rGGA.Longitude = atof(Buf); break;
				case  5: rGGA.EW_Indicator = Buf[0]; break;
				case  6: rGGA.Position_Fix = Buf[0]; break;
				case  7: rGGA.Satellites_Used = (char)atoi(Buf); break;
				case  8: rGGA.HDOP = atof(Buf); break;
				case  9: rGGA.MSL_Altitude = atof(Buf); break;
				case 10: rGGA.Unit1 = Buf[0]; break;
				case 11: rGGA.Geoidal_Separation = atof(Buf); break;
				case 12: rGGA.Unit2 = Buf[0]; break;
				case 13: rGGA.Age_of_Diff_Corr = atoi(Buf); break;
				default: break;
			}
		}
//		k++;
	}
}
//--------------------------------------------------------------------------
// $GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00
void CMD_GSA_Conver(char *Da, int slen)
{
	int i = 0, j = 0, k = 0, ii = 0;
	char Buf[Buf_Size] = {0};
	//
	k = 0;
	//
	memset(Buf, 0, Buf_Size);
	for(i=0;i<slen;){
		memset(Buf, 0, Buf_Size);
		ii = 1;
		j = 0;
		while(ii){
			if(Da[i] == ','){ii = 0; k++;}
			if(Da[i] == '*'){ii = 0; i = slen;}
			if(i >= slen){ii = 0;}
			if(ii) Buf[j++] = Da[i];
			i++;
		}
		if(j>0){
//			len = strlen(Buf);
			switch(k){
				case  0: rGSA.Mode_1 = (char)atoi(Buf); break;
				case  1: rGSA.Mode_2 = (char)atoi(Buf); break;
				case  2: rGSA.Satellite_Used[0]  = atoi(Buf); break;
				case  3: rGSA.Satellite_Used[1]  = atoi(Buf); break;
				case  4: rGSA.Satellite_Used[2]  = atoi(Buf); break;
				case  5: rGSA.Satellite_Used[3]  = atoi(Buf); break;
				case  6: rGSA.Satellite_Used[4]  = atoi(Buf); break;
				case  7: rGSA.Satellite_Used[5]  = atoi(Buf); break;
				case  8: rGSA.Satellite_Used[6]  = atoi(Buf); break;
				case  9: rGSA.Satellite_Used[7]  = atoi(Buf); break;
				case 10: rGSA.Satellite_Used[8]  = atoi(Buf); break;
				case 11: rGSA.Satellite_Used[9]  = atoi(Buf); break;
				case 12: rGSA.Satellite_Used[10] = atoi(Buf); break;
				case 13: rGSA.Satellite_Used[11] = atoi(Buf); break;
				case 14: rGSA.PDOP = atof(Buf); break;
				case 15: rGSA.HDOP = atof(Buf); break;
				case 16: rGSA.VDOP = atof(Buf); break;
				default: break;
			}
		}
//		k++;
	}
}
//--------------------------------------------------------------------------
// $GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D
void CMD_GSV_Conver(char *Da, int slen)
{
	int i = 0, j = 0, k = 0, ii = 0;
	char Buf[Buf_Size] = {0};
	//
	k = 0;
	//
	memset(Buf, 0, Buf_Size);
	for(i=0;i<slen;){
		memset(Buf, 0, Buf_Size);
		ii = 1;
		j = 0;
		while(ii){
			if(Da[i] == ','){ii = 0; k = 0;}
			if(Da[i] == '*'){ii = 0; i = slen; j = 0;}
			if(i >= slen){ii = 0; j = 0;}
			if(ii) Buf[j++] = Da[i];
			i++;
		}
		if(j>0){
//			slen = strlen(Buf);
			switch(k){
				case  1: rGSV.Number_of_Messages = (char)atoi(Buf); break;
				case  2: rGSV.Messages_Number    = (char)atoi(Buf); break;
				case  3: rGSV.Satellites      	 = (char)atoi(Buf); break;
				case  4: rGSV.Satellite_ID[0]    = (char)atoi(Buf); break;
				case  5: rGSV.Elevation[0]       = (char)atoi(Buf); break;
				case  6: rGSV.Azimuth[0]         = atoi(Buf); break;
				case  7: rGSV.SNR[0]             = (char)atoi(Buf); break;
				case  8: rGSV.Satellite_ID[1]    = (char)atoi(Buf); break;
				case  9: rGSV.Elevation[1]       = (char)atoi(Buf); break;
				case 10: rGSV.Azimuth[1]         = atoi(Buf); break;
				case 11: rGSV.SNR[1]             = (char)atoi(Buf); break;
				case 12: rGSV.Satellite_ID[2]    = (char)atoi(Buf); break;
				case 13: rGSV.Elevation[2]       = (char)atoi(Buf); break;
				case 14: rGSV.Azimuth[2]         = atoi(Buf); break;
				case 15: rGSV.SNR[2]             = (char)atoi(Buf); break;
				case 16: rGSV.Satellite_ID[3]    = (char)atoi(Buf); break;
				case 17: rGSV.Elevation[3]       = (char)atoi(Buf); break;
				case 18: rGSV.Azimuth[3]         = atoi(Buf); break;
				case 19: rGSV.SNR[3]             = (char)atoi(Buf); break;
				default: break;
			}
		}
//		k++;
	}
}
//--------------------------------------------------------------------------
// $GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406, 3.05,W,A*55
void CMD_RMC_Conver(char *Da, int slen)
{
	int len = 0;
	int i = 0, j = 0, k = 0, ii = 0;
	char Buf[Buf_Size] = {0};
	//
	memset(Buf, 0, Buf_Size);
	for(i=0;i<slen;){
		memset(Buf, 0, Buf_Size);
		ii = 1;
		j = 0;
		while(ii){
			if(Da[i] == ','){ii = 0; k++;}
			if(Da[i] == '*'){ii = 0; i = slen;}
			if(i >= slen){ii = 0;}
			if(ii) Buf[j++] = Da[i];
			i++;
		}
		//---
		if(j>0){
			len = strlen(Buf);
			switch(k){
				case  1: memset(rRMC.UTC_Time, 0, 10); memcpy(rRMC.UTC_Time, Buf, len); break;
				case  2: rRMC.Status = Buf[0]; break;
				case  3: rRMC.Latitude = atof(Buf); break;
				case  4: rRMC.NS_Indicator = Buf[0]; break;
				case  5: rRMC.Longitude = atof(Buf); break;
				case  6: rRMC.EW_Indicator = Buf[0]; break;
				case  7: rRMC.Speed_over = atof(Buf); break;
				case  8: rRMC.Course_over = atof(Buf); break;
				case  9: memset(rRMC.UTC_Date, 0, 6); memcpy(rRMC.UTC_Date, Buf, len); rRMC_FG = 1; break;
				case 10: rRMC.Magnetic = atof(Buf); break;
				case 11: rRMC.Magnetic_V = Buf[0]; break;
				case 12: rRMC.Mode = Buf[0]; break;
				default: break;
			}
		}
	}
}
//--------------------------------------------------------------------------
// $GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37
void CMD_VTG_Conver(char *Da, int slen)
{
	int i = 0, j = 0, k = 0, ii = 0;
	char Buf[Buf_Size] = {0};
	//
	memset(Buf, 0, Buf_Size);
	for(i=0;i<slen;){
		memset(Buf, 0, Buf_Size);
		ii = 1;
		j = 0;
		while(ii){
			if(Da[i] == ','){ii = 0; k++;}
			if(Da[i] == '*'){ii = 0; i = slen;}
			if(i >= slen){ii = 0;}
			if(ii) Buf[j++] = Da[i];
			i++;
		}
		if(j>0){
//			slen = strlen(Buf);
			switch(k){
				case  1: rVTG.Course1 = atof(Buf); break;
				case  2: rVTG.Reference1 = Buf[0]; break;
				case  3: rVTG.Course2 = atof(Buf); break;
				case  4: rVTG.Reference2 = Buf[0]; break;
				case  5: rVTG.Speed1 = atof(Buf); break;
				case  6: rVTG.Unit1 = Buf[0]; break;
				case  7: rVTG.Speed2 = atof(Buf); break;
				case  8: rVTG.Unit2 = Buf[0]; break;
				case  9: rVTG.Mode = Buf[0]; break;
				default: break;
			}
		}
//		k++;
	}
}
//--------------------------------------------------------------------------
// $GPZDA,060053.00,30,08,2019,00,00*67
void CMD_ZDA_Conver(char *Da, int slen)
{
	int len = 0;
	int i = 0, j = 0, k = 0, ii = 0, kk = 0;
	char Buf[Buf_Size] = {0};
	//
	k = 0; kk = 0;
	//
	memset(Buf, 0, Buf_Size);
	for(i=0;i<slen;){
		memset(Buf, 0, Buf_Size);
		ii = 1;
		j = 0;
		while(ii){
			if(Da[i] == ','){ii = 0; k++;}
			if(Da[i] == '*'){ii = 0; i = slen;}
			if(i >= slen){ii = 0;}
			if(ii) Buf[j++] = Da[i];
			i++;
		}
		if(j>0){
			len = strlen(Buf);
//		sprintf(rRMC.UTC_Date, "121018\0");
			switch(k){
				case  1: memset(rZDA.UTC_Time,    0, 10); memcpy(rZDA.UTC_Time,    Buf, len);
					strcpy(rRMC.UTC_Time, rZDA.UTC_Time); break;
				case  2: 
					memset(rZDA.UTC_D_Day,   0,  3); memcpy(rZDA.UTC_D_Day,   Buf, len); break;
				case  3: 
					memset(rZDA.UTC_D_Month, 0,  3); memcpy(rZDA.UTC_D_Month, Buf, len); break;
				case  4:
					memset(rZDA.UTC_D_Year,  0,  5); memcpy(rZDA.UTC_D_Year,  Buf, len); break;
				default: break;
			};
		}
	}
}
//--------------------------------------------------------------------------
//char COM1_CONVER(unsigned char *Da, int sLen)
int GPS_NMEA_Conver(unsigned char *Da, int sLen)
{
	int j = 0, jj = 0;
	//---
	int i = 0, k = 0;
	unsigned int SUM = 0;
	//---
	SUM = 0;
	for(i=1;i<sLen;i++){
		if(Da[i] == '*'){
			j = i+1;
			i = sLen + 1;
		} else {
			if(SUM == 0) SUM = Da[i]; else SUM ^= Da[i];
		};
	};
	//
	if(Da[j] >= 0x3A) i = Da[j] - 0x37; else i = Da[j] - 0x30; j++;
	if(Da[j] >= 0x3A) k = Da[j] - 0x37; else k = Da[j] - 0x30;
	j = ((i<<4)&0xF0) + (k&0x0F);
	if((SUM&0x00FF) != j) return -1;
	//---
	if(memcmp(&Da[0], "$GP", 3) == 0){
		i = 1;
		j = 0;
		while(i){
			if(memcmp(NMEA_CMD[j], "End\0", 3) == 0) i = 0;
			else if(memcmp(&Da[3], NMEA_CMD[j], 3) == 0){
				switch(j){
					case 0: CMD_GGA_Conver(&Da[7], sLen - 7); jj = 1; break;
					case 1: CMD_GSA_Conver(&Da[7], sLen - 7); jj = 2; break;
					case 2: CMD_GSV_Conver(&Da[7], sLen - 7); jj = 3; break;
					case 3:	CMD_RMC_Conver(&Da[7], sLen - 7); jj = 4; break;
					case 4: CMD_VTG_Conver(&Da[7], sLen - 7); jj = 5; break;
					case 5: CMD_ZDA_Conver(&Da[7], sLen - 7); jj = 6; break;
					default:  jj = 0; break;
				};
//				break;
			}
			j++;
		};
	};
	return jj;
}
//==========================================================================
// End of File
