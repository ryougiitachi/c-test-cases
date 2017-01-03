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
/***
//There is something wrong when using macro, which seems the address of the macro?
#define SECS_OF_DAY 24ll * 60ll * 60ll
#define SECS_OF_HOUR 3600ll
#define SECS_OF_MINUTE 60ll

#define DAYS_OF_LEAP_YEAR 366ll
#define DAYS_OF_NONLEAP_YEAR 365ll

#define DAYS_OF_LEAP_LOOP (DAYS_OF_LEAP_YEAR * 4ll + 1ll)
#define DAYS_OF_100_YEAR_LOOP (24ll * 366ll + 76ll * 365ll)
#define DAYS_OF_400_YEAR_LOOP (DAYS_OF_100_YEAR_LOOP * 4ll + 1ll)
#define DAYS_BEFORE_1970 (DAYS_OF_400_YEAR_LOOP * 4ll + DAYS_OF_100_YEAR_LOOP * 3ll + DAYS_OF_LEAP_YEAR * 17ll + DAYS_OF_NONLEAP_YEAR * (53ll-1ll))

#define DAYS_OF_JANUARY 31
#define DAYS_OF_FEBRUARY_LEAP 29
#define DAYS_OF_FEBRUARY_NONLEAP 28
#define DAYS_OF_MARCH 31
#define DAYS_OF_APRIL 30
#define DAYS_OF_MAY 31
#define DAYS_OF_JUNE 30
#define DAYS_OF_JULY 31
#define DAYS_OF_AUGUST 31
#define DAYS_OF_SEPTEMBER 30
#define DAYS_OF_OCTOBER 31
#define DAYS_OF_NOVEMBER 30
#define DAYS_OF_DECEMBER 31

#define SECS_OF_LEAP_YEAR (DAYS_OF_LEAP_YEAR * SECS_OF_DAY)
#define SECS_OF_NONLEAP_YEAR (DAYS_OF_NONLEAP_YEAR * SECS_OF_DAY)

#define SECS_OF_LEAP_LOOP (DAYS_OF_LEAP_LOOP * SECS_OF_DAY)
#define SECS_OF_100_YEAR_LOOP (DAYS_OF_100_YEAR_LOOP * SECS_OF_DAY)
#define SECS_OF_400_YEAR_LOOP (DAYS_OF_400_YEAR_LOOP * SECS_OF_DAY)
#define SECS_BEFORE_1970 (DAYS_BEFORE_1970 * SECS_OF_DAY)
***/
const int MONTHS_OF_YEAR = 12;

const int SECS_OF_DAY = 86400;
const int SECS_OF_HOUR = 3600;
const int SECS_OF_MINUTE = 60;

const int DAYS_OF_LEAP_YEAR = 366ll;
const int DAYS_OF_NONLEAP_YEAR = 365ll;

const int DAYS_OF_LEAP_LOOP = (365ll * 4ll + 1ll);
const int DAYS_OF_100_YEAR_LOOP = (24ll * 366ll + 76ll * 365ll);//365*100 + 100/4 - 100/100
const int DAYS_OF_400_YEAR_LOOP = (24ll * 366ll + 76ll * 365ll) * 4ll + 1ll;//365*400 + 400/4 - 400/100 + 400/400
//const int DAYS_BEFORE_1970 = (((24ll * 366ll + 76ll * 365ll) * 4ll + 1ll) * 4ll + (24ll * 366ll + 76ll * 365ll) * 3ll + 366ll * 17ll + 365ll * (53ll-1ll));
const int DAYS_BEFORE_1970 = 1969 * 365 + 1969 / 4 - 1969 / 100 + 1969 / 400 + 1;//because AD 0004-02-28

const int DAYS_CUTOVER_FOR_GROGORIAN = 577736;
const int DAYS_CUTOVER_FOR_JULIAN_FIXED = 0;
const int DAYS_CUTOVER_FOR_JULIAN_TYPO = 0;

const int DAYS_OF_JANUARY = 31;
const int DAYS_OF_FEBRUARY_LEAP = 29;
const int DAYS_OF_FEBRUARY_NONLEAP = 28;
const int DAYS_OF_MARCH = 31;
const int DAYS_OF_APRIL = 30;
const int DAYS_OF_MAY = 31;
const int DAYS_OF_JUNE = 30;
const int DAYS_OF_JULY = 31;
const int DAYS_OF_AUGUST = 31;
const int DAYS_OF_SEPTEMBER = 30;
const int DAYS_OF_OCTOBER = 31;
const int DAYS_OF_NOVEMBER = 30;
const int DAYS_OF_DECEMBER = 31;

const time_t SECS_OF_LEAP_YEAR = (366ll * 86400ll);
const time_t SECS_OF_NONLEAP_YEAR = (365ll * 86400ll);

const time_t SECS_OF_LEAP_LOOP = ((365ll * 4ll + 1ll) * 86400ll);
const time_t SECS_OF_100_YEAR_LOOP = ((24ll * 366ll + 76ll * 365ll) * 86400ll);
const time_t SECS_OF_400_YEAR_LOOP = (((24ll * 366ll + 76ll * 365ll) * 4ll + 1ll) * 86400ll);
const time_t SECS_OF_AD_BEFORE_1970 = ((1969 * 365 + 1969 / 4 - 1969 / 100 + 1969 / 400 + 1) * 86400ll);//because AD 0004-02-28

const int SECS_OF_JANUARY = 31 * 86400;
const int SECS_OF_FEBRUARY_LEAP = 29 * 86400;
const int SECS_OF_FEBRUARY_NONLEAP = 28 * 86400;
const int SECS_OF_MARCH = 31 * 86400;
const int SECS_OF_APRIL = 30 * 86400;
const int SECS_OF_MAY = 31 * 86400;
const int SECS_OF_JUNE = 30 * 86400;
const int SECS_OF_JULY = 31 * 86400;
const int SECS_OF_AUGUST = 31 * 86400;
const int SECS_OF_SEPTEMBER = 30 * 86400;
const int SECS_OF_OCTOBER = 31 * 86400;
const int SECS_OF_NOVEMBER = 30 * 86400;
const int SECS_OF_DECEMBER = 31 * 86400;

const int SECS_OF_MONTHS_COMMON[12] = {
		31 * 86400, 28 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400
};

const int SECS_OF_MONTHS_LEAP[12] = {
		31 * 86400, 29 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 30 * 86400,
		31 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400,
		30 * 86400, 31 * 86400
};

static struct tm RESULT_GMTIME_GRE;

struct tm *gmtime_by_gre_day(const time_t *timeptr)
{
	time_t lltime = 0;
	time_t iNumDay = 0;

	int isADFlag = 0;
	int isLeapFlag = 0;
	int iNum400Years = 0;
	int iNum100Years = 0;
	int iLeapYears = 0;
	int iLeftYears = 0;
	int iHMS = 0;

	memset(&RESULT_GMTIME_GRE, 0, sizeof(struct tm));
	if(!timeptr)
	{
		time(&lltime);
	}
	else
	{
		lltime = timeptr[0];
	}
	iNumDay = (lltime + SECS_OF_AD_BEFORE_1970)/ SECS_OF_DAY;//lltime / SECS_OF_DAY + DAYS_BEFORE_1970 seems err.
	iHMS = lltime % SECS_OF_DAY;
	//set BC AND AD flag
	if(iNumDay >= 0)
	{
		isADFlag = 1;
	}
	else
	{
		isADFlag = -1;
		iNumDay =-iNumDay;
	}
	/***YEAR MONTH DAY***/
	//check 400-year loop
	if(iNumDay >= DAYS_OF_400_YEAR_LOOP)
	{
		iNum400Years = iNumDay / DAYS_OF_400_YEAR_LOOP;
		RESULT_GMTIME_GRE.tm_year += iNum400Years * 400;
		iNumDay -= DAYS_OF_400_YEAR_LOOP * iNum400Years;
	}
	//check nonleap 100-year loop
	if(iNumDay >= DAYS_OF_100_YEAR_LOOP)
	{
		iNum100Years = iNumDay / DAYS_OF_100_YEAR_LOOP;
		RESULT_GMTIME_GRE.tm_year += iNum100Years * 100;
		iNumDay -= DAYS_OF_100_YEAR_LOOP * iNum100Years;
	}
	//check leap year in nonleap 100-year loop
	if(iNumDay >= DAYS_OF_LEAP_LOOP)
	{
		iLeapYears = iNumDay / DAYS_OF_LEAP_LOOP;
		RESULT_GMTIME_GRE.tm_year += iLeapYears * 4;
		iNumDay -= DAYS_OF_LEAP_LOOP * iLeapYears;
	}
	//check nonleap year
	if(iNumDay >= DAYS_OF_NONLEAP_YEAR)
	{
		iLeftYears = iNumDay / DAYS_OF_NONLEAP_YEAR;
		RESULT_GMTIME_GRE.tm_year += iLeftYears;
		iNumDay -= DAYS_OF_NONLEAP_YEAR * iLeftYears;
	}
	//there is neither BC 0 nor AD 0.
	if(iNumDay >= 0)//back in time
	{
		++RESULT_GMTIME_GRE.tm_year;
	}
	//check leap or nonleap year
	if(isADFlag==1 && (RESULT_GMTIME_GRE.tm_year & 3)==0 && (RESULT_GMTIME_GRE.tm_year % 100) != 0)
	{//AD leap year
		isLeapFlag = 1;
	}
	else if(isADFlag==1 && (RESULT_GMTIME_GRE.tm_year % 400 ) == 0)
	{//AD leap year
		isLeapFlag = 1;
	}
	if(isADFlag==-1 && ((RESULT_GMTIME_GRE.tm_year-1) & 3)==0 && ((RESULT_GMTIME_GRE.tm_year-1) % 100) != 0)
	{//BC nonleap year
		isLeapFlag = 1;
	}
	else if(isADFlag==-1 && ((RESULT_GMTIME_GRE.tm_year-1) % 400 ) == 0)
	{//BC nonleap year
		isLeapFlag = 1;
	}
	else
	{
		isLeapFlag = 0;
	}
	//handle BC
	if(isADFlag == -1)
	{
		RESULT_GMTIME_GRE.tm_year = -RESULT_GMTIME_GRE.tm_year;//set year
		iNumDay = (isLeapFlag==0 ? DAYS_OF_NONLEAP_YEAR : DAYS_OF_LEAP_YEAR) - iNumDay;
	}
	//check month and day
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_JANUARY) <= 0)
	{//January
		RESULT_GMTIME_GRE.tm_mon = 1;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_JANUARY + 1;
	}
	if(iNumDay > 0 && isLeapFlag == 1 && (iNumDay-=DAYS_OF_FEBRUARY_LEAP) <= 0)
	{//February in leap year
		RESULT_GMTIME_GRE.tm_mon = 2;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_FEBRUARY_LEAP + 1;
	}
	if(iNumDay > 0 && isLeapFlag == 0 && (iNumDay-=DAYS_OF_FEBRUARY_NONLEAP) <= 0)
	{//February in nonleap year
		RESULT_GMTIME_GRE.tm_mon = 2;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_FEBRUARY_NONLEAP + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_MARCH) <= 0)
	{//March
		RESULT_GMTIME_GRE.tm_mon = 3;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_MARCH + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_APRIL) <= 0)
	{//April
		RESULT_GMTIME_GRE.tm_mon = 4;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_APRIL + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_MAY) <= 0)
	{//May
		RESULT_GMTIME_GRE.tm_mon = 5;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_MAY + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_JUNE) <= 0)
	{//June
		RESULT_GMTIME_GRE.tm_mon = 6;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_JUNE + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_JULY) <= 0)
	{//July
		RESULT_GMTIME_GRE.tm_mon = 7;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_JULY + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_AUGUST) <= 0)
	{//August
		RESULT_GMTIME_GRE.tm_mon = 8;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_AUGUST + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_SEPTEMBER) <= 0)
	{//September
		RESULT_GMTIME_GRE.tm_mon = 9;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_SEPTEMBER + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_OCTOBER) <= 0)
	{//October
		RESULT_GMTIME_GRE.tm_mon = 10;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_OCTOBER + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_NOVEMBER) <= 0)
	{//November
		RESULT_GMTIME_GRE.tm_mon = 11;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_NOVEMBER + 1;
	}
	if(iNumDay > 0 && (iNumDay-=DAYS_OF_DECEMBER) <= 0)
	{//December
		RESULT_GMTIME_GRE.tm_mon = 12;
		RESULT_GMTIME_GRE.tm_mday = iNumDay + DAYS_OF_DECEMBER + 1;
	}
	/***HOUR MINUTE SECOND***/
	if(iHMS == 0)
	{
		RESULT_GMTIME_GRE.tm_hour = 0;
		RESULT_GMTIME_GRE.tm_min = 0;
		RESULT_GMTIME_GRE.tm_sec = 0;
	}
	else
	{
		//handle BC
		if(iHMS < 0)
		{
			iHMS += SECS_OF_DAY;//iHMS is negative at this time.
		}
		RESULT_GMTIME_GRE.tm_hour = iHMS / SECS_OF_HOUR;
		RESULT_GMTIME_GRE.tm_min = (iHMS / SECS_OF_MINUTE) % SECS_OF_MINUTE;
		RESULT_GMTIME_GRE.tm_sec = iHMS % SECS_OF_MINUTE;
	}
	return &RESULT_GMTIME_GRE;
}

/**
 * year -> month / day -> hour / minute / second
 * */
struct tm *gmtime_by_gre_sec(const time_t *timeptr)
{
	time_t lltime = 0;
	time_t llADSec = 0;

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
		lltime = *timeptr;
	}
	llADSec = lltime + SECS_OF_AD_BEFORE_1970;
	if(llADSec >= DAYS_CUTOVER_FOR_GROGORIAN * SECS_OF_DAY)
	{
		llADSec -= SECS_OF_DAY;
	}
	//set BC AND AD flag
	if(llADSec >= 0)
	{
		isADFlag = 1;
//		++iNumDay;//plus 1 means there is no 0000-01-00.
	}
	else
	{
		isADFlag = -1;llADSec =-llADSec;
//		iNumDay =-iNumDay - 1;
	}
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
	//there is neither BC 0 nor AD 0.
	if(llADSec >= 0)//back in time
	{
		++itmyear;
	}
	//check leap or nonleap year
/**	if(isADFlag==1 && (itmyear & 3)==0 && (itmyear % 100) != 0)
	{//AD leap year
		isLeapFlag = 1;
	}
	else if(isADFlag==1 && (itmyear % 400 ) == 0)
	{//AD leap year
		isLeapFlag = 1;
	}
	else if(isADFlag==-1 && ((itmyear-1) & 3)==0 && ((itmyear-1) % 100) != 0)
	{//BC nonleap year
		isLeapFlag = 1;
	}
	else if(isADFlag==-1 && ((itmyear-1) % 400 ) == 0)
	{//BC nonleap year
		isLeapFlag = 1;
	}
	else
	{
		isLeapFlag = 0;
	}***/
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
	const int *pSecPerMonths = NULL;
	//WAHT IF llADSec < 0? both month and day are 0?
	if(llADSec >= 0)
	{
//		if(isLeapFlag)
//		{
//			pSecPerMonths = SECS_OF_MONTHS_LEAP;
//		}
//		else
//		{
//			pSecPerMonths = SECS_OF_MONTHS_COMMON;
//		}
		for(int i=0; i < MONTHS_OF_YEAR; ++i)
		{
			if((llADSec -= SECS_OF_MONTHS_COMMON[i]) <= 0)
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
//		if(llADSec < 0)
//		{
//			llADSec += SECS_OF_MONTHS[itmmon-1];
//			if(isLeapFlag == 1 && itmmon == 2)
//			{
//				llADSec += SECS_OF_DAY;
//			}
//		}
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

int is_leap_year(int year)
{
	return ((year&3)==0 && (year%100)!=0) || (year%400)==0 ? 1 : 0;
}

struct tm *gmtime_by_gre(const time_t *timeptr)
{
	struct tm *result = NULL;
	result=gmtime_by_gre_day(timeptr);
//	result=gmtime_by_gre_sec(timeptr);
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
