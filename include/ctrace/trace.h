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

#ifndef CTRACE_TRACE_H
#define CTRACE_TRACE_H

#include "ctrace/config.h"
#include <stdio.h>

#define CTR_DEBUG	0	/**< Verbose. */
#define CTR_INFO	1	/**< Common log message. */
#define CTR_WARNING	2	/**< Warning log message. */
#define CTR_ERROR	3	/**< Current operation aborted. The program will not crash. */
#define CTR_FATAL	4	/**< Critical failure. Program crash imminent. */

#ifdef __cplusplus
extern "C" {
#endif
#if 0 /* auto-indent fix */
}
#endif

/**
 * Initialize CTrace library and set the log output.
 *
 * @param file  Either a file or a standard output.
 *
 * @return 1 on success, o otherwise.
 */
CTRAPI int CTRCALL ctr_trace_begin(FILE* file);

/**
 * Close the CTrace library and the output file.
 */
CTRAPI void CTRCALL ctr_trace_end(void);

CTRAPI void CTRCALL ctr_trace(
	const char* filename,
	int line,
	const char* func,
	int ctr,
	const char* format,
	...
);

#ifdef __cplusplus
}
#endif

#define CTRACE(ctr, format, ...) \
	ctr_trace(CTR_THIS_FILE, CTR_THIS_LINE, CTR_THIS_FUNC, ctr, format, __VA_ARGS__)

#define CTRACED(format, ...) \
	CTRACE(CTR_DEBUG, format, __VA_ARGS__)

#define CTRACEI(format, ...) \
	CTRACE(CTR_INFO, format, __VA_ARGS__)

#define CTRACEW(format, ...) \
	CTRACE(CTR_WARNING, format, __VA_ARGS__)

#define CTRACEE(format, ...) \
	CTRACE(CTR_ERROR, format, __VA_ARGS__)

#define CTRACEF(format, ...) \
	CTRACE(CTR_FATAL, format, __VA_ARGS__)

#define CTRACE_ENTER_FN() CTRACED("<< Entering \"" CTR_THIS_FUNC "\"")
#define CTRACE_EXIT_FN()  CTRACED(">> Exiting  \"" CTR_THIS_FUNC "\"")

#endif /* CTRACE_TRACE_H */