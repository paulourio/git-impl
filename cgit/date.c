#include <ctype.h>
#include <stdio.h>
#include <time.h>


static time_t my_mktime(struct tm *tm)
{
	static const int mdays[] = {
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	};
	int year = tm->tm_year - 70;
	int month = tm->tm_mon;
	int day = tm->tm_mday;

	if (year < 0 || year > 129) /* algo only works for 1970-2099 */
		return -1;
	if (month < 0 || month > 11) /* array bounds */
		return -1;
	if (month < 2 || (year + 2) % 4)
		day--;
	return (year * 365
		+ (year + 1) / 4
		+ mdays[month] + day) * 24*60*60UL
		+ tm->tm_hour * 60*60
		+ tm->tm_min * 60
		+ tm->tm_sec;
}


void datestamp(char *buf, int bufsize)
{
	time_t now;
	int offset;

	time(&now);

	offset = my_mktime(localtime(&now)) - now;
	offset /= 60;

	snprintf(buf, bufsize, "%lu %+05d", now, offset/60*100 + offset%60);
}
