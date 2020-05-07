#include <stdio.h>
#include <time.h>
#include "util.h"

int utilStrNullOrEmpty(char* a)
{
	if (a == NULL) return 1;
	if (a[0] == '\0') return 1;

	return 0;
}

void utilGetTime(char* outTimestr)
{

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(outTimestr, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}