/**
 * time_julian_day.h
 *
 *  Created on: Feb 20, 2017
 *      Author: 
 */
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef TIME_JULIAN_DAY_H_
#define TIME_JULIAN_DAY_H_

typedef struct _SJULIAN_DAY
{
	long long integer;
	double decimal;
} SJULIAN_DAY, *PJULIAN_DAY;

double getJulianDayBySecond(time_t);

time_t getSecondByJulianDay(double jd);

double getJulianCenturyByJulianDay(double jd);

double getJulianCenturyBySecond(time_t timeptr);

double getJulianMillenniumByJulianDay(double jd);

double getJulianMillenniumBySecond(time_t timePoint);

#endif /* TIME_JULIAN_DAY_H_ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
