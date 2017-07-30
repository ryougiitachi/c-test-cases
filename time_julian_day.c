/**
 * time_julian_day.c
 *
 *  Created on: Feb 20, 2017
 *      Author: 
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "time_julian_day.h"
#include "time_calendar.h"

/**
 * error occurs here.
 * time_julian_day.o:time_julian_day.c:(.rdata+0x0): multiple definition of `SECS_OF_DAY'
 * time_gregorian_calendar.o:time_gregorian_calendar.c:(.rdata+0x4): first defined here
 * */
//const int SECS_OF_DAY = 86400;
//const time_t SECS_OF_JD_BEFORE_1970 = (4713 * 365 + 4713 / 4 + 1 + 719163) * 86400ll - 43200;


//static SJULIAN_DAY RESULT_JULIAN_DAY;

/**
 * timeptr used to be declared as a time_t* point. 
 * */
double getJulianDayBySecond(time_t timePoint)
{
	time_t lltime = timePoint;
	time_t llinteger;
	time_t lldecimal = 0.0;
	time_t llJDsecs = lltime + SECS_OF_JD_BEFORE_1970;
	double ddecimal;

	llinteger = llJDsecs / SECS_OF_DAY;
	lldecimal = llJDsecs - llinteger * SECS_OF_DAY;
	if(lldecimal > 0)
	{
		ddecimal = lldecimal / (double)SECS_OF_DAY;
	}
	double dJulianDay = llinteger + ddecimal;
	return dJulianDay;
}

/**
 * @param jd	Julian day.
 * */
time_t getSecondByJulianDay(double jd)
{
	time_t llJDsecs = 0;
	time_t integer;
	double decimal;
	integer = (time_t)ceil(jd);
	decimal = jd - ceil(jd);
	llJDsecs += integer * SECS_OF_DAY;
	llJDsecs += decimal * SECS_OF_DAY;
	llJDsecs -= SECS_OF_JD_BEFORE_1970;
	return llJDsecs;
}

double getJulianCenturyByJulianDay(double jd)
{
	double dJulianDaySince2000 = jd - 2451545.0;
	return dJulianDaySince2000 / 36525.0;
}

double getJulianCenturyBySecond(time_t timePoint)
{
	double jd = getJulianDayBySecond(timePoint);
	return getJulianCenturyByJulianDay(jd);
}

double getJulianMillenniumByJulianDay(double jd)
{
	double dJulianDaySince2000 = jd - 2451545.0;
	return dJulianDaySince2000 / 365250.0;
}

double getJulianMillenniumBySecond(time_t timePoint)
{
	double jd = getJulianDayBySecond(timePoint);
	return getJulianMillenniumByJulianDay(jd);
}
