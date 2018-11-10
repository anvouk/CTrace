/*
 * The MIT License
 *
 * Copyright 2018 Andrea Vouk.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ctrace/trace.h"

#include <time.h>
#include <stdarg.h>
#include <string.h>

/*------------------------------------------------------------------------------
	globals
------------------------------------------------------------------------------*/

static FILE* g_out = NULL;

#define MAX_LOGMESSAGE_LEN 256

#define FORMAT_HEADER  "== [MESSAGE] [%25s: LINE | %-20s] Begin Trace (%d/%.2d/%.2d - %.2d:%.2d:%.2d)\n\n"
#define FORMAT_MESSAGE "-- [%-7s] [%25s:%5d | %-20s] %s\n"
#define FORMAT_FOOTER  "\n== [MESSAGE] [%25s: LINE | %-20s] End Trace   (%d/%.2d/%.2d - %.2d:%.2d:%.2d)\n"

/*------------------------------------------------------------------------------
	local functions
------------------------------------------------------------------------------*/

static const char* get_filename(const char* file)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	return (strrchr(file, '\\') ? strrchr(file, '\\') + 1 : file);
#else
	return (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
#endif
}

static const char* ctr_tostr(int ctr)
{
	switch (ctr) {
		case CTR_DEBUG:
			return "Debug";
		case CTR_INFO:
			return "Info";
		case CTR_WARNING:
			return "Warning";
		case CTR_ERROR:
			return "Error";
		case CTR_FATAL:
			return "Fatal";
		default:
			return "Unknown";
	}
}

static void print_sep(const char* format)
{
	time_t raw = time(NULL);
	struct tm* t = localtime(&raw);
	fprintf(g_out, format, "FILENAME", "FUNCTION",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);
}

/*------------------------------------------------------------------------------
	library functions
------------------------------------------------------------------------------*/

int ctr_trace_begin(FILE* file)
{
	if (!file)
		return 0;
	g_out = file;
	print_sep(FORMAT_HEADER);
	return 1;
}

void ctr_trace_end(void)
{
	print_sep(FORMAT_FOOTER);
	g_out = NULL;
}

void ctr_trace(const char* filename, int line, const char* func, int ctr, const char* format, ...)
{
	char buff[MAX_LOGMESSAGE_LEN];
	const char* trstr = ctr_tostr(ctr);

	sprintf(buff, FORMAT_MESSAGE, trstr, get_filename(filename), line, func, format);

	va_list vl;
	va_start(vl, format);
	vfprintf(g_out, buff, vl);
	va_end(vl);
}
