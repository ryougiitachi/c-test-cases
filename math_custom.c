/**
 * math_custom.c
 *
 *  Created on: Apr 26, 2017
 *      Author: 
 */
#include <math.h>
#include "math_custom.h"

/**
 * degree mod 360.0
 * */
double getDegreeIn360(double degree)
{
	if(degree >= 0.0 && degree < 360.0)
	{
		return degree;
	}
	if(degree >= -360.0 && degree < 0.0)
	{
		return degree + 360.0;
	}
	double raw = degree >= 0 ? degree : -degree;
	double circle = floor(raw / 360.0);
	double result = raw - circle * 360.0;
	if(degree < 0)
	{
		result = 360.0 - result;
	}
	return result;
}

/**
 * 360 degree
 * */
double getDegreeFromRadian(double radian)
{
	return radian * 180.0 / PI;
}

/**
 * 2 pi radian
 * */
double getRadianFromDegree(double degree)
{
	return degree * PI / 180.0;
}
