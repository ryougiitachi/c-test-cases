/**
 * time_lunar_calendar.c
 *
 *  Created on: 2016Äê11ÔÂ6ÈÕ
 *      Author: 
 */

#include <math.h>
#include "math_custom.h"
#include "time_calendar.h"
#include "time_julian_day.h"
#include "time_lunar_calendar.h"

//const int SECS_OF_DAY = 86400;

const int COUNT_OF_HEAVENLY_STEMS = 10;
const int COUNT_OF_EARTHLY_BRANCHES = 12;

const int HEAVENLY_STEM_IN_1970 = 7;
const int EARTHLY_BRANCH_IN_1970 = 11;

/**
 * Refer to Chapter 21 in Astronomical Algorithms
 * Terms of Nutation
 * 63 periodic terms of IAU 1980
 * */
//warning: 'LIST_TERM_IAU1980_NUTATION' initialized and declared 'extern'
//it is better to not use extern here?
STERM_IAU1980_NUTATION LIST_TERM_IAU1980_NUTATION[] = {
		{0, 0, 0, 0, 1, -171996, -174.2, +92025, +8.9},
		{-2, 0, 0, 2, 2, -13187, -1.6, +5736, -3.1},
		{0, 0, 0, 2, 2, -2274, -0.2, +977, -0.5},
		{0, 0, 0, 0, 2, +2062, +0.2, -895, +0.5},
		{0, 1, 0, 0, 0, +1426, -3.4, +54, -0.1},
		{0, 0, 1, 0, 0, +712, +0.1, -7, 0},
		{-2, 1, 0, 2, 2, -517, +1.2, +224, -0.6},
		{0, 0, 0, 2, 1, -386, -0.4, +200, 0},
		{0, 0, 1, 2, 2, -301, 0, +129, -0.1},
		{-2, -1, 0, 2, 2, +217, -0.5, -95, +0.3},
		{-2, 0, 1, 0, 0, -158, 0, 0, 0},
		{-2, 0, 0, 2, 1, +129, +0.1, -70, 0},
		{0, 0, -1, 2, 2, +123, 0, -53, 0},
		{2, 0, 0, 0, 0, +63, 0, 0, 0},
		{0, 0, 1, 0, 1, +63, +0.1, -33, 0},
		{2, 0, -1, 2, 2, -59, 0, +26, 0},
		{0, 0, -1, 0, 1, -58, -0.1, +32, 0},
		{0, 0, 1, 2, 1, -51, 0, +27, 0},
		{-2, 0, 2, 0, 0, +48, 0, 0, 0},
		{0, 0, -2, 2, 1, +46, 0, -24, 0},
		{2, 0, 0, 2, 2, -38, 0, +16, 0},
		{0, 0, 2, 2, 2, -31, 0, +13, 0},
		{0, 0, 2, 0, 0, +29, 0, 0, 0},
		{-2, 0, 1, 2, 2, +29, 0, -12, 0},
		{0, 0, 0, 2, 0, +26, 0, 0, 0},
		{-2, 0, 0, 2, 0, -22, 0, 0, 0},
		{0, 0, -1, 2, 1, +21, 0, -10, 0},
		{0, 2, 0, 0, 0, +17, -0.1, 0, },
		{2, 0, -1, 0, 1, +16, 0, -8, 0},
		{-2, 2, 0, 2, 2, -16, +0.1, +7, 0},
		{0, 1, 0, 0, 1, -15, 0, +9, 0},
		{-2, 0, 1, 0, 1, -13, 0, +7, 0},
		{0, -1, 0, 0, 1, -12, 0, +6, 0},
		{0, 0, 2, -2, 0, +11, 0, 0, 0},
		{2, 0, -1, 2, 1, -10, 0, +50, },
		{2, 0, 1, 2, 2, -8, 0, +3, 0},
		{0, 1, 0, 2, 2, +7, 0, -3, 0},
		{-2, 1, 1, 0, 0, -7, 0, 0, 0},
		{0, -1, 0, 2, 2, -7, 0, +3, 0},
		{2, 0, 0, 2, 1, -7, 0, +3, 0},
		{2, 0, 1, 0, 0, +6, 0, 0, 0},
		{-2, 0, 2, 2, 2, +6, 0, -3, 0},
		{-2, 0, 1, 2, 1, +6, 0, -3, 0},
		{2, 0, -2, 0, 1, -6, 0, +3, 0},
		{2, 0, 0, 0, 1, -6, 0, +3, 0},
		{0, -1, 1, 0, 0, +5, 0, 0, 0},
		{-2, -1, 0, 2, 1, -5, 0, +3, 0},
		{-2, 0, 0, 0, 1, -5, 0, +3, 0},
		{0, 0, 2, 2, 1, -5, 0, +3, 0},
		{-2, 0, 2, 0, 1, +4, 0, 0, 0},
		{-2, 1, 0, 2, 1, +4, 0, 0, 0},
		{0, 0, 1, -2, 0, +4, 0, 0, 0},
		{-1, 0, 1, 0, 0, -4, 0, 0, 0},
		{-2, 1, 0, 0, 0, -4, 0, 0, 0},
		{1, 0, 0, 0, 0, -4, 0, 0, 0},
		{0, 0, 1, 2, 0, +3, 0, 0, 0},
		{0, 0, -2, 2, 2, -3, 0, 0, 0},
		{-1, -1, 1, 0, 0, -3, 0, 0, 0},
		{0, 1, 1, 0, 0, -3, 0, 0, 0},
		{0, -1, 1, 2, 2, -3, 0, 0, 0},
		{2, -1, -1, 2, 2, -3, 0, 0, 0},
		{0, 0, 3, 2, 2, -3, 0, 0, 0},
		{2, -1, 0, 2, 2, -3, 0, 0, 0}
};

double LIST_IAU1980_ARGUMENT_D_PARAMS[] = {
		297.85036, 455267.111480, -0.0019142, 1.0/189474.0
};

double LIST_IAU1980_ARGUMENT_M_PARAMS[] = {
		357.52772, 35999.050340, -0.0001603, -1.0/300000.0
};

double LIST_IAU1980_ARGUMENT_Mp_PARAMS[] = {
		134.96298, 477198.867398, 0.0086972, 1.0/56250.0
};

double LIST_IAU1980_ARGUMENT_F_PARAMS[] = {
		93.27191, 483202.017538, -0.0036825, 1.0/327270.0
};

double LIST_IAU1980_ARGUMENT_Omega_PARAMS[] = {
		125.04452, -1934.136261, 0.0020708, 1.0/450000.0
};


void calculateIAU1980EarthNutationParameters(double dt, PPARAM_TERM_IAU1980_NUTATION params)
{
	//D = 297.85036 + 455267.111480 * T - 0.0019142 * T2 + T3 / 189474
	params->D = 0.0;
	for(int i = COUNT_IAU1980_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->D *= dt;
		params->D += LIST_IAU1980_ARGUMENT_D_PARAMS[i];
	}
	//M = 357.52772 + 35999.050340 * T - 0.0001603 * T2 - T3 / 300000
	params->M = 0.0;
	for(int i = COUNT_IAU1980_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->M *= dt;
		params->M += LIST_IAU1980_ARGUMENT_M_PARAMS[i];
	}
	//M'= 134.96298 + 477198.867398 * T + 0.0086972 * T2 + T3 / 56250
	params->Mp = 0.0;
	for(int i = COUNT_IAU1980_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->Mp *= dt;
		params->Mp += LIST_IAU1980_ARGUMENT_Mp_PARAMS[i];
	}
	//F = 93.27191 + 483202.017538 * T - 0.0036825 * T2 + T3 / 327270
	params->F = 0.0;
	for(int i = COUNT_IAU1980_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->F *= dt;
		params->F += LIST_IAU1980_ARGUMENT_F_PARAMS[i];
	}
	//¦¸= 125.04452 - 1934.136261 * T + 0.0020708 * T2 + T3 / 450000
	params->Omega = 0.0;
	for(int i = COUNT_IAU1980_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->Omega *= dt;
		params->Omega += LIST_IAU1980_ARGUMENT_Omega_PARAMS[i];
	}
}

/**
 * Calculate earth longitude nutation
 * Refer to http://blog.csdn.net/orbit/article/details/7944248 CalcEarthLongitudeNutation
 * 
 * @param dt	Julian day.
 * @return The unit of result is degree.
 * */
double getIAU1980EarthLongitudeNutation(double dt)
{
	double dNutation = 0.0;

	SPARAM_TERM_IAU1980_NUTATION params;
	calculateIAU1980EarthNutationParameters(dt, &params);

	double dTermDegree = 0.0;
//	double dTermRadian = 0.0;
	for(int i = 0; i < COUNT_TERM_IAU1980_NUTATION; ++i)
	{
		dTermDegree = LIST_TERM_IAU1980_NUTATION[i].D * params.D +
				LIST_TERM_IAU1980_NUTATION[i].M * params.M +
				LIST_TERM_IAU1980_NUTATION[i].Mp * params.Mp +
				LIST_TERM_IAU1980_NUTATION[i].F * params.F +
				LIST_TERM_IAU1980_NUTATION[i].Omega * params.Omega;
		dTermDegree = getDegreeIn360(dTermDegree);//degree mod 360
		dNutation += (LIST_TERM_IAU1980_NUTATION[i].sine1 + LIST_TERM_IAU1980_NUTATION[i].sine2 * dt) *
				sin(getRadianFromDegree(dTermDegree));
	}
	//return should be 0.0001 / 3600.0, because 0.0001 is unit of sine1, and 3600 is degree second.
	//unit is 0.0001".
	return dNutation / 36000000.0;
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
