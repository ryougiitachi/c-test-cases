/**
 * time_julian_day.c
 *
 *  Created on: Feb 20, 2017
 *      Author: 
 */

#include <time.h>
#include <string.h>
#include "time_julian_day.h"
#include "time_calendar.h"

/**
 * error occurs here.
 * time_julian_day.o:time_julian_day.c:(.rdata+0x0): multiple definition of `SECS_OF_DAY'
 * time_gregorian_calendar.o:time_gregorian_calendar.c:(.rdata+0x4): first defined here
 * */
//const int SECS_OF_DAY = 86400;
//const time_t SECS_OF_JD_BEFORE_1970 = (4713 * 365 + 4713 / 4 + 1 + 719163) * 86400ll - 43200;


static SJULIAN_DAY RESULT_JULIAN_DAY;

PJULIAN_DAY getJulianDayBySecond(const time_t *timeptr)
{
	if(!timeptr)
	{
		return &RESULT_JULIAN_DAY;
	}
	time_t lltime = timeptr[0];
	time_t llinteger;
	time_t lldecimal = 0.0;
	time_t llJDsecs = lltime + SECS_OF_JD_BEFORE_1970;
	double ddecimal;

	memset(&RESULT_JULIAN_DAY, 0, sizeof(SJULIAN_DAY));
	llinteger = llJDsecs / SECS_OF_DAY;
	lldecimal = llJDsecs - llinteger * SECS_OF_DAY;
	if(lldecimal > 0)
	{
		ddecimal = lldecimal / (double)SECS_OF_DAY;
	}

	RESULT_JULIAN_DAY.integer = llinteger;
	RESULT_JULIAN_DAY.decimal = ddecimal;

	return &RESULT_JULIAN_DAY;
}
