/*
 * time_solar_term.c
 *
 *  Created on: 2017Äê7ÔÂ11ÈÕ
 *      Author: 
 */

#include <math.h>
#include <time.h>
#include "math_custom.h"
#include "time_julian_day.h"
#include "time_lunar_calendar.h"

/**
 * 64 terms of VSOP 82/87 Earth L0
 * */
STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_L0[] = {
	{175347046, 0, 0}, 
	{3341656, 4.6692568, 6283.0758500}, 
	{34894, 4.62610, 12566.15170}, 
	{5497, 2.7441, 5753.3849}, 
	{3418, 2.8289, 3.5231}, 
	{3136, 3.6277, 77713.7715}, 
	{2676, 4.4181, 7860.4194}, 
	{2343, 6.1352, 3930.2097}, 
	{1324, 0.7425, 11506.7698}, 
	{1273, 2.0371, 529.6910}, 
	{1199, 1.1096, 1577.3435}, 
	{990, 5.233, 5884.927}, 
	{902, 2.045, 26.298}, 
	{857, 3.508, 398.149}, 
	{780, 1.179, 5223.694}, 
	{753, 2.533, 5507.553}, 
	{505, 4.583, 18849.228}, 
	{492, 4.205, 775.523}, 
	{357, 2.920, 0.067}, 
	{317, 5.849, 11790.629}, 
	{284, 1.899, 796.298}, 
	{271, 0.315, 10977.079}, 
	{243, 0.345, 5486.778}, 
	{206, 4.806, 2544.314}, 
	{205, 1.869, 5573.143}, 
	{202, 2.458, 6069.777}, 
	{156, 0.833, 213.299}, 
	{132, 3.411, 2942.463}, 
	{126, 1.083, 20.775}, 
	{115, 0.645, 0.980}, 
	{105, 0.636, 4694.003}, 
	{102, 0.976, 15720.839}, 
	{102, 4.267, 7.114}, 
	{99, 6.21, 2146.17}, 
	{98, 0.68, 155.42}, 
	{86, 5.98, 161000.69}, 
	{85, 1.30, 6275.96}, 
	{85, 3.67, 71430.70}, 
	{80, 1.81, 17260.15}, 
	{79, 3.04, 12036.46}, 
	{75, 1.76, 5088.63}, 
	{74, 3.50, 3154.69}, 
	{74, 4.68, 801.82}, 
	{70, 0.83, 9437.76}, 
	{62, 3.98, 8827.39}, 
	{61, 1.82, 7084.90}, 
	{57, 2.78, 6286.60}, 
	{56, 4.39, 14143.50}, 
	{56, 3.47, 6279.55}, 
	{52, 0.19, 12139.55}, 
	{52, 1.33, 1748.02}, 
	{51, 0.28, 5856.48}, 
	{49, 0.49, 1194.45}, 
	{41, 5.37, 8429.24}, 
	{41, 2.40, 19651.05}, 
	{39, 6.17, 10447.39}, 
	{37, 6.04, 10213.29}, 
	{37, 2.57, 1059.38}, 
	{36, 1.71, 2352.87}, 
	{36, 1.78, 6812.77}, 
	{33, 0.59, 17789.85}, 
	{30, 0.44, 83996.85}, 
	{30, 2.74, 1349.87}, 
	{25, 3.16, 4690.48}
};

/**
 * 34 terms of VSOP 82/87 Earth L1
 * */
STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_L1[] = {
	{628331966747, 0, 0}, 
	{206059, 2.678235, 6283.075850}, 
	{4303, 2.6351, 12566.1517}, 
	{425, 1.590, 3.523}, 
	{119, 5.796, 26.298}, 
	{109, 2.966, 1577.344}, 
	{93, 2.59, 18849.23}, 
	{72, 1.14, 529.69}, 
	{68, 1.87, 398.15}, 
	{67, 4.41, 5507.55}, 
	{59, 2.89, 5223.69}, 
	{56, 2.17, 155.42}, 
	{45, 0.40, 796.30}, 
	{36, 0.47, 775.52}, 
	{29, 2.65, 7.11}, 
	{2l, 5.34, 0.98}, 
	{19, 1.85, 5486.78}, 
	{19, 4.97, 213.30}, 
	{17, 2.99, 6275.96}, 
	{16, 0.03, 2544.31}, 
	{16, 1.43, 2146.17}, 
	{15, 1.21, 10977.08}, 
	{12, 2.83, 1748.02}, 
	{12, 3.26, 5088.63}, 
	{12, 5.27, 1194.45}, 
	{12, 2.08, 4694.00}, 
	{11, 0.77, 553.57}, 
	{10, 1.30, 6286.60}, 
	{10, 4.24, 1349.87}, 
	{9, 2.70, 242.73}, 
	{9, 5.64, 951.72}, 
	{8, 5.30, 2352.87}, 
	{6, 2.65, 9437.76}, 
	{6, 4.67, 4690.48}, 
};

/**
 * 20 terms of VSOP 82/87 Earth L2
 * */
STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_L2[] = {
	{52919, 0, 0}, 
	{8720, 1.0721, 6283.0758}, 
	{309, 0.867, 12566.152}, 
	{27, 0.05, 3.52}, 
	{16, 5.19, 26.30}, 
	{16, 3.68, 155.42}, 
	{10, 0.76, 18849.23}, 
	{9, 2.06, 77713.77}, 
	{7, 0.83, 775.52}, 
	{5, 4.66, 1577.34}, 
	{4, 1.03, 7.11}, 
	{4, 3.44, 5573.14}, 
	{3, 5.14, 796.30}, 
	{3, 6.05, 5507.55}, 
	{3, 1.19, 242.73}, 
	{3, 6.12, 529.69}, 
	{3, 0.31, 398.15}, 
	{3, 2.28, 553.57}, 
	{2, 4.38, 5223.69}, 
	{2, 3.75, 0.98}
};

/**
 * 7 terms of VSOP 82/87 Earth L3
 * */
STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_L3[] = {
	{289, 5.844, 6283.076}, 
	{35, 0, 0}, 
	{17, 5.49, 12566.15}, 
	{3, 5.20, 155.42}, 
	{1, 4.72, 3.52}, 
	{1, 5.30, 18849.23}, 
	{1, 5.97, 242.73}
};

/**
 * 3 terms of VSOP 82/87 Earth L4
 * */
STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_L4[] = {
	{114, 3.142, 0}, 
	{8, 4.13, 6283.08}, 
	{1, 3.84, 12566.15}
};

/**
 * 1 term of VSOP 82/87 Earth L5
 * */
STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_L5[] = {
	{1, 3.14, 0}
};

STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_B0[] = {
	{280, 3.199, 84334.662}, 
	{102, 5.422, 5507.553}, 
	{80, 3.88, 5223.69}, 
	{44, 3.70, 2352.87}, 
	{32, 4.00, 1577.34}
};

STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_B1[] = {
	{9, 3.90, 5507.55}, 
	{6, 1.73, 5223.69}
};

STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_R0[] = {
	{100013989, 0, 0}, 
	{1670700, 3.0984635, 6283.0758500}, 
	{13956, 3.05525, 12566.15170}, 
	{3084, 5.1985, 77713.7715}, 
	{1628, 1.1739, 5753.3849}, 
	{1576, 2.8469, 7860.4194}, 
	{925, 5.453, 11506.770}, 
	{542, 4.564, 3930.210}, 
	{472, 3.661, 5884.927}, 
	{346, 0.964, 5507.553}, 
	{329, 5.900, 5223.694}, // {329, 5.900, 5223,694} warning: excess elements in struct initializer
	{307, 0.299, 5573.143}, 
	{243, 4.273, 11790.629}, 
	{212, 5.847, 1577.344}, 
	{186, 5.022, 10977.079}, 
	{175, 3.012, 18849.228}, 
	{110, 5.055, 5486.778}, 
	{98, 0.89, 6069.78}, 
	{86, 5.69, 15720.84}, 
	{86, 1.27, 161000.69}, 
	{65, 0.27, 17260.15}, 
	{63, 0.92, 529.69}, 
	{57, 2.01, 83996.85}, 
	{56, 5.24, 71430.70}, 
	{49, 3.25, 2544.31}, 
	{47, 2.58, 775.52}, 
	{45, 5.54, 9437.76}, 
	{43, 6.01, 6275.96}, 
	{39, 5.36, 4694.00}, 
	{38, 2.39, 8827.39}, 
	{37, 0.83, 19651.05}, 
	{37, 4.90, 12139.55}, 
	{36, 1.67, 12036.46}, 
	{35, 1.84, 2942.46}, 
	{33, 0.24, 7084.90}, 
	{32, 0.18, 5088.63}, 
	{32, 1.78, 398.15}, 
	{28, 1.21, 6286.60}, 
	{28, 1.90, 6279.55}, 
	{26, 4.59, 10447.39}
};

STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_R1[] = {
	{103019, 1.107490, 6283.075850}, 
	{1721, 1.0644, 12566.1517}, 
	{702, 3.142, 0}, 
	{32, 1.02, 18849.23}, 
	{31, 2.84, 5507.55}, 
	{25, 1.32, 5223.69}, 
	{18, 1.42, 1577.34}, 
	{10, 5.91, 10977.08}, 
	{9, 1.42, 6275.96}, 
	{9, 0.27, 5486.78}
};

STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_R2[] = {
	{4359, 5.7846, 6283.0758}, 
	{124, 5.579, 12566.152}, 
	{12, 3.14, 0}, 
	{9, 3.63, 77713.77}, 
	{6, 1.87, 5573.14}, 
	{3, 5.47, 18849.23}
};

STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_R3[] = {
	{145, 4.273, 6283.076}, 
	{7, 3.92, 12566.15}
};

STERM_VSOP8287_PLANETS LIST_TERM_VSOP8287_EARTH_R4[] = {
	{4, 2.56, 6283.08}
};

/**
 * @param dJulianMillennium	Julian millenninum. 
 * */
double getVSOP8287PeriodicTerm(PTERM_VSOP8287_PLANETS terms, int count, double dJulianMillennium)
{
	int i;
	double result = 0.0;
	for(i=0; i < count; ++i) 
	{
		result += terms[i].A * cos(terms[i].B + terms[i].C * dJulianMillennium);
	}
	return result;
}

/**
 * geocentric longitude(earth-centre)
 * @param dJulianMillennium	Julian millennium.
 * @return 					The unit of result is degree. 
 * */
double getVSOP8287EarthLongitude(double dJulianMillennium) //getVSOP8287EarthLongitudePeriodicTermSum
{
	double paramsEarthL[COUNT_TERM_VSOP8287_EARTH_L];
	paramsEarthL[0] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_L0, COUNT_TERM_VSOP8287_EARTH_L0, dJulianMillennium);
	paramsEarthL[1] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_L1, COUNT_TERM_VSOP8287_EARTH_L1, dJulianMillennium);
	paramsEarthL[2] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_L2, COUNT_TERM_VSOP8287_EARTH_L2, dJulianMillennium);
	paramsEarthL[3] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_L3, COUNT_TERM_VSOP8287_EARTH_L3, dJulianMillennium);
	paramsEarthL[4] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_L4, COUNT_TERM_VSOP8287_EARTH_L4, dJulianMillennium);
	paramsEarthL[5] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_L5, COUNT_TERM_VSOP8287_EARTH_L5, dJulianMillennium);
	int i;
	double L = 0.0;
	for(i = COUNT_TERM_VSOP8287_EARTH_L-1; i >= 0; --i)
	{
		L += paramsEarthL[i];
		L *= dJulianMillennium;
	}
	L /= 100000000.0; // L is 10e-8 radian, that is, 10^8 
	return getDegreeIn360(getDegreeFromRadian(L) + 180.0);
}

/**
 * return degree; 
 * */
double getVSOP8287EarthLatitude(double dJulianMillennium)//getVSOP8287EarthLatitudePeriodicTermSum
{
	double paramsEarthB[COUNT_TERM_VSOP8287_EARTH_B];
	paramsEarthB[0] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_B0, COUNT_TERM_VSOP8287_EARTH_B0, dJulianMillennium);
	paramsEarthB[1] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_B1, COUNT_TERM_VSOP8287_EARTH_B1, dJulianMillennium);
	int i;
	double B = 0.0;
	for(i = COUNT_TERM_VSOP8287_EARTH_B-1; i >= 0; --i)
	{
		B += paramsEarthB[i];
		B *= dJulianMillennium;
	}
	B /= 100000000.0; // B is 10e-8 radian, that is, 10^8 
	return -getDegreeFromRadian(B);
}

/**
 * @return 	The unit of result is astronomical unit, approximately distance between sun and earth. 
 * */
double getVSOP8287EarthSunRadius(double dJulianMillennium)
{
	double paramsEarthR[COUNT_TERM_VSOP8287_EARTH_R];
	paramsEarthR[0] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_R0, COUNT_TERM_VSOP8287_EARTH_R0, dJulianMillennium);
	paramsEarthR[1] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_R1, COUNT_TERM_VSOP8287_EARTH_R1, dJulianMillennium);
	paramsEarthR[2] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_R2, COUNT_TERM_VSOP8287_EARTH_R2, dJulianMillennium);
	paramsEarthR[3] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_R3, COUNT_TERM_VSOP8287_EARTH_R3, dJulianMillennium);
	paramsEarthR[4] = getVSOP8287PeriodicTerm(LIST_TERM_VSOP8287_EARTH_R4, COUNT_TERM_VSOP8287_EARTH_R4, dJulianMillennium);
	int i;
	double R = 0.0;
	for(i = COUNT_TERM_VSOP8287_EARTH_R-1; i >= 0; --i)
	{
		R += paramsEarthR[i];
		R *= dJulianMillennium;
	}
	R /= 100000000.0;
	return R;
}

/**
 * @param	longitude	the return value of getVSOP8287EarthLongitudePeriodicTermSum
 * @param	latitude	the return value of getVSOP8287EarthLatitudePeriodicTermSum
 * @retrun	The unit of result is degree;
 * */
double getSunEclipticLongitudeECAdjustment(double dJulianCentury, double longitude, double latitude)
{
	double T = dJulianCentury;
	// L' = L - 1.397 * T - 0.00031*T^2, this formula returns degree. 
	double dbLdash = longitude - (1.397 + 0.00031 * T) * T;
	// dbLdash is required to convert into radian.
	dbLdash = getRadianFromDegree(dbLdash);
	// ¦¤L = -0.09033 + 0.03916 * ( cos(L') + sin(L') ) * tan(B) 
	// the unit of ¦¤L is degree second ". 
	return (-0.09033 + 0.03916 * (cos(dbLdash) + sin(dbLdash)) * tan(getRadianFromDegree(latitude))) / 3600.0;//1 degree = 60*60 degree second
}

/**
 * 
 * @param jd	Julian day. 
 * @return		The unit of result is degree. 
 * */
double getSunEclipticLongitudeECByJulianDay(double jd)
{
	double dJulianCentury = getJulianCenturyByJulianDay(jd);
	double dJulianMillennium = getJulianMillenniumByJulianDay(jd);
	double dLongitude = getVSOP8287EarthLongitude(dJulianMillennium);
	double dLatitude = getVSOP8287EarthLatitude(dJulianMillennium);
	double dLongitudeAdjustment = getSunEclipticLongitudeECAdjustment(dJulianCentury, dLongitude, dLatitude);
	double dLongitudeNutation = getIAU1980EarthLongitudeNutation(dJulianCentury);
	dLongitude += dLongitudeAdjustment;
	dLongitude += dLongitudeNutation;
	// (20 * PI) means 180/pi /3600, because unit of 20.4898 is degree second ", namely 20.4898"
	dLongitude -= 20.4898 / getVSOP8287EarthSunRadius(dJulianMillennium) / (20 * PI);
	return dLongitude;
}

double getSunEclipticLongitudeECBySecond(time_t timePoint)
{
	double dJulianDay = getJulianDayBySecond(timePoint);
	return getSunEclipticLongitudeECByJulianDay(dJulianDay);
}

double getSolarTermJulianDayNewtonByJulianDay(double jd)
{
	double JD0, JD1, stDegree, stDegreep;
//	JD1 = jd;
//	do
//	{
//		JD0 = JD1;
//		stDegree = GetSunEclipticLongitudeECDegree(JD0) - angle;
//		stDegreep = (GetSunEclipticLongitudeECDegree(JD0 + 0.000005)
//					  - GetSunEclipticLongitudeECDegree(JD0 - 0.000005)) / 0.00001;
//		JD1 = JD0 - stDegree / stDegreep;
//	} while((fabs(JD1 - JD0) > 0.0000001));
	return JD1;
}

double getSolarTermJulianDayNewtonBySecond(time_t timePoint)
{
	double dJulianDay = getJulianDayBySecond(timePoint);
	return getSolarTermJulianDayNewtonByJulianDay(dJulianDay);
}
