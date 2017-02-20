/**
 * time_calendar.h
 *
 *  Created on: Feb 20, 2017
 *      Author: 
 *  To resolve multiple definition of constant value, such as 'SECS_OF_DAY'.
 */

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef TIME_CALENDAR_H_
#define TIME_CALENDAR_H_

/***
//There is something wrong when using macro, which seems the address of the macro?
//This part has been removed.
***/

//Unexpectedly, compilation succeeded after adding static.
//the way of definition
/*****
static const int MONTHS_OF_YEAR = 12;

static const int SECS_OF_DAY = 86400;
static const int SECS_OF_HOUR = 3600;
static const int SECS_OF_MINUTE = 60;

static const int DAYS_OF_LEAP_YEAR = 366ll;
static const int DAYS_OF_NONLEAP_YEAR = 365ll;

static const int DAYS_OF_LEAP_LOOP = (365ll * 4ll + 1ll);
static const int DAYS_OF_100_YEAR_LOOP = (24ll * 366ll + 76ll * 365ll);//365*100 + 100/4 - 100/100
static const int DAYS_OF_400_YEAR_LOOP = (24ll * 366ll + 76ll * 365ll) * 4ll + 1ll;//365*400 + 400/4 - 400/100 + 400/400
//const int DAYS_BEFORE_1970 = (((24ll * 366ll + 76ll * 365ll) * 4ll + 1ll) * 4ll + (24ll * 366ll + 76ll * 365ll) * 3ll + 366ll * 17ll + 365ll * (53ll-1ll));
static const int DAYS_BEFORE_1970 = 1969 * 365 + 1969 / 4 - 1969 / 100 + 1969 / 400 + 1;//because AD 0004-02-28

static const int DAYS_CUTOVER_FOR_GROGORIAN = 577736;
static const int DAYS_CUTOVER_FOR_JULIAN = 1154;//3*365+31+28 <==> 0004-02-28
static const int DAYS_CUTOVER_FOR_JULIAN_FIXED = 0;
static const int DAYS_CUTOVER_FOR_JULIAN_TYPO = 0;

static const int DAYS_OF_JANUARY = 31;
static const int DAYS_OF_FEBRUARY_LEAP = 29;
static const int DAYS_OF_FEBRUARY_NONLEAP = 28;
static const int DAYS_OF_MARCH = 31;
static const int DAYS_OF_APRIL = 30;
static const int DAYS_OF_MAY = 31;
static const int DAYS_OF_JUNE = 30;
static const int DAYS_OF_JULY = 31;
static const int DAYS_OF_AUGUST = 31;
static const int DAYS_OF_SEPTEMBER = 30;
static const int DAYS_OF_OCTOBER = 31;
static const int DAYS_OF_NOVEMBER = 30;
static const int DAYS_OF_DECEMBER = 31;

static const time_t SECS_OF_LEAP_YEAR = (366ll * 86400ll);
static const time_t SECS_OF_NONLEAP_YEAR = (365ll * 86400ll);

static const time_t SECS_OF_LEAP_TYPO = ((365ll * 3ll + 1ll) * 86400ll);
static const time_t SECS_OF_LEAP_LOOP = ((365ll * 4ll + 1ll) * 86400ll);
static const time_t SECS_OF_100_YEAR_LOOP = ((24ll * 366ll + 76ll * 365ll) * 86400ll);
static const time_t SECS_OF_400_YEAR_LOOP = (((24ll * 366ll + 76ll * 365ll) * 4ll + 1ll) * 86400ll);
static const time_t SECS_OF_AD_BEFORE_1970 = ((1969 * 365 + 1969 / 4 - 1969 / 100 + 1969 / 400 + 1) * 86400ll);//because AD 0004-02-28

static const time_t SECS_CUTOVER_FOR_GROGORIAN = 577736ll * 86400;// AD 1582-10-15
static const time_t SECS_CUTOVER_FOR_JULIAN = 1154ll * 86400;//365 * 3 + 59 AD 0004-03-01
static const time_t SECS_CUTOVER_FOR_JULIAN_FIXED = -3226ll * 86400;//365*9 - 59 BC 0009-03-01
static const time_t SECS_CUTOVER_FOR_JULIAN_TYPO = -16438ll * 86400;//365 * 45 + 13 BC 0045-01-01

//static const time_t SECS_OF_JD_BEFORE_1970 = (4713 * 365 + 4713 / 4 + 1 + 719163) * 86400ll - 43200;

//const int SECS_OF_JANUARY = 31 * 86400;
//const int SECS_OF_FEBRUARY_LEAP = 29 * 86400;
//const int SECS_OF_FEBRUARY_NONLEAP = 28 * 86400;
//const int SECS_OF_MARCH = 31 * 86400;
//const int SECS_OF_APRIL = 30 * 86400;
//const int SECS_OF_MAY = 31 * 86400;
//const int SECS_OF_JUNE = 30 * 86400;
//const int SECS_OF_JULY = 31 * 86400;
//const int SECS_OF_AUGUST = 31 * 86400;
//const int SECS_OF_SEPTEMBER = 30 * 86400;
//const int SECS_OF_OCTOBER = 31 * 86400;
//const int SECS_OF_NOVEMBER = 30 * 86400;
//const int SECS_OF_DECEMBER = 31 * 86400;
*****/
static const int SECS_OF_MONTHS_COMMON[12] = {
		31 * 86400, 28 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400
};

static const int SECS_OF_MONTHS_LEAP[12] = {
		31 * 86400, 29 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400
};


//the way of macro
#define MONTHS_OF_YEAR (int)12

#define SECS_OF_DAY (int)86400
#define SECS_OF_HOUR (int)3600
#define SECS_OF_MINUTE (int)60

#define DAYS_OF_LEAP_YEAR (int)366
#define DAYS_OF_NONLEAP_YEAR (int)365

#define DAYS_OF_LEAP_LOOP (int)(365ll * 4ll + 1ll)
#define DAYS_OF_100_YEAR_LOOP (int)(24ll * 366ll + 76ll * 365ll)//365*100 + 100/4 - 100/100
#define DAYS_OF_400_YEAR_LOOP (int)((24ll * 366ll + 76ll * 365ll) * 4ll + 1ll)//365*400 + 400/4 - 400/100 + 400/400
//#define DAYS_BEFORE_1970 (((24ll * 366ll + 76ll * 365ll) * 4ll + 1ll) * 4ll + (24ll * 366ll + 76ll * 365ll) * 3ll + 366ll * 17ll + 365ll * (53ll-1ll));
#define DAYS_BEFORE_1970 (int)(1969 * 365 + 1969 / 4 - 1969 / 100 + 1969 / 400 + 1)//because AD 0004-02-28

#define DAYS_CUTOVER_FOR_GROGORIAN (int)577736
#define DAYS_CUTOVER_FOR_JULIAN (int)1154//3*365+31+28 <==> 0004-02-28
#define DAYS_CUTOVER_FOR_JULIAN_FIXED (int)0
#define DAYS_CUTOVER_FOR_JULIAN_TYPO (int)0

#define DAYS_OF_JANUARY (int)31
#define DAYS_OF_FEBRUARY_LEAP (int)29
#define DAYS_OF_FEBRUARY_NONLEAP (int)28
#define DAYS_OF_MARCH (int)31
#define DAYS_OF_APRIL (int)30
#define DAYS_OF_MAY (int)31
#define DAYS_OF_JUNE (int)30
#define DAYS_OF_JULY (int)31
#define DAYS_OF_AUGUST (int)31
#define DAYS_OF_SEPTEMBER (int)30
#define DAYS_OF_OCTOBER (int)31
#define DAYS_OF_NOVEMBER (int)30
#define DAYS_OF_DECEMBER (int)31

#define SECS_OF_LEAP_YEAR (time_t)(366ll * 86400ll)
#define SECS_OF_NONLEAP_YEAR (time_t)(365ll * 86400ll)

#define SECS_OF_LEAP_TYPO (time_t)((365ll * 3ll + 1ll) * 86400ll)
#define SECS_OF_LEAP_LOOP (time_t)((365ll * 4ll + 1ll) * 86400ll)
#define SECS_OF_100_YEAR_LOOP (time_t)((24ll * 366ll + 76ll * 365ll) * 86400ll)
#define SECS_OF_400_YEAR_LOOP (time_t)(((24ll * 366ll + 76ll * 365ll) * 4ll + 1ll) * 86400ll)
#define SECS_OF_AD_BEFORE_1970 (time_t)((1969 * 365 + 1969 / 4 - 1969 / 100 + 1969 / 400 + 1) * 86400ll) //because AD 0004-02-28

#define SECS_CUTOVER_FOR_GROGORIAN (time_t)(577736ll * 86400)// AD 1582-10-15
#define SECS_CUTOVER_FOR_JULIAN (time_t)(1154ll * 86400)//365 * 3 + 59 AD 0004-03-01
#define SECS_CUTOVER_FOR_JULIAN_FIXED (time_t)(-3226ll * 86400)//365*9 - 59 BC 0009-03-01
#define SECS_CUTOVER_FOR_JULIAN_TYPO (time_t)(-16438ll * 86400)//365 * 45 + 13 BC 0045-01-01


#define SECS_OF_JD_BEFORE_1970 (time_t)((4713 * 365 + 4713 / 4 + 1 + 719163) * 86400ll - 43200)

#endif /* TIME_CALENDAR_H_ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
