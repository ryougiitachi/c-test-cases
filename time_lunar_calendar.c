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
 *
 * */
#define COUNT_TERM_IAU1980_NUTATION 63
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

#define COUNT_IAU1980_ARGUMENT_PARAMS 4

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


/**
 * Refer to Chapter 45 in Astronomical Algorithms
 * Terms of Moon Longitude
 * {a for D, b for M, c for M', d for F, amplitude A for ¦²I, amplitude A for ¦²r }
 * */
#define COUNT_TERM_ELP200082_LONGITUDE 60
STERM_ELP200082_MOON LIST_TERM_ELP200082_LONGITUDE[] = {
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
 * Refer to Chapter 45 in Astronomical Algorithms
 * Terms of Moon Latitude
 * {a for D, b for M, c for M', d for F, amplitude A for ¦²I, reserved}
 * */
#define COUNT_TERM_ELP200082_LATITUDE 60
STERM_ELP200082_MOON LIST_TERM_ELP200082_LATITUDE[] = {
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

double LIST_ELP200082_ARGUMENT_D_PARAMS[] = {
		297.8502042, 445267.1115168, -0.0016300, 1.0/545868.0, -1.0/113065000.0
};

double LIST_ELP200082_ARGUMENT_M_PARAMS[] = {
		357.5291092, 35999.0502909, -0.0001536, -1.0/24490000.0, 0
};

double LIST_ELP200082_ARGUMENT_Mp_PARAMS[] = {
		134.9634114, 477198.8676313, 0.0089970, 1.0/69699.0, -1.0/14712000.0
};

double LIST_ELP200082_ARGUMENT_F_PARAMS[] = {
		93.2720993, 483202.0175273, -0.0034029, -1.0/3526000.0, 1.0/863310000.0
};

double LIST_ELP200082_ARGUMENT_Lp_PARAMS[] = {
		218.3164591, 481267.88134236, - 0.0013268, 1.0/538841.0, -1.0/65194000.0
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
 * return unit is degree.
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
 * Calculate when new moon appears.
 * Refer to http://blog.csdn.net/orbit/article/details/8223751 GetMoonEclipticParameter
 * calculate parameters D, M, M', F in the formula ¦È = a * D + b * M + c * M' + d * F
 * */
void calculateELP200082MEPeriodicTermParams(double dt,
		PPARAM_TERM_ELP200082_MOON_ECLIPTIC params)
{
	//D = 297.8502042 + 445267.1115168 * T^1 - 0.0016300 * T^2 + T^3 / 545868 - T^4 / 113065000
	params->D = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->D *= dt;
		params->D += LIST_ELP200082_ARGUMENT_D_PARAMS[i];
	}
	//M = 357.5291092 + 35999.0502909 * T^1 - 0.0001536 * T^2 + T^3 / 24490000
	params->M = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->M *= dt;
		params->M += LIST_ELP200082_ARGUMENT_M_PARAMS[i];
	}
	//M' = 134.9634114 + 477198.8676313 * T^1 + 0.0089970 * T^2 + T^3 / 69699 - T^4 / 14712000
	params->Mp = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->Mp *= dt;
		params->Mp += LIST_ELP200082_ARGUMENT_Mp_PARAMS[i];
	}
	//F = 93.2720993 + 483202.0175273 * T^1 - 0.0034029 * T^2 - T^3 / 3526000 + T^4 / 863310000
	params->F = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->F *= dt;
		params->F += LIST_ELP200082_ARGUMENT_F_PARAMS[i];
	}
	//E = 1 - 0.002516 * T^1 - 0.0000074 * T^2
	params->E = (-0.0000074 * dt -0.002516) * dt + 1.0;
	//L'=218.3164591 + 481267.88134236 * T - 0.0013268 * T^2 + T^3 / 538841 - T^4 / 65194000
	params->Lp = 0.0;
	for(int i = COUNT_ELP200082_ARGUMENT_PARAMS - 1; i >=0; --i)
	{
		params->Lp *= dt;
		params->Lp += LIST_ELP200082_ARGUMENT_Lp_PARAMS[i];
	}
//	double d = PI;
}

/**
 * Calculate when new moon appears.
 * Refer to http://blog.csdn.net/orbit/article/details/8223751 CalcMoonECLongitudePeriodicTbl
 * calculate each periodic term of moon ecliptic longitude and sum all of them,
 * and then return this result.
 * MELong means Moon Ecliptic Longitude = =
 * */
double getELP200082MELongPeriodicTermSum(double dt,
		const PPARAM_TERM_ELP200082_MOON_ECLIPTIC params)
{
	double dSumI = 0.0;
	double dTermDegree = 0.0; // degree
	double dTermRadian = 0.0; // radian
	for(int i=0; i < COUNT_TERM_ELP200082_LONGITUDE; ++i)
	{
		dTermDegree = LIST_TERM_ELP200082_LONGITUDE[i].D * params->D +
				LIST_TERM_ELP200082_LONGITUDE[i].M * params->M +
				LIST_TERM_ELP200082_LONGITUDE[i].Mp * params->Mp +
				LIST_TERM_ELP200082_LONGITUDE[i].F * params->F;
		dTermRadian = getRadianFromDegree(dTermDegree);
		dSumI += LIST_TERM_ELP200082_LONGITUDE[i].amplitudeAsin * sin(dTermRadian) *
				pow(params->E, fabs(LIST_TERM_ELP200082_LONGITUDE[i].M));
	}
	return dSumI;
}
/**
 * Calculate when new moon appears.
 * Refer to http://blog.csdn.net/orbit/article/details/8223751 CalcMoonLongitudePerturbation
 * Used parameters are L' / F.
 * */
double getELP200082MELongPerturbation(double dt, const PPARAM_TERM_ELP200082_MOON_ECLIPTIC params)
{
	double dPerturbation = 0.0;
	double T = dt;

	//A1 = 119.75 + 131.849 * T degree
	double degreeA1 = 119.75 + 131.849 * T;
	//A2 = 53.09 + 479264.290 * T degree
	double degreeA2 = 53.09 + 479264.290 * T;
	degreeA1 = getDegreeIn360(degreeA1);
	degreeA2 = getDegreeIn360(degreeA2);

	//¦²I += +3958 * sin(A1) + 1962 * sin(L' - F) + 318 * sin(A2)
	dPerturbation += 3958.0 * sin(getRadianFromDegree(degreeA1));
	dPerturbation += 1962.0 * sin(getRadianFromDegree(params->Lp - params->F));
	dPerturbation += 318.0 * sin(getRadianFromDegree(degreeA2));

	return dPerturbation;
}

/**
 * Calculate when new moon appears.
 * Refer to http://blog.csdn.net/orbit/article/details/8223751 GetMoonEclipticLongitudeEC
 * calculate Moon Ecliptic Longitude.
 * */
double getELP200082MELongitude(const time_t* timePoint)
{
	double longitude = 0.0;
	double dJulianCentury = getJulianCenturyBySecond(timePoint);
	//calculate term parameters of moon ecliptic longitude and latitude.
	SPARAM_TERM_ELP200082_MOON_ECLIPTIC params;
	calculateELP200082MEPeriodicTermParams(dJulianCentury, &params);
	//calculate and sum all terms of moon ecliptic longitude.
	double dSumI = getELP200082MELongPeriodicTermSum(dJulianCentury, &params);
	//calculate perturbation which has influence on moon ecliptic longitude by Venus / Earth / Jupiter.
	dSumI += getELP200082MELongPerturbation(dJulianCentury, &params);

	//¦Ë = L'+ ¦²I / 1000000.0
	longitude = params.Lp + dSumI/1000000.0;//millionth
	//calculate nutation
	longitude += getIAU1980EarthLongitudeNutation(dJulianCentury);
	longitude = getDegreeIn360(longitude);//degree mod 360.0

	return longitude;
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
