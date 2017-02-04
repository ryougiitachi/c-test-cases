/*
 * testing_cases.c
 *
 *  Created on: 2016��9��18��
 *      Author: 
 * It seems that this file can be compiled successfully without testing_cases.h except that NullPointException occurs.
 * But it is better to include "testing_cases.h".
 */
#include <stdio.h>
//#include <tre/tre.h>
#include <regex.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include "time_gregorian_calender.h"
#include "testing_cases.h"

/**
 * number is 1
 * It says multiple definition of `test_basic_data_types' if this method is implemented in header file.
 * */
int test_basic_data_types()
{
	puts("\n001 - This is test_basic_data_types: ");
	// long int is ok for integer, 12345678901234567890123456789012 is also ok but different from long int, strange.
	// but different from long int, strange. it says that integer constant is too large for its type.
	int i = 1;
	int arrayInt[8];
	//(int*) ptr1, ptr2;	//compile error
	float f = 1.1f;
	printf("The value of i is %d\n", i);
	printf("The value of i is %i\n", i);
	printf("The address of i is %p\n", i);			//Pointer address, also hex for address format 32bits or 64 bits.
	printf("Hex of float is %08X\n", f);
	printf("The value of float is %d\n", f);
	printf("The value of float is %09.3f\n", f);
	printf("The address of stdout is 0x%08x\n", stdout);
	printf("The address of stdout is 0X%p\n", stdout);			//Pointer address, p is used for expressing address value.
	
	memset((int*)arrayInt, 1, sizeof(arrayInt));
	for(i=0; i < 8; ++i ) {
		printf("%08X ", arrayInt[i]);
	}
	printf("\n");
	return 0;
}

/**
 * number is 2
 * */
int test_regex()
{
	puts("\n002 - This is test_regex");
	char *szRegex = "[-\\+]?\\d+(\\.\\d+)?";
	regex_t regex;
	regcomp(&regex, szRegex, 0);
	regfree(&regex);
	return 0;
}

/**
 * number is 3%a ���ڼ��ļ�д 
%A ���ڼ���ȫ�� 
%b �·ֵļ�д 
%B �·ݵ�ȫ�� 
%c ��׼�����ڵ�ʱ�䴮 
%C ��ݵĺ���λ���� 
%d ʮ���Ʊ�ʾ��ÿ�µĵڼ��� 
%D ��/��/�� 
%e �����ַ����У�ʮ���Ʊ�ʾ��ÿ�µĵڼ��� 
%F ��-��-�� 
%g ��ݵĺ���λ���֣�ʹ�û����ܵ��� 
%G ��֣�ʹ�û����ܵ��� 
%h ��д���·��� 
%H 24Сʱ�Ƶ�Сʱ 
%I 12Сʱ�Ƶ�Сʱ
%j ʮ���Ʊ�ʾ��ÿ��ĵڼ��� 
%m ʮ���Ʊ�ʾ���·� 
%M ʮʱ�Ʊ�ʾ�ķ����� 
%n ���з� 
%p ���ص�AM��PM�ĵȼ���ʾ 
%r 12Сʱ��ʱ�� 
%R ��ʾСʱ�ͷ��ӣ�hh:mm 
%S ʮ���Ƶ����� 
%t ˮƽ�Ʊ�� 
%T ��ʾʱ���룺hh:mm:ss 
%u ÿ�ܵĵڼ��죬����һΪ��һ�� ��ֵ��0��6������һΪ0��
%U ����ĵڼ��ܣ�����������Ϊ��һ�죨ֵ��0��53��
%V ÿ��ĵڼ��ܣ�ʹ�û����ܵ��� 
%w ʮ���Ʊ�ʾ�����ڼ���ֵ��0��6��������Ϊ0��
%W ÿ��ĵڼ��ܣ�������һ��Ϊ��һ�죨ֵ��0��53�� 
%x ��׼�����ڴ� 
%X ��׼��ʱ�䴮 
%y �������͵�ʮ������ݣ�ֵ��0��99��
%Y �����Ͳ��ֵ�ʮ����� 
%z��%Z ʱ�����ƣ�������ܵõ�ʱ�������򷵻ؿ��ַ���
%% �ٷֺ�
 * */
int test_time()
{
	puts("\n003 - This is test_time");
	printf("The size of struct tm is %" PRIu64 "\n", sizeof(struct tm));
	time_t time;
	struct tm *pTime;
	char szTime[64];
	memset(szTime, 0, sizeof(szTime));
	time = 1ll;
	pTime = gmtime(&time);
	strftime(szTime, sizeof(szTime)-1, "%Y-%m-%d %H:%M:%S", pTime);
	printf("Millisecond is %" PRId64 "\n", time);
	printf("struct tm value is %p\n", pTime);
	printf("date is %04d-%02d-%02d %02d:%02d:%02d\n", pTime->tm_year, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	printf("date is %s\n", szTime);
	
	time = 0ll;
	pTime = gmtime(&time);
	printf("Millisecond is %" PRId64 "\n", time);
	printf("struct tm value is %p\n", pTime);
	printf("date is %04d-%02d-%02d %02d:%02d:%02d\n", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, 
		pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	time = 0x790ffffffll;	//0x8000000000000000ll it is still available till 0x790ffffffll. 
	pTime = localtime(&time);
	printf("Millisecond is %" PRId64 "\n", time);
	printf("struct tm value is %p\n", pTime);
	if(pTime) {
		printf("date is %04d-%02d-%02d %02d:%02d:%02d\n", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, 
			pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	}
	time = -1ll;
	printf("Millisecond is %" PRId64 "\n", time);
	printf("struct tm value is %p\n", gmtime(&time));//return value will be null. therefore, time_t is not allowed negative ?
	
	struct tm tmTime;
	memset(&tmTime, 0, sizeof(struct tm));
	tmTime.tm_year = -20;
	printf("Millisecond is %" PRId64 "\n", mktime(&tmTime));//return -1, maybe not available. 
	return 0;
}

/**
 * number is 4
 * */
int test_macro()
{
	puts("\n004 - This is test_macro: ");
	
#if defined(__cplusplus)
	puts("There is __cplusplus");
#else
	puts("There is NOOOOO __cplusplus");
#endif
	
#if defined(__MINGW_EXTENSION)
	puts("There is __MINGW_EXTENSION");
#else
	puts("There is NOOOOO __MINGW_EXTENSION");
#endif
	
#if defined(__extension__)	//__extension__ seems not a macro. 
	puts("There is __extension__");
#else
	puts("There is NOOOOO __extension__");
#endif
	
#if defined(_TESTING_CASES_H_)
	puts("There is _TESTING_CASES_H_");
//	printf("There is _TESTING_CASES_H_, which is %d\n", (_TESTING_CASES_H_));	// error: expected expression before ')' token
#else
	puts("There is NOOOOO _TESTING_CASES_H_. ");
#endif
	
#if defined(_POSIX_)
	puts("There is _POSIX_");
#else
	puts("There is NOOOOO _POSIX_. ");
#endif
	
#if defined(_WIN64)	// 
	puts("There is _WIN64");
#else
	puts("There is NOOOOO _WIN64. ");
#endif
	
#if defined(_STDIO_DEFINED)	// 
	puts("There is _STDIO_DEFINED");
#else
	puts("There is NOOOOO _STDIO_DEFINED. ");
#endif
	
#if defined(_MSVCRT_)	// 
	puts("There is _MSVCRT_");
#else
	puts("There is NOOOOO _MSVCRT_. ");
#endif
	
#if defined(__GNUC__)	// 
	puts("There is __GNUC__");
#else
	puts("There is NOOOOO __GNUC__. ");
#endif
	
#if defined(__GNUG__)	// 
	puts("There is __GNUG__");
#else
	puts("There is NOOOOO __GNUG__. ");
#endif
	
#if defined(_STDSTREAM_DEFINED)	// 
	puts("There is _STDSTREAM_DEFINED");
#else
	puts("There is NOOOOO _STDSTREAM_DEFINED. ");
#endif
	
#if defined(RC_INVOKED)	// RC_INVOKED
	puts("There is RC_INVOKED");
#else
	puts("There is NOOOOO RC_INVOKED. ");
#endif
	
#if defined(__CRT__NO_INLINE)	// __CRT__NO_INLINE
	puts("There is __CRT__NO_INLINE");
#else
	puts("There is NOOOOO __CRT__NO_INLINE. ");
#endif
	
#if defined(_USE_32BIT_TIME_T)	// 
	puts("There is _USE_32BIT_TIME_T");
#else
	puts("There is NOOOOO _USE_32BIT_TIME_T. ");//
#endif
	
#if defined(_TESTING_CASES_H_)	// 
	printf("There is _TESTING_CASES_H_ " _TESTING_CASES_H_);
#else
	puts("There is NOOOOO _TESTING_CASES_H_. ");
#endif
	
	const int *ptrMacroNumber = (const int *)TESTING_MACRO_POINT;
	const char *szTestStrConn="a string connected ";
	printf("This is TESTING_MACRO_NUMBER %d\n", TESTING_MACRO_NUMBER);
//	printf("This is TESTING_MACRO_NUMBER " TESTING_MACRO_NUMBER);//Syntax error, maybe it is just OK for string macro. ���Ҳ�������д
	printf("This is TESTING_MACRO_STRING " TESTING_MACRO_STRING "\n");
//	printf("This is TESTING_MACRO_POINT " TESTING_MACRO_POINT);
	printf("This is TESTING_MACRO_POINT %d", ptrMacroNumber[0]);//no compile error but runtime error 
//	printf("This is szTestStrConn " szTestStrConn "\n");//Syntax error, maybe it is just OK for string macro?
	return 0;
}

/**
 * number is 5
 * */
int test_entry_args(int argc, char **argv)
{
	puts("\n005 - This is test_entry_args: ");
	int i;
	puts("The addresses of arguments are as follows: ");
	// %#p warning: '#' flag used with '%p' ms_printf format [-Wformat=]
	printf("The address of argv is 0X%pH\n", argv);
	for (i = 0; i < argc; ++i) 
	{
		printf("The address of argv[%d] is 0X%pH, and length is %I64d, and value is %s\n", i, argv[i], strlen(argv[i]), argv[i]);
	}
	return 0;
}

/**
 * number is 6
 * */
int test_std_stream()
{
	puts("\n006 - This is test_std_stream: ");
	printf("The address of stdin is %p.\n", stdin);
	printf("The address of stdout is %p.\n", stdout);
	printf("The address of stderr is %p.\n", stderr);
	printf("The stdin next position for file input is %s.\n", stdin->_ptr);
	printf("The stdin relative position for current buffer is %d.\n", stdin->_cnt);
	printf("The stdin initial position for file is %s.\n", stdin->_base);
	printf("The stdin flag is %08X.\n", stdin->_flag);
	printf("The stdin availability of file is %d.\n", stdin->_file);
	printf("The stdin status for checking buffer is %d.\n", stdin->_charbuf);
	printf("The stdin size of buffer is %d.\n", stdin->_bufsiz);
	printf("The stdin temporary file name is %s.\n", stdin->_tmpfname);
	printf("The stdout next position for file input is %s.\n", stdout->_ptr);
	printf("The stdout relative position for current buffer is %d.\n", stdout->_cnt);
//	printf("The stdout initial position for file is %s.\n", stdout->_base);
	printf("The stdout flag is %08X.\n", stdout->_flag);
	printf("The stdout availability of file is %d.\n", stdout->_file);
	printf("The stdout status for checking buffer is %d.\n", stdout->_charbuf);
	printf("The stdout size of buffer is %d.\n", stdout->_bufsiz);
	printf("The stdout temporary file name is %s.\n", stdout->_tmpfname);
	printf("The stderr next position for file input is %s.\n", stderr->_ptr);
	printf("The stderr relative position for current buffer is %d.\n", stderr->_cnt);
	printf("The stderr initial position for file is %s.\n", stderr->_base);
	printf("The stderr flag is %08X.\n", stderr->_flag);
	printf("The stderr availability of file is %d.\n", stderr->_file);
	printf("The stderr status for checking buffer is %d.\n", stderr->_charbuf);
	printf("The stderr size of buffer is %d.\n", stderr->_bufsiz);
	printf("The stderr temporary file name is %s.\n", stderr->_tmpfname);
	return 0;
}

/**
 * number is 7
 * */
int test_custom_calendar()
{
	struct tm tmGre[3];
	//warning: excess elements in array initializer
//	time_t lltime[2]={0, -1ll, -62162323149ll};//just warning, but don't use this.
	time_t lltime[3]={0, -12219292800ll, -62162323149ll};
	memcpy(tmGre, gmtime_by_gre(lltime), sizeof(struct tm));
	memcpy(tmGre+1, gmtime_by_gre(lltime+1), sizeof(struct tm));
	memcpy(tmGre+2, gmtime_by_gre(lltime+2), sizeof(struct tm));
	printf("The current time is %05d-%02d-%02d %02d:%02d:%02d. \n",
			tmGre[0].tm_year, tmGre[0].tm_mon, tmGre[0].tm_mday,
			tmGre[0].tm_hour, tmGre[0].tm_min, tmGre[0].tm_sec);
	printf("The current time is %05d-%02d-%02d %02d:%02d:%02d. \n",
			tmGre[1].tm_year, tmGre[1].tm_mon, tmGre[1].tm_mday,
			tmGre[1].tm_hour, tmGre[1].tm_min, tmGre[1].tm_sec);
	printf("The current time is %05d-%02d-%02d %02d:%02d:%02d. \n",
			tmGre[2].tm_year, tmGre[2].tm_mon, tmGre[2].tm_mday,
			tmGre[2].tm_hour, tmGre[2].tm_min, tmGre[2].tm_sec);
	return 0;
}
