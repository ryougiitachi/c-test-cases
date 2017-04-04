/**
 * time_lunar_calendar.c
 *
 *  Created on: 2016Äê11ÔÂ6ÈÕ
 *      Author: 
 */

#include "time_lunar_calendar.h"

const int SECS_OF_DAY = 86400;

const int COUNT_OF_HEAVENLY_STEMS = 10;
const int COUNT_OF_EARTHLY_BRANCHES = 12;

const int HEAVENLY_STEM_IN_1970 = 7;
const int EARTHLY_BRANCH_IN_1970 = 11;

/**
 * These methods are based on gregorian calendar year. 
 * */
int getHeavenlyStemByYear(int year);
int getEarthlyBranchByYear(int year);

int getHeavenlyStemByYear(int year)
{
	int offset = year - 1970;
	int heavenly = (HEAVENLY_STEM_IN_1970 + offset) % COUNT_OF_HEAVENLY_STEMS;
	if(heavenly < 0)
	{
		heavenly += COUNT_OF_HEAVENLY_STEMS;
	}
	return heavenly;
}

int getEarthlyBranchByYear(int year)
{
	int offset = year - 1970;
	int earthly = (EARTHLY_BRANCH_IN_1970 + offset) % COUNT_OF_EARTHLY_BRANCHES;
	if(earthly < 0)
	{
		earthly += COUNT_OF_EARTHLY_BRANCHES;
	}
	return earthly;
}
