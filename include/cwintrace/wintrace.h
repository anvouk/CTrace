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

/**
 * @file
 */

#ifndef CWINTRACE_WINTRACE_H
#define CWINTRACE_WINTRACE_H

#pragma once

#include "cwintrace/config.h"
#include <stdio.h>
#include <tchar.h>

#define CWTR_DEBUG	 0	/**< Verbose. */
#define CWTR_INFO	 1	/**< Common log message. */
#define CWTR_WARNING 2	/**< Warning log message. */
#define CWTR_ERROR	 3	/**< Current operation aborted. The program will not crash. */
#define CWTR_FATAL	 4	/**< Critical failure. Program crash imminent. */

#ifdef __cplusplus
extern "C" {
#endif
#if 0 /* auto-indent fix */
}
#endif

/**
 * Initialize CWinTrace library and set the log output.
 *
 * @param file  Either a file or a standard output.
 *
 * @return 1 on success, o otherwise.
 */
CWTRAPI int CWTRCALL ctr_wintrace_begin(FILE* file);

/**
 * Close the CTrace library and the output file.
 */
CWTRAPI void CWTRCALL ctr_wintrace_end(void);

CWTRAPI void CWTRCALL ctr_wintrace(
	const TCHAR* filename,
	int line,
	const TCHAR* func,
	int ctr,
	const TCHAR* format,
	...
);

/**
 * Get a human-friendly windows error message.
 *
 * @param buf   The out string buffer.
 * @param size  The out buffer's size.
 *
 * @return 1 on success, 0 otherwise.
 */
CWTRAPI int CWTRCALL ctr_get_winerr_str(TCHAR* buf, size_t size);

#ifdef __cplusplus
}
#endif

#define CWTRACE(ctr, wformat, ...) \
	ctr_wintrace(_T(CWTR_THIS_FILE), CWTR_THIS_LINE, _T(CWTR_THIS_FUNC), ctr, wformat, __VA_ARGS__)

#define CWTRACED(wformat, ...) \
	CWTRACE(CWTR_DEBUG, wformat, __VA_ARGS__)

#define CWTRACEI(wformat, ...) \
	CWTRACE(CWTR_INFO, wformat, __VA_ARGS__)

#define CWTRACEW(wformat, ...) \
	CWTRACE(CWTR_WARNING, wformat, __VA_ARGS__)

#define CWTRACEE(wformat, ...) \
	CWTRACE(CWTR_ERROR, wformat, __VA_ARGS__)

#define CWTRACEF(wformat, ...) \
	CWTRACE(CWTR_FATAL, wformat, __VA_ARGS__)

#define CWTRACE_ENTER_FN() CWTRACED(_T("<< Entering \"") _T(CWTR_THIS_FUNC) _T("\""))
#define CWTRACE_EXIT_FN()  CWTRACED(_T(">> Exiting  \"") _T(CWTR_THIS_FUNC) _T("\""))

#endif /* CWINTRACE_WINTRACE_H */
