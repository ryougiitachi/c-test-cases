/*
 * testing_cases.h
 *
 *  Created on: 2016Äê9ÔÂ18ÈÕ
 *      Author: 
 */
#ifndef _TESTING_CASES_H_
#define _TESTING_CASES_H_

#include <stdio.h>

#define TESTING_MACRO_NUMBER 128
#define TESTING_MACRO_STRING "successful macro string"
#define TESTING_MACRO_POINT 0X0000000012345678ULL

/**
 * number is 1
 * It will prompt multiple definition of `test_basic_data_types' ?
 * */
/***
int test_basic_data_types()
{
	float f = 1.1f;
	printf("Hex of float is %08X\n", f);
	printf("The value of float is %d\n", f);
	printf("The value of float is %09.3f\n", f);
	return 0;
}
**/
int test_basic_data_types();

/**
 * number is 2
 * */
int test_regex();

/**
 * number is 3
 * */
int test_time();

/**
 * number is 4
 * */
int test_macro();

/**
 * number is 5
 * */
int test_entry_args(int argc, char **argv);

/**
 * number is 6
 * */
int test_std_stream();

/**
 * number is 7
 * */
int test_custom_calendar(int argc, const char **argv);

/**
 * number is 8
 * */
int test_absolute_from_gregorian();

/**
 * number is 9
 * */
int test_math_formula(int argc, const char **argv);

#endif
