#include "global.h"


#include <stdarg.h>
#include <stdio.h>


static void report(const char *prefix, const char *err, va_list params)
{
	fputs(prefix, stderr);
	vfprintf(stderr, err, params);
	fputs("\n", stderr);
}


void die(const char *err, ...)
{
	va_list params;

	va_start(params, err);
	report("fatal: ", err, params);
	va_end(params);
	exit(1);
}
