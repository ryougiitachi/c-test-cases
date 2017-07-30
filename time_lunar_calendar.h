/*
 * time_lunar_calendar.h
 *
 *  Created on: 2016Äê11ÔÂ6ÈÕ
 *      Author: 
 */

#ifndef TIME_LUNAR_CALENDAR_H_
#define TIME_LUNAR_CALENDAR_H_

//const int SECONDS_OF_DAY = 24 * 60 * 60;



/*************************IAU 1980*************************/
#define COUNT_TERM_IAU1980_NUTATION 63

#define COUNT_IAU1980_ARGUMENT_PARAMS 4

typedef struct _TERM_IAU1980_NUTATION {
	int D;//a
	int M;//b
	int Mp;//c
	int F;//d
	int Omega;//e
	double sine1;//¦¤¦×
	double sine2;//¦¤¦×
	double cose1;//¦¤¦Å
	double cose2;//¦¤¦Å
} STERM_IAU1980_NUTATION, *PTERM_IAU1980_NUTATION;

typedef struct _PARAM_TERM_IAU1980_NUTATION {
	double D;
	double M;
	double Mp;
	double F;
	double Omega;
}SPARAM_TERM_IAU1980_NUTATION, *PPARAM_TERM_IAU1980_NUTATION;

double getIAU1980EarthLongitudeNutation(double dt);



/*************************VSOP 82/87*************************/
#define COUNT_TERM_VSOP8287_EARTH_L 6
#define COUNT_TERM_VSOP8287_EARTH_B 2
#define COUNT_TERM_VSOP8287_EARTH_R 5

#define COUNT_TERM_VSOP8287_EARTH_L0 64
#define COUNT_TERM_VSOP8287_EARTH_L1 34
#define COUNT_TERM_VSOP8287_EARTH_L2 20
#define COUNT_TERM_VSOP8287_EARTH_L3 7
#define COUNT_TERM_VSOP8287_EARTH_L4 3
#define COUNT_TERM_VSOP8287_EARTH_L5 1
#define COUNT_TERM_VSOP8287_EARTH_B0 5
#define COUNT_TERM_VSOP8287_EARTH_B1 2
#define COUNT_TERM_VSOP8287_EARTH_R0 40
#define COUNT_TERM_VSOP8287_EARTH_R1 10
#define COUNT_TERM_VSOP8287_EARTH_R2 6
#define COUNT_TERM_VSOP8287_EARTH_R3 2
#define COUNT_TERM_VSOP8287_EARTH_R4 1

typedef struct _TERM_VSOP8287_PLANETS {
	double A;
	double B;
	double C;
} STERM_VSOP8287_PLANETS, *PTERM_VSOP8287_PLANETS;

/**
 * 
 * @param jd	Julian day. 
 * @return		The unit of result is degree. 
 * */
double getSunEclipticLongitudeECByJulianDay(double jd);

double getSunEclipticLongitudeECBySecond(time_t timePoint);

/**
 * 
 * @param jd	Julian day. 
 * @return		The unit of result is Julian day. 
 * */
double getSolarTermJulianDayNewtonByJulianDay(double jd);

double getSolarTermJulianDayNewtonBySecond(time_t timePoint);



/*************************ELP 2000/82*************************/
#define COUNT_TERM_ELP200082_LONGITUDE 60
#define COUNT_TERM_ELP200082_LATITUDE 60
#define COUNT_ELP200082_ARGUMENT_PARAMS 5

typedef struct _TERM_ELP200082_MOON {
	int D;//a
	int M;//b
	int Mp;//c
	int F;//d
	int amplitudeAsin;
	int amplitudeAcos;
} STERM_ELP200082_MOON, *PTERM_ELP200082_MOON;

typedef struct _PARAM_TERM_ELP200082_MOON_ECLIPTIC {
	double D;
	double M;
	double Mp;
	double F;
	double E;
	double Lp;
} SPARAM_TERM_ELP200082_MOON_ECLIPTIC, *PPARAM_TERM_ELP200082_MOON_ECLIPTIC;

/**
 * Calculate ELP2000/82 longitude using Julian day. 
 * @param jd	It is Julian day, instead of Julian century.
 * @return 		The unit of result is degree. 
 * */
double getMoonEclipticLongitudeECByJulianDay(double jd);

/**
 * Calculate ELP2000/82 longitude using Unix second. 
 * */
double getMoonEclipticLongitudeECBySecond(time_t timePoint);

/**
 * the same usage as that of getELP200082MELongitudeBySecond(time_t)
 * */
double getELP200082MELongitude(time_t timePoint);

double getJulianDayForNewMoonByJulianDay(double jd);

double getJulianDayForNewMoonBySecond(time_t timePoint);


#endif /* TIME_LUNAR_CALENDAR_H_ */
