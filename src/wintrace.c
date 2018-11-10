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

#ifndef _CRT_SECURE_NO_WARNINGS
#  define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _WIN32_LEAN_AND_MEAN
#  define _WIN32_LEAN_AND_MEAN
#endif

#include "cwintrace/wintrace.h"

#include <stdarg.h>
#include <string.h>
#include <io.h>		/* for _get_osfhandle() */

#include <windows.h>

typedef enum CB_COLOR {
	CB_BLACK = 0,
	CB_DARKBLUE = FOREGROUND_BLUE,
	CB_DARKGREEN = FOREGROUND_GREEN,
	CB_DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	CB_DARKRED = FOREGROUND_RED,
	CB_DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	CB_DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	CB_DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	CB_GRAY = FOREGROUND_INTENSITY,
	CB_BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	CB_GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	CB_CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	CB_RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
	CB_MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	CB_YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	CB_WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	CB_COUNT
} CB_COLOR;

#define CB_COLOR_MAKE(f, b) (((b) << 4) | (f))

/*------------------------------------------------------------------------------
	globals
------------------------------------------------------------------------------*/

static FILE* g_out;
static HANDLE g_hout;

#define MAX_STRLEN 256

#define FORMAT_HEADER  TEXT("== [MESSAGE] [%25s: LINE | %-20s] Begin Trace (%d/%.2d/%.2d - %.2d:%.2d:%.2d)\n\n")
#define FORMAT_MESSAGE TEXT("-- [%-7s] [%25s:%5d | %-20s] %s\n")
#define FORMAT_FOOTER  TEXT("\n== [MESSAGE] [%25s: LINE | %-20s] End Trace   (%d/%.2d/%.2d - %.2d:%.2d:%.2d)\n")

/*------------------------------------------------------------------------------
	local functions
------------------------------------------------------------------------------*/

static HANDLE get_handle(FILE* file)
{
	return (HANDLE)_get_osfhandle(_fileno(file));
}

static const TCHAR* get_filename(const TCHAR* file)
{
	return (_tcsrchr(file, TEXT('\\')) ? _tcsrchr(file, TEXT('\\')) + 1 : file);
}

static const TCHAR* ctr_wintostr(int ctr)
{
	switch (ctr) {
		case CWTR_DEBUG:
			return TEXT("Debug");
		case CWTR_INFO:
			return TEXT("Info");
		case CWTR_WARNING:
			return TEXT("Warning");
		case CWTR_ERROR:
			return TEXT("Error");
		case CWTR_FATAL:
			return TEXT("Fatal");
	}
	return TEXT("Unknown");
}

static void set_color(int ctr)
{
	switch (ctr) {
	case CWTR_DEBUG:
		SetConsoleTextAttribute(g_hout, CB_COLOR_MAKE(CB_GREEN, CB_BLACK));
		break;
	case CWTR_INFO:
		SetConsoleTextAttribute(g_hout, CB_COLOR_MAKE(CB_WHITE, CB_BLACK));
		break;
	case CWTR_WARNING:
		SetConsoleTextAttribute(g_hout, CB_COLOR_MAKE(CB_YELLOW, CB_BLACK));
		break;
	case CWTR_ERROR:
		SetConsoleTextAttribute(g_hout, CB_COLOR_MAKE(CB_MAGENTA, CB_BLACK));
		break;
	case CWTR_FATAL:
		SetConsoleTextAttribute(g_hout, CB_COLOR_MAKE(CB_RED, CB_BLACK));
		break;
	default:
		SetConsoleTextAttribute(g_hout, CB_COLOR_MAKE(CB_WHITE, CB_BLACK));
		break;
	}
}

static void print_sep(const TCHAR* format)
{
	set_color(CB_COLOR_MAKE(CB_WHITE, CB_BLACK));
	SYSTEMTIME t;
	GetLocalTime(&t);
	_ftprintf(g_out, format, TEXT("FILENAME"), TEXT("FUNCTION"),
			  t.wYear, t.wMonth, t.wDay,
			  t.wHour, t.wMinute, t.wSecond);
}

/*------------------------------------------------------------------------------
	library dunctions
------------------------------------------------------------------------------*/

int ctr_wintrace_begin(FILE* out)
{
	if (!out)
		return 0;
	g_out = out;
	g_hout = get_handle(out);
	print_sep(FORMAT_HEADER);
	return 1;
}

void ctr_wintrace_end(void)
{
	// TODO: free console
	print_sep(FORMAT_FOOTER);
	g_out = NULL;
}

void ctr_wintrace(const TCHAR* filename, int line, const TCHAR* func, int ctr, const TCHAR* format, ...)
{
	TCHAR buff[MAX_STRLEN];
	const TCHAR* trstr = ctr_wintostr(ctr);

	_stprintf(buff, FORMAT_MESSAGE, trstr, get_filename(filename), line, func, format);

	set_color(ctr);

	va_list vl;
	va_start(vl, format);
	_vftprintf(g_out, buff, vl);
	va_end(vl);
}

int ctr_get_winerr_str(TCHAR* buf, size_t size)
{
	return (int)FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buf,
		size,
		NULL
	);
}
