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

PJULIAN_DAY getJulianDayBySecond(const time_t *);

#endif /* TIME_JULIAN_DAY_H_ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
