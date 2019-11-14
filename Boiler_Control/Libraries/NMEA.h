//============================================================================
// File Name          : IAP.c
// Author             : SunKyung
// Version            : V1.0
// HomePage           : http://sunkyung.iptime.org
// Date               : 11/02/2017
// Description        : Sikhoon J.
//============================================================================
#ifndef _GPS_NMEA_H
#define _GPS_NMEA_H
//--------------------------------------------------------------------------
// NMEA Output Sentence ($GP)
//--------------------------------------------------------------------------
// GGA-Global Positioning System Fixed Data. Time, Position and fix related data
typedef struct {
	char    UTC_Time[10];		// hhmmss.sss
	double  Latitude;			// ddmm.mmmm
	char    NS_Indicator;		// N=north or S=south
	double  Longitude;			// dddmm.mmmm
	char    EW_Indicator;		// E=east or W=west
	char    Position_Fix;
	char    Satellites_Used;
	double  HDOP;
	double  MSL_Altitude;
	char    Unit1;
	double  Geoidal_Separation;
	char    Unit2;
	char    Age_of_Diff_Corr;
} TypeGGA;
//
// GSA-GNSS DOP and Active Satellites
typedef struct {
	char    Mode_1;
	char    Mode_2;
	int		Satellite_Used[12];
	double	PDOP;
	double	HDOP;
	double	VDOP;
} TypeGSA;
//
// GSV-GNSS Satellites in View
typedef struct {
	char    Number_of_Messages;	// Range 1 to 3  (Depending on the number of satellites tracked, multiple messages of GSV data may be required.)
	char    Messages_Number;	// Range 1 to 3
	char    Satellites;			// Satellites in View
	char    Satellite_ID[4];	// Channel 1 (Range 1 to 32)
	char    Elevation[4];		// Channel 1 (Maximum 90)					Units : degrees
	int     Azimuth[4];			// Channel 1 (True, Range 0 to 359)			Units : degrees
	char    SNR[4];				// Range 0 to 99 (null when not tracking)	Units : dBHz
} TypeGSV;
//
// RMC-Recommended Minimum Navigation Information
typedef struct {
	char    UTC_Time[10];		// hhmmss.sss
	char    Status;				// A=data valid or V=data not valid
	double	Latitude;			// ddmm.mmmm
	char    NS_Indicator;		// N=north or S=south
	double  Longitude;			// dddmm.mmmm
	char    EW_Indicator;		// E=east or W=west
	double  Speed_over;			// Speed_over_Ground   Units : knots
	double  Course_over;		// Course_over_Ground  Units : degrees
	char    UTC_Date[6];		// ddmmyy
	double  Magnetic;			// Magnetic_Variation  Units : degrees
	char    Magnetic_V;			// E=east or W=west
	char    Mode;				// A= Autonomous mode  D= Differential mode  E= Estimated mode
} TypeRMC;
//
// ZDA Time & Date Information
// ZDA Time & Date – UTC, Day, Month, Year and Local Time Zone
//        1         2  3  4    5  6 7
//        |         |  |  |    |  | |
// $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh
// 1) Local zone minutes description, same sign as local hours
// 2) Local zone description, 00 to +/- 13 hours
// 3) Year
// 4) Month, 01 to 12
// 5) Day, 01 to 31
// 6) Time (UTC)
// 7) Checksum
typedef struct {
	char    UTC_Time[10];		// hhmmss.ss
	char    UTC_D_Day[3];		// dd
	char    UTC_D_Month[3];		// mm
	char    UTC_D_Year[5];		// yyyy
} TypeZDA;
//
// VTG-Course and speed information relative to the ground
typedef struct {
	double  Course1;			// Measured heading  Units : degrees
	char    Reference1;			// True
	double  Course2;			// Measured heading  Units : degrees
	char    Reference2;			// Magnetic (Need AscenKorea Customization Service)
	double  Speed1;				// Measured horizontal speed  Units : knots
	char    Unit1;				// Knots
	double  Speed2;				// Measured horizontal speed  Units : km/hr
	char    Unit2;				// Measured horizontal speed
	char    Mode;				// A= Autonomous mode  D= Differential mode  E= Estimated mode
} TypeVTG;
//--------------------------------------------------------------------------
#endif
//============================================================================
// End of File

