/**
 * time_gregorian_calendar.h
 *
 *  Created on: Nov 7, 2016
 *      Author: 
 */

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef TIME_GREGORIAN_CALENDAR_H_
#define TIME_GREGORIAN_CALENDAR_H_
/***
const int SECS_OF_DAY = 24 * 60 * 60;

const int DAYS_OF_LEAP_YEAR = 366;
const int DAYS_OF_NONLEAP_YEAR = 365;

const int DAYS_OF_LEAP_LOOP = DAYS_OF_LEAP_YEAR * 4 + 1;
const int DAYS_OF_100_YEAR_LOOP = 24 * 366 + 76 * 365;
const int DAYS_OF_400_YEAR_LOOP = DAYS_OF_100_YEAR_LOOP * 4 + 1;
const int DAYS_BEFORE_1970 = DAYS_OF_400_YEAR_LOOP * 4 + DAYS_OF_100_YEAR_LOOP * 3 + DAYS_OF_LEAP_YEAR * 17 + DAYS_OF_NONLEAP_YEAR * (53-1);

const time_t SECS_OF_LEAP_YEAR = DAYS_OF_LEAP_YEAR * SECS_OF_DAY;
const time_t SECS_OF_NONLEAP_YEAR = DAYS_OF_NONLEAP_YEAR * SECS_OF_DAY;

const time_t SECS_OF_LEAP_LOOP = DAYS_OF_LEAP_LOOP * SECS_OF_DAY;
const time_t SECS_OF_100_YEAR_LOOP = DAYS_OF_100_YEAR_LOOP * SECS_OF_DAY;
const time_t SECS_OF_400_YEAR_LOOP = DAYS_OF_400_YEAR_LOOP * SECS_OF_DAY;
const time_t SECS_BEFORE_1970 = DAYS_BEFORE_1970 * SECS_OF_DAY;
***/

int is_leap_year(int year);

/**
 * in seconds
 * */
struct tm *gmtime_by_gre(const time_t *timeptr);

void test_all_gre_constant(void);

#endif /* TIME_GREGORIAN_CALENDAR_H_ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
