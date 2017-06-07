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

#define REGEX_ARGUMENT_OPTION "'?(-\\w)'?"
#define REGEX_ARGUMENT_PARAMETER "'?((\\d+)(\\,\\-?\\w+)*)'?"

/**
 * format: -f 1[,arg1,arg2...] [-f 1[,arg1,arg2...]...]
 * */
int manage_testing_cases(int argc, char **argv)
{
	if(argc <= 1 || argv == NULL)
	{
		puts("No executing code");
		return -1;
	}
	int status;
	regex_t regexOption;
	regex_t regexParam;
	regmatch_t regmatchOption[8];
	regmatch_t regmatchParam[8];
	
	int regCflags = REG_EXTENDED;	// REG_EXTENDED | REG_ICASE | REG_NEWLINE | REG_NOSUB
	int regEflags = 0;				// REG_NOTBOL | REG_NOTEOL
	char szExecCode[32];
	char szErrMsg[128];

	char *szParameters;
	char **arrayParam;
	char *pTempParameter;
	int lengthParameters;
	int capacityParameters;

	status = regcomp (&regexOption, REGEX_ARGUMENT_OPTION, regCflags);
	if (status) {
		regerror (status, &regexOption, szErrMsg, sizeof(szErrMsg)-1);
		printf("Error occurs when parsing REGEX_ARGUMENT_OPTION regular expression: %s \n", szErrMsg);
		return -2;
	}
	status = regcomp (&regexParam, REGEX_ARGUMENT_PARAMETER, regCflags);
	if (status) {
		regerror (status, &regexParam, szErrMsg, sizeof(szErrMsg)-1);
		printf("Error occurs when parsing REGEX_ARGUMENT_PARAMETER regular expression: %s \n", szErrMsg);
		return -2;
	}

	int iExecCode;
	puts("Arguments with '' are as follows: ");
	for (int i = 1; i < argc; ++i)
	{
		printf("%s ", argv[i]);
		if(argv[i][0] == '\'')
		{
			printf("yes ");
		}
		else
		{
			printf("no ");
		}
		if(argv[i][strlen(argv[i]) - 1] == '\'')
		{
			printf("yes ");
		}
		else
		{
			printf("no ");
		}
		printf("\n");
	}
	puts("\n");

	lengthParameters = 512;
	capacityParameters = 16;
	szParameters = (char*)malloc(lengthParameters);//initialise the content of parameters.
	arrayParam = (char**)malloc(capacityParameters * sizeof(char*));//initilise the array of parameters.
	memset(szParameters, 0, lengthParameters * sizeof(char));
	memset(arrayParam, 0, capacityParameters * sizeof(char*));

	for (int i = 1; i < argc; ++i)
	{
		memset(regmatchOption, 0, sizeof(regmatch_t) * 8);		// the 3rd parameter is the size of specific memory, but not the number of elements.
		memset(regmatchParam, 0, sizeof(regmatch_t) * 8);		// the 3rd parameter is the size of specific memory, but not the number of elements.
		//Firstly, handle the option.
		//check whether current argument is option like '-f'
		status = regexec (&regexOption, argv[i], 8, regmatchOption, regEflags);		//REG_NOTBOL | REG_NOTEOL
		if (status != REG_NOMATCH)
		{
			if(i + 1 < argc)
			{
				//Secondly, handle the parameter.
				status = regexec (&regexParam, argv[i + 1], 8, regmatchParam, regEflags);	//won't record all of * item.
				if (status == REG_NOMATCH) {
					printf("%s is not legal parameter. \n", argv[i]);
					continue;//jump out of current loop.
				}
				if(lengthParameters < strlen(argv[i + 1]) + 1){//realloc the content of parameters.
					lengthParameters = strlen(argv[i + 1]) + 1;
					szParameters = (char*)realloc(szParameters, lengthParameters);
				}
				memset(szParameters, 0, lengthParameters * sizeof(char));
				memcpy(szParameters, argv[i + 1] + regmatchParam[1].rm_so, regmatchParam[1].rm_eo - regmatchParam[1].rm_so);
				memset(szExecCode, 0, sizeof(szExecCode));
		//		strncpy(szExecCode, argv[i] + regmatch[1].rm_so, regmatch[1].rm_eo - regmatch[1].rm_so);	//for unknown reason, end character is non-zero
				memcpy(szExecCode, argv[i + 1] + regmatchParam[2].rm_so, regmatchParam[2].rm_eo - regmatchParam[2].rm_so);
		//		for(int j=0; j < 8; ++j){printf("'%c' %d ", szExecCode[j], szExecCode[j]);}printf("\n");
		//		printf("%05d - start is %d, end is %d. string is %s\n", i, regmatch[1].rm_so, regmatch[1].rm_eo, szExecCode);
				iExecCode = atoi(szExecCode);		//if parameter value is alphabetics, such as abc, atoi will return 0.
				strtok(szParameters, ",");//skip the first parameter.
				int countParams = 0;
				for(countParams = 0; (pTempParameter = strtok(NULL, ",")); ++countParams)
				{
					if(countParams >= capacityParameters)
					{
						capacityParameters += 8;
						arrayParam = (char**)realloc(arrayParam, capacityParameters * sizeof(char*));
					}
					arrayParam[countParams] = pTempParameter;
				}

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
					test_custom_calendar(countParams, arrayParam);
					break;
				case 8:
					test_absolute_from_gregorian();
					break;
				case 9:
					test_math_formula(countParams, arrayParam);
					break;
				default:
					puts("There is no valid parameter. ");
					break;
				}
				++i;
			}

		}
		else
		{
			printf("%s is not legal option. \n", argv[i]);
		}
	}

	free(szParameters);
	free(arrayParam);
	szParameters = NULL;
	arrayParam = NULL;
	regfree(&regexOption);
	regfree(&regexParam);
	return 0;
}
