/*
 * time_lunar_calendar.h
 *
 *  Created on: 2016Äê11ÔÂ6ÈÕ
 *      Author: 
 */

#ifndef TIME_LUNAR_CALENDAR_H_
#define TIME_LUNAR_CALENDAR_H_

//const int SECONDS_OF_DAY = 24 * 60 * 60;

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


/***/
double getELP200082MELongitude(const time_t* timePoint);

#endif /* TIME_LUNAR_CALENDAR_H_ */
