#include<time.h>
#include <stdio.h>
#pragma warning( disable : 4996 ) //消除localtime报错
void timeToString(time_t t, char* pBuf)
{
	struct tm* timeinfo;
	timeinfo = localtime(&t);
		strftime(pBuf,20, "%Y-%m-%d %H:%M", timeinfo); //将time_t转换为字符串
}
time_t stringToTime(char *pTime) {
	struct tm tml;
	time_t timel;
	sscanf(pTime,"%d-%d-%d %d:%d",&tml.tm_year,&tml.tm_mon,&tml.tm_mday,&tml.tm_hour,&tml.tm_min);
	tml.tm_year -= 1900;
	tml.tm_mon -= 1;
	tml.tm_sec = 0;
	tml.tm_isdst = -1;
	timel = mktime(&tml);
	return timel;
}