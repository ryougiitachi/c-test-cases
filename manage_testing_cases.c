/*
 * manage_testing_cases.c
 *
 *  Created on: 2016Äê9ÔÂ18ÈÕ
 *      Author: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "manage_testing_cases.h"
#include "testing_cases.h"

int manage_testing_cases(int argc, char **argv)
{
	if(argc <= 1 || argv == NULL)
	{
		puts("No executing code");
		return -1;
	}
	int status;
	regex_t regex;
	regmatch_t regmatch[8];
	
	int regflags = REG_EXTENDED;	// REG_EXTENDED | REG_ICASE | REG_NEWLINE | REG_NOSUB
	char *szParamPattern="'?(\\d+)'?";
	char szExecCode[32];
	char szErrMsg[128];
	status = regcomp (&regex, szParamPattern, regflags);
	if (status) {
		regerror (status, &regex, szErrMsg, sizeof(szErrMsg)-1);
		printf("Error occurs when parsing regular expression: %s \n", szErrMsg);
		return -2;
	}

	int iExecCode;
	for (int i = 1; i < argc; ++i)
	{
		status = regexec (&regex, argv[i], 8, regmatch, 0);		//REG_NOTBOL | REG_NOTEOL
		if (status == REG_NOMATCH) {
			printf("%s is not legal argument. \n", argv[i]);
			continue;
		}
		memset(szExecCode, 0, sizeof(szExecCode));
//		strncpy(szExecCode, argv[i] + regmatch[1].rm_so, regmatch[1].rm_eo - regmatch[1].rm_so);	//for unknown reason, end character is non-zero
		memcpy(szExecCode, argv[i] + regmatch[1].rm_so, regmatch[1].rm_eo - regmatch[1].rm_so);
//		for(int j=0; j < 8; ++j){printf("'%c' %d ", szExecCode[j], szExecCode[j]);}printf("\n");
//		printf("%05d - start is %d, end is %d. string is %s\n", i, regmatch[1].rm_so, regmatch[1].rm_eo, szExecCode);
		iExecCode = atoi(szExecCode);		//if parameter value is alphabetics, such as abc, atoi will return 0. 
		switch (iExecCode)
		{
		case 0:
			puts("This is parameter 0. ");
			break;
		case 1:
			test_basic_data_types();
			break;
		case 2:
			test_regex();
			break;
		case 3:
			test_time();
			break;
		case 4:
			test_macro();
			break;
		case 5:
			test_entry_args(argc, argv);
			break;
		case 6:
			test_std_stream();
			break;
		case 7:
			test_custom_calendar();
			break;
		default:
			puts("There is no valid parameter. ");
			break;
		}
		memset(regmatch, 0, sizeof(regmatch_t) * 8);		// the 3rd parameter is the size of specific memory, but not the number of elements.
	}
	regfree(&regex);
	return 0;
}
