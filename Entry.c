/*
 * Entry.c
 *
 *  Created on: 2014Äê8ÔÂ31ÈÕ
 *      Author: 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manage_testing_cases.h"


int main(int argc, char * args[])
{
	manage_testing_cases(argc, args);

	int i;

//	iReturn=fork();
//	printf("create result %d \n", iReturn);

	FILE *file=fopen(".", "r");
	if(file != NULL)
	{
		puts("The current dir");
	}
	else
	{
		puts("It isn't right !");
	}
	fclose(file);
	file = NULL;

	time_t time;time = 0l;

	return 0;
}
