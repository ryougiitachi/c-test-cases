/**
 * time_lunar_calendar.c
 *
 *  Created on: 2016Äê11ÔÂ6ÈÕ
 *      Author: 
 */

#include <math.h>
#include "math_custom.h"
#include "time_calendar.h"
#include "time_lunar_calendar.h"

//const int SECS_OF_DAY = 86400;

const int COUNT_OF_HEAVENLY_STEMS = 10;
const int COUNT_OF_EARTHLY_BRANCHES = 12;

const int HEAVENLY_STEM_IN_1970 = 7;
const int EARTHLY_BRANCH_IN_1970 = 11;

/**
 * Terms of Moon Longitude
 * */
#define COUNT_TERM_ELP200082_LONGITUDE 60
extern PTERM_ELP200082_MOON LIST_TERM_ELP200082_LONGITUDE = {
		{0, 0, 1, 0, 6288744, -20905355},
		{2, 0, -1, 0, 1274027, -3699111},
		{2, 0, 0, 0, 658314, -2955968},
		{0, 0, 2, 0, 213618, -569925},
		{0, 1, 0, 0, -185116, 48888},
		{0, 0, 0, 2, -114332, -3149},
		{2, 0, -2, 0, 58793, 246158},
		{2, -1, -1, 0, 57066, -152138},
		{2, 0, 1, 0, 53322, -170733},
		{2, -1, 0, 0, 45758, -204586},
		{0, 1, -1, 0, -40923, -129620},
		{1, 0, 0, 0, -34720, 108743},
		{0, 1, 1, 0, -30383, 104755},
		{2, 0, 0, -2, 15327, 10321},
		{0, 0, 1, 2, -12528, 0},
		{0, 0, 1, -2, 10980, 79661},
		{4, 0, -1, 0, 10675, -34782},
		{0, 0, 3, 0, 10034, -23210},
		{4, 0, -2, 0, 8548, -21636},
		{2, 1, -1, 0, -7888, 24208},
		{2, 1, 0, 0, -6766, 30824},
		{1, 0, -1, 0, -5163, -8379},
		{1, 1, 0, 0, 4987, -16675},
		{2, -1, 1, 0, 4036, -12831},
		{2, 0, 2, 0, 3994, -10445},
		{4, 0, 0, 0, 3861, -11650},
		{2, 0, -3, 0, 3665, 14403},
		{0, 1, -2, 0, -2689, -7003},
		{2, 0, -1, 2, -2602, 0},
		{2, -1, -2, 0, 2390, 10056},
		{1, 0, 1, 0, -2348, 6322},
		{2, -2, 0, 0, 2236, -9884},
		{0, 1, 2, 0, -2120, 5751},
		{0, 2, 0, 0, -2069, 0},
		{2, -2, -1, 0, 2048, -4950},
		{2, 0, 1, -2, -1773, 4130},
		{2, 0, 0, 2, -1595, 0},
		{4, -1, -1, 0, 1215, -3958},
		{0, 0, 2, 2, -1110, 0},
		{3, 0, -1, 0, -892, 3258},
		{2, 1, 1, 0, -810, 2616},
		{4, -1, -2, 0, 759, -1897},
		{0, 2, -1, 0, -713, -2117},
		{2, 2, -1, 0, -700, 2354},
		{2, 1, -2, 0, 691, 0},
		{2, -1, 0, -2, 596, 0},
		{4, 0, 1, 0, 549, -1423},
		{0, 0, 4, 0, 537, -1117},
		{4, -1, 0, 0, 520, -1571},
		{1, 0, -2, 0, -487, -1739},
		{2, 1, 0, -2, -399, 0},
		{0, 0, 2, -2, -381, -4421},
		{1, 1, 1, 0, 351, 0},
		{3, 0, -2, 0, -340, 0},
		{4, 0, -3, 0, 330, 0},
		{2, -1, 2, 0, 327, 0},
		{0, 2, 1, 0, -323, 1165},
		{1, 1, -1, 0, 299, 0},
		{2, 0, 3, 0, 294, 0},
		{2, 0, -1, -2, 0, 8752}
};

/**
 * Terms of Moon Latitude
 * */
#define COUNT_TERM_ELP200082_LATITUDE 60
extern PTERM_ELP200082_MOON LIST_TERM_ELP200082_LATITUDE = {
		{0, 0, 0, 1, 5128122, 0},
		{0, 0, 1, 1, 280602, 0},
		{0, 0, 1, -1, 277693, 0},
		{2, 0, 0, -1, 173237, 0},
		{2, 0, -1, 1, 55413, 0},
		{2, 0, -1, -1, 46271, 0},
		{2, 0, 0, 1, 32573, 0},
		{0, 0, 2, 1, 17198, 0},
		{2, 0, 1, -1, 9266, 0},
		{0, 0, 2, -1, 8822, 0},
		{2, -1, 0, -1, 8216, 0},
		{2, 0, -2, -1, 4324, 0},
		{2, 0, 1, 1, 4200, 0},
		{2, 1, 0, -1, -3359, 0},
		{2, -1, -1, 1, 2463, 0},
		{2, -1, 0, 1, 2211, 0},
		{2, -1, -1, -1, 2065, 0},
		{0, 1, -1, -1, -1870, 0},
		{4, 0, -1, -1, 1828, 0},
		{0, 1, 0, 1, -1794, 0},
		{0, 0, 0, 3, -1749, 0},
		{0, 1, -1, 1, -1565, 0},
		{1, 0, 0, 1, -1491, 0},
		{0, 1, 1, 1, -1475, 0},
		{0, 1, 1, -1, -1410, 0},
		{0, 1, 0, -1, -1344, 0},
		{1, 0, 0, -1, -1335, 0},
		{0, 0, 3, 1, 1107, 0},
		{4, 0, 0, -1, 1021, 0},
		{4, 0, -1, 1, 833, 0},
		{0, 0, 1, -3, 777, 0},
		{4, 0, -2, 1, 671, 0},
		{2, 0, 0, -3, 607, 0},
		{2, 0, 2, -1, 596, 0},
		{2, -1, 1, -1, 491, 0},
		{2, 0, -2, 1, -451, 0},
		{0, 0, 3, -1, 439, 0},
		{2, 0, 2, 1, 422, 0},
		{2, 0, -3, -1, 421, 0},
		{2, 1, -1, 1, -366, 0},
		{2, 1, 0, 1, -351, 0},
		{4, 0, 0, 1, 331, 0},
		{2, -1, 1, 1, 315, 0},
		{2, -2, 0, -1, 302, 0},
		{0, 0, 1, 3, -283, 0},
		{2, 1, 1, -1, -229, 0},
		{1, 1, 0, -1, 223, 0},
		{1, 1, 0, 1, 223, 0},
		{0, 1, -2, -1, -220, 0},
		{2, 1, -1, -1, -220, 0},
		{1, 0, 1, 1, -185, 0},
		{2, -1, -2, -1, 181, 0},
		{0, 1, 2, 1, -177, 0},
		{4, 0, -2, -1, 176, 0},
		{4, -1, -1, -1, 166, 0},
		{1, 0, 1, -1, -164, 0},
		{4, 0, 1, -1, 132, 0},
		{1, 0, -1, -1, -119, 0},
		{4, -1, 0, -1, 115, 0},
		{2, -2, 0, 1, 107, 0}
};

#define COUNT_ELP200082_ARGUMENT_PARAMS 5

extern double *LIST_ELP200082_ARGUMENT_D_PARAMS = {
		297.8502042, 445267.1115168, -0.0016300, 1.0/545868.0, -1.0/113065000.0
};

extern double *LIST_ELP200082_ARGUMENT_M_PARAMS = {
		357.5291092, 35999.0502909, -0.0001536, -1.0/24490000.0, 0
};

extern double *LIST_ELP200082_ARGUMENT_Mp_PARAMS = {
		134.9634114, 477198.8676313, 0.0089970, 1.0/69699.0, -1.0/14712000.0
};

extern double *LIST_ELP200082_ARGUMENT_F_PARAMS = {
		93.2720993, 483202.0175273, -0.0034029, -1.0/3526000.0, -1.0/863310000.0
};

/**
 * calculate parameters D, M, M', F in the formula ¦È = a * D + b * M + c * M' + d * F
 * */
void calculateELP200082ArgParams(double dt,
		double *paramD, double *paramM, double *paramMp, double *paramF)
{
	paramD[0] = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		paramD[0] *= dt;
		paramD[0] += LIST_ELP200082_ARGUMENT_D_PARAMS[i];
	}
	paramM[0] = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		paramM[0] *= dt;
		paramM[0] += LIST_ELP200082_ARGUMENT_M_PARAMS[i];
	}
	paramMp[0] = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		paramMp[0] *= dt;
		paramMp[0] += LIST_ELP200082_ARGUMENT_Mp_PARAMS[i];
	}
	paramF[0] = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		paramF[0] *= dt;
		paramF[0] += LIST_ELP200082_ARGUMENT_F_PARAMS[i];
	}
//	double d = PI;
}

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
