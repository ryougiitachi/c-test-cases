/**
 * time_gregorian.calendar.c
 *
 *  Created on: Nov 7, 2016
 *      Author: 
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include "time_gregorian_calendar.h"
#include "time_calendar.h"


/***** Declaration in C source file starts *****/
struct tm *calcal_by_gregorian_sec(time_t fixedDateSecs);
struct tm *calcal_by_julian_sec(time_t fixedDateSecs);
struct tm *calcal_by_julian_noleap_sec(time_t fixedDateSecs);
struct tm *calcal_by_julian_typo_sec(time_t fixedDateSecs);
/***** Declaration in C source file ends *****/

static struct tm RESULT_GMTIME_GRE;

struct tm *gmtime_by_gre_day(const time_t *timeptr)
{
	return &RESULT_GMTIME_GRE;
}

/**
 * basic parsing steps: year -> month / day -> hour / minute / second
 * */
struct tm *gmtime_by_gre_sec(const time_t *timeptr)
{
	time_t lltime = 0;

	int isADFlag = 0;
	int isLeapFlag = 0;
	int iNum400Years = 0;
	int iNum100Years = 0;
	int iLeapYears = 0;
	int iLeftYears = 0;
	int iHMS = 0;
	//Temporary variables of result.
	int itmyear = 0;
	int itmmon = 0;//January = 1
	int itmmday = 0;
	int itmhour = 0;
	int itmmin = 0;
	int itmsec = 0;

	memset(&RESULT_GMTIME_GRE, 0, sizeof(struct tm));
	if(!timeptr)
	{
		time(&lltime);
	}
	else
	{
		lltime = timeptr[0];
	}
	if(lltime >= SECS_CUTOVER_FOR_GROGORIAN)
	{//since Gregorian Calendar AD 1582-10-15
		return calcal_by_gregorian_sec(lltime);
	}
	else if(lltime >= SECS_CUTOVER_FOR_JULIAN)
	{//since Julian Calendar with correct leap year AD 0005-01-01
		return calcal_by_julian_sec(lltime);
	}
	else if(lltime >= SECS_CUTOVER_FOR_JULIAN_FIXING)
	{//since Julian Calendar without leap year BC 0008-01-01
		return calcal_by_julian_noleap_sec(lltime);
	}
	else if(lltime >= SECS_CUTOVER_FOR_JULIAN_TYPO)
	{//since Julian Calendar with incorrect leap year BC 0045-01-01
		return calcal_by_julian_typo_sec(lltime);
	}
	else
	{//before BC 0045-01-01
		return calcal_by_julian_sec(lltime);
	}

	return &RESULT_GMTIME_GRE;
}

int is_leap_year(int year)
{
	return ((year&3)==0 && (year%100)!=0) || (year%400)==0 ? 1 : 0;
}

int is_leap_year_julian(int year)
{
	return (year&3)==0 ? 1 : 0;
}

int is_leap_year_incorrect(int year)
{
	return (year%3)==0 ? 1 : 0;
}

struct tm *calcal_by_gregorian_sec(time_t fixedDateSecs)
{
	time_t llADSec;
	int isADFlag = 0;
	int isLeapFlag = 0;
	int iNum400Years = 0;
	int iNum100Years = 0;
	int iLeapYears = 0;
	int iLeftYears = 0;
	int iHMS = 0;
	//Temporary variables of result.
	int itmyear = 0;
	int itmmon = 0;//January = 1
	int itmmday = 0;
	int itmhour = 0;
	int itmmin = 0;
	int itmsec = 0;

//	llADSec = fixedDateSecs - SECS_OF_DAY;//0004-02-28
	//set BC AND AD flag
/***	if(llADSec >= 0)
	{
		isADFlag = 1;
	}
	else
	{//not very possible for gregorian calendar
		isADFlag = -1;
		llADSec =-llADSec;
	}***/
	llADSec = fixedDateSecs - SECS_CUTOVER_FOR_GROGORIAN;
	llADSec += SECS_OFFSET_FOR_GROGORIAN;
	llADSec -= SECS_OF_DAY;
	/***YEAR MONTH DAY***/
	//check 400-year loop
	if(llADSec >= SECS_OF_400_YEAR_LOOP)
	{
		iNum400Years = llADSec / SECS_OF_400_YEAR_LOOP;
		itmyear += iNum400Years * 400;
		llADSec -= SECS_OF_400_YEAR_LOOP * iNum400Years;
	}
	//check nonleap 100-year loop
	if(llADSec >= SECS_OF_100_YEAR_LOOP)
	{
		iNum100Years = llADSec / SECS_OF_100_YEAR_LOOP;
		itmyear += iNum100Years * 100;
		llADSec -= SECS_OF_100_YEAR_LOOP * iNum100Years;
	}
	//check leap year in nonleap 100-year loop
	if(llADSec >= SECS_OF_LEAP_LOOP)
	{
		iLeapYears = llADSec / SECS_OF_LEAP_LOOP;
		itmyear += iLeapYears * 4;
		llADSec -= SECS_OF_LEAP_LOOP * iLeapYears;
	}
	//check nonleap year
	if(llADSec >= SECS_OF_NONLEAP_YEAR)
	{
		iLeftYears = llADSec / SECS_OF_NONLEAP_YEAR;
		itmyear += iLeftYears;
		llADSec -= SECS_OF_NONLEAP_YEAR * iLeftYears;
	}
	//there is neither BC 0 nor AD 0. Maybe no need to add one year. 
//	if(llADSec >= 0)//back in time
//	{
//		++itmyear;
//	}
	itmyear += YEAR_OFFSET_FOR_GROGORIAN;
	//check leap or nonleap year
	if(isADFlag == 1)
	{// AD
		isLeapFlag = is_leap_year(itmyear);
	}
	if(isADFlag == -1)
	{// BC
		isLeapFlag = is_leap_year(itmyear - 1);
	}
	//handle BC
	if(isADFlag == -1)
	{
		itmyear = -itmyear;//set year
		llADSec = (isLeapFlag==0 ? SECS_OF_NONLEAP_YEAR : SECS_OF_LEAP_YEAR) - llADSec;
	}
	//check month and day
	//WAHT IF llADSec < 0? both month and day are 0?
	if(llADSec >= 0)
	{
		for(int i=0; i < MONTHS_OF_YEAR; ++i)
		{
			if((llADSec -= SECS_OF_MONTHS_COMMON[i]) < 0)
			{
				itmmon = i + 1;
				itmmday = (llADSec += SECS_OF_MONTHS_COMMON[i]) / SECS_OF_DAY + 1;
				break;
			}
		}
		if(isLeapFlag && itmmon > 2)
		{
			--itmmday;
			if(itmmday <= 0)
			{
				--itmmon;
				itmmday = SECS_OF_MONTHS_COMMON[itmmon];//SECS_OF_MONTHS_LEAP[itmmon]
				if(itmmon == 2)
				{
					++itmmday;
				}
			}
		}
	}
	/***HOUR MINUTE SECOND***/
	if(llADSec == 0)
	{
		itmhour = 0;
		itmmin = 0;
		itmsec = 0;
	}
	else
	{
		iHMS = llADSec % SECS_OF_DAY;
		itmhour = iHMS / SECS_OF_HOUR;
		itmmin = (iHMS / SECS_OF_MINUTE) % SECS_OF_MINUTE;
		itmsec = iHMS % SECS_OF_MINUTE;
	}

	RESULT_GMTIME_GRE.tm_year = itmyear;
	RESULT_GMTIME_GRE.tm_mon = itmmon;
	RESULT_GMTIME_GRE.tm_mday = itmmday;
	RESULT_GMTIME_GRE.tm_hour = itmhour;
	RESULT_GMTIME_GRE.tm_min = itmmin;
	RESULT_GMTIME_GRE.tm_sec = itmsec;

	return &RESULT_GMTIME_GRE;
}

struct tm *calcal_by_julian_sec(time_t fixedDateSecs)
{
	time_t llADSec;
	int isADFlag = 0;
	int isLeapFlag = 0;
	int iLeapYears = 0;
	int iLeftYears = 0;
	int iHMS = 0;
	//Temporary variables of result.
	int itmyear = 0;
	int itmmon = 0;//January = 1
	int itmmday = 0;
	int itmhour = 0;
	int itmmin = 0;
	int itmsec = 0;

	llADSec = fixedDateSecs;
	//In real history, there is no ad 0004-02-29, but there is 0004-02-29 for julian rule.
	llADSec += SECS_OF_DAY;
	llADSec += SECS_OF_AD_BEFORE_1970;
	//set BC AND AD flag
/******/	if(llADSec >= 0)
	{
		isADFlag = 1;
	}
	else
	{//not very possible for gregorian calendar
		isADFlag = -1;
		llADSec += SECS_OF_DAY;//need to adjust a day for BC, unknown reason.
		llADSec =-llADSec;
	}
//	llADSec = fixedDateSecs - SECS_CUTOVER_FOR_JULIAN;
//	llADSec += SECS_OFFSET_FOR_JULIAN;
	/***YEAR MONTH DAY***/
	//check leap year in 4-year loop
	if(llADSec >= SECS_OF_LEAP_LOOP)
	{
		iLeapYears = llADSec / SECS_OF_LEAP_LOOP;
		itmyear += iLeapYears * 4;
		llADSec -= SECS_OF_LEAP_LOOP * iLeapYears;
	}
	//check nonleap year
	if(llADSec >= SECS_OF_NONLEAP_YEAR)
	{
		iLeftYears = llADSec / SECS_OF_NONLEAP_YEAR;
		itmyear += iLeftYears;
		llADSec -= SECS_OF_NONLEAP_YEAR * iLeftYears;
	}
	//there is neither BC 0 nor AD 0.
	if(llADSec >= 0 && isADFlag == 1)//back in time
	{
		++itmyear;
	}
	//check leap year for julian calendar
	isLeapFlag = is_leap_year_julian(itmyear);
	//handle BC
	if(isADFlag == -1)
	{//Maybe, there is still something wrong in B.C. ...
		itmyear = -itmyear;//set year
		--itmyear;//maybe not necessary
		llADSec = (isLeapFlag==0 ? SECS_OF_NONLEAP_YEAR : SECS_OF_LEAP_YEAR) - llADSec;
	}
	//check month and day
	if(llADSec >= 0)
	{
		for(int i=0; i < MONTHS_OF_YEAR; ++i)
		{
			if((llADSec -= SECS_OF_MONTHS_COMMON[i]) < 0)// <= is incorrect. it will enter next loop when 0
			{
				itmmon = i + 1;
				itmmday = (llADSec += SECS_OF_MONTHS_COMMON[i]) / SECS_OF_DAY + 1;
				break;
			}
		}
		if(isLeapFlag && itmmon > 2)
		{
			--itmmday;
			if(itmmday <= 0)
			{
				--itmmon;
				itmmday = SECS_OF_MONTHS_COMMON[itmmon];//SECS_OF_MONTHS_LEAP[itmmon]
				if(itmmon == 2)
				{
					++itmmday;
				}
			}
		}
	}
	/***HOUR MINUTE SECOND***/
	if(llADSec == 0)
	{
		itmhour = 0;
		itmmin = 0;
		itmsec = 0;
	}
	else
	{
		iHMS = llADSec % SECS_OF_DAY;
		itmhour = iHMS / SECS_OF_HOUR;
		itmmin = (iHMS / SECS_OF_MINUTE) % SECS_OF_MINUTE;
		itmsec = iHMS % SECS_OF_MINUTE;
	}

	RESULT_GMTIME_GRE.tm_year = itmyear;
	RESULT_GMTIME_GRE.tm_mon = itmmon;
	RESULT_GMTIME_GRE.tm_mday = itmmday;
	RESULT_GMTIME_GRE.tm_hour = itmhour;
	RESULT_GMTIME_GRE.tm_min = itmmin;
	RESULT_GMTIME_GRE.tm_sec = itmsec;

	return &RESULT_GMTIME_GRE;
}

/**
 * There is no AD 0004-02-29
 * */
struct tm *calcal_by_julian_noleap_sec(time_t fixedDateSecs)
{
	time_t llADSec;
	int isADFlag = 0;
	int iLeftYears = 0;
	int iHMS = 0;
	//Temporary variables of result.
	int itmyear = 0;
	int itmmon = 0;//January = 1
	int itmmday = 0;
	int itmhour = 0;
	int itmmin = 0;
	int itmsec = 0;

//	llADSec = fixedDateSecs;//not necessary to adjust fixed date?
	//set BC AND AD flag
/***	if(llADSec >= 0)
	{
		isADFlag = 1;
	}
	else
	{//not very possible for gregorian calendar
		isADFlag = -1;
		llADSec =-llADSec;
	}***/
	llADSec = fixedDateSecs - SECS_CUTOVER_FOR_JULIAN_FIXING;
	llADSec += SECS_OFFSET_FOR_JULIAN_FIXING;
	/***YEAR MONTH DAY***/
	//check nonleap year
	if(llADSec >= SECS_OF_NONLEAP_YEAR)
	{
		iLeftYears = llADSec / SECS_OF_NONLEAP_YEAR;
		itmyear += iLeftYears;
		llADSec -= SECS_OF_NONLEAP_YEAR * iLeftYears;
	}
	//there is neither BC 0 nor AD 0.
	if(llADSec >= 0)//back in time
	{//It should be Astronomical year numbering in this way.
		++itmyear;
	}
	itmyear += YEAR_OFFSET_FOR_JULIAN_FIXING;
	//no need to check leap year for this calendar
	//It is not necessary if using Astronomical year numbering.
	if(itmyear <= 0)
	{
		--itmyear;
	}
	//check month and day
	if(llADSec >= 0)
	{
		for(int i=0; i < MONTHS_OF_YEAR; ++i)
		{
			if((llADSec -= SECS_OF_MONTHS_COMMON[i]) < 0)// <= is incorrect. it will enter next loop when 0
			{
				itmmon = i + 1;
				itmmday = (llADSec += SECS_OF_MONTHS_COMMON[i]) / SECS_OF_DAY + 1;
				break;
			}
		}
	}
	/***HOUR MINUTE SECOND***/
	if(llADSec == 0)
	{
		itmhour = 0;
		itmmin = 0;
		itmsec = 0;
	}
	else
	{
		iHMS = llADSec % SECS_OF_DAY;
		itmhour = iHMS / SECS_OF_HOUR;
		itmmin = (iHMS / SECS_OF_MINUTE) % SECS_OF_MINUTE;
		itmsec = iHMS % SECS_OF_MINUTE;
	}

	RESULT_GMTIME_GRE.tm_year = itmyear;
	RESULT_GMTIME_GRE.tm_mon = itmmon;
	RESULT_GMTIME_GRE.tm_mday = itmmday;
	RESULT_GMTIME_GRE.tm_hour = itmhour;
	RESULT_GMTIME_GRE.tm_min = itmmin;
	RESULT_GMTIME_GRE.tm_sec = itmsec;

	return &RESULT_GMTIME_GRE;
}

//Currently, there is something wrong.
//It is not always typo after BC 0045 this period(BC 0045-01-01 - BC 0009-12-31).
struct tm *calcal_by_julian_typo_sec(time_t fixedDateSecs)
{
	time_t llADSec;
	int isADFlag = 0;
	int isLeapFlag = 0;
	int iTypoLeapYear = 0;
	int iLeftYears = 0;
	int iHMS = 0;
	//Temporary variables of result.
	int itmyear = 0;
	int itmmon = 0;//January = 1
	int itmmday = 0;
	int itmhour = 0;
	int itmmin = 0;
	int itmsec = 0;

//	llADSec = fixedDateSecs;//not necessary to adjust fixed date?
	//set BC AND AD flag
/***	if(llADSec >= 0)
	{
		isADFlag = 1;
	}
	else
	{//not very possible for gregorian calendar
		isADFlag = -1;
		llADSec =-llADSec;
	}***/
	llADSec = fixedDateSecs - SECS_CUTOVER_FOR_JULIAN_TYPO;
	llADSec += SECS_OFFSET_FOR_JULIAN_TYPO;
	/***YEAR MONTH DAY***/
	//check incorrect leap year loop
	if(llADSec >= SECS_OF_LEAP_TYPO)
	{
		iTypoLeapYear = llADSec / SECS_OF_LEAP_TYPO;
		itmyear += iTypoLeapYear * 3;
		llADSec -= SECS_OF_LEAP_TYPO * iTypoLeapYear;
	}
	//check nonleap year
	if(llADSec >= SECS_OF_NONLEAP_YEAR)
	{
		iLeftYears = llADSec / SECS_OF_NONLEAP_YEAR;
		itmyear += iLeftYears;
		llADSec -= SECS_OF_NONLEAP_YEAR * iLeftYears;
	}
	//there is neither BC 0 nor AD 0.
	if(llADSec >= 0)//back in time
	{//It should be Astronomical year numbering in this way.
		++itmyear;
	}
	itmyear += YEAR_OFFSET_FOR_JULIAN_TYPO;
	//check leap year for incorrect julian calendar
	isLeapFlag = is_leap_year_incorrect(itmyear - 1);
	//It is not necessary if using Astronomical year numbering.
	if(itmyear <= 0)
	{
		--itmyear;
	}
	//check month and day
	if(llADSec >= 0)
	{
		for(int i=0; i < MONTHS_OF_YEAR; ++i)
		{
			if((llADSec -= SECS_OF_MONTHS_COMMON[i]) < 0)// <= is incorrect
			{
				itmmon = i + 1;
				itmmday = (llADSec += SECS_OF_MONTHS_COMMON[i]) / SECS_OF_DAY + 1;
				break;
			}
		}
		if(isLeapFlag && itmmon > 2)
		{
			--itmmday;
			if(itmmday <= 0)
			{
				--itmmon;
				itmmday = SECS_OF_MONTHS_COMMON[itmmon];//SECS_OF_MONTHS_LEAP[itmmon]
				if(itmmon == 2)
				{
					++itmmday;
				}
			}
		}
	}
	/***HOUR MINUTE SECOND***/
	if(llADSec == 0)
	{
		itmhour = 0;
		itmmin = 0;
		itmsec = 0;
	}
	else
	{
		iHMS = llADSec % SECS_OF_DAY;
		itmhour = iHMS / SECS_OF_HOUR;
		itmmin = (iHMS / SECS_OF_MINUTE) % SECS_OF_MINUTE;
		itmsec = iHMS % SECS_OF_MINUTE;
	}

	RESULT_GMTIME_GRE.tm_year = itmyear;
	RESULT_GMTIME_GRE.tm_mon = itmmon;
	RESULT_GMTIME_GRE.tm_mday = itmmday;
	RESULT_GMTIME_GRE.tm_hour = itmhour;
	RESULT_GMTIME_GRE.tm_min = itmmin;
	RESULT_GMTIME_GRE.tm_sec = itmsec;

	return &RESULT_GMTIME_GRE;
}

struct tm *gmtime_by_gre(const time_t *timeptr)
{
	struct tm *result = NULL;
//	result=gmtime_by_gre_day(timeptr);
	result=gmtime_by_gre_sec(timeptr);
	return result;
}

void test_all_gre_constant(void)
{
	time_t temp = -31564749l;//-62162323149
	time_t secsOfDay			= SECS_OF_DAY;
	time_t daysOfLeapYear		= DAYS_OF_LEAP_YEAR;
	time_t daysOfNonleapYear	= DAYS_OF_NONLEAP_YEAR;
	time_t daysOfLeapLoop		= DAYS_OF_LEAP_LOOP;
	time_t daysOf100YearLoop	= DAYS_OF_100_YEAR_LOOP;
	time_t daysOf400YearLoop	= DAYS_OF_400_YEAR_LOOP;
	time_t daysBefore1970		= DAYS_BEFORE_1970;
	time_t secsOfLeapYear		= SECS_OF_LEAP_YEAR;
	time_t secsOfNonleapYear	= SECS_OF_NONLEAP_YEAR;
	time_t secsOfLeapLoop		= SECS_OF_LEAP_LOOP;
	time_t secsOf100LeapLoop	= SECS_OF_100_YEAR_LOOP;
	time_t secsOf400LeapLoop	= SECS_OF_400_YEAR_LOOP;
	time_t secsBefore1970		= SECS_OF_AD_BEFORE_1970;
	struct tm *pGTMge = gmtime_by_gre(NULL);//&temp NULL
	printf("The value of SECS_OF_DAY is %d\n", SECS_OF_DAY);
	printf("The value of SECS_OF_DAY is %"PRId64"\n", secsOfDay);
	printf("The value of DAYS_OF_LEAP_YEAR is %"PRId64"\n", daysOfLeapYear);
	printf("The value of DAYS_OF_NONLEAP_YEAR is %"PRId64"\n", daysOfNonleapYear);
	printf("The value of DAYS_OF_LEAP_LOOP is %"PRId64"\n", daysOfLeapLoop);
	printf("The value of DAYS_OF_100_YEAR_LOOP is %"PRId64"\n", daysOf100YearLoop);
	printf("The value of DAYS_OF_400_YEAR_LOOP is %"PRId64"\n", daysOf400YearLoop);
	printf("The value of DAYS_BEFORE_1970 is %"PRId64"\n", daysBefore1970);
	printf("The value of SECS_OF_LEAP_YEAR is %"PRId64"\n", secsOfLeapYear);
	printf("The value of SECS_OF_NONLEAP_YEAR is %"PRId64"\n", secsOfNonleapYear);
	printf("The value of SECS_OF_LEAP_LOOP is %"PRId64"\n", secsOfLeapLoop);
	printf("The value of SECS_OF_100_YEAR_LOOP is %"PRId64"\n", secsOf100LeapLoop);
	printf("The value of SECS_OF_400_YEAR_LOOP is %"PRId64"\n", secsOf400LeapLoop);
	printf("The value of SECS_BEFORE_1970 is %"PRId64"\n", secsBefore1970);
	printf("The current time is %05d-%02d-%02d %02d:%02d:%02d. \n",
			pGTMge->tm_year, pGTMge->tm_mon, pGTMge->tm_mday,
			pGTMge->tm_hour, pGTMge->tm_min, pGTMge->tm_sec);
}
