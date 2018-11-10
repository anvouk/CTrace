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

#ifndef CWTRACE_CONFIG_H
#define CWTRACE_CONFIG_H

#ifdef CTRACE_CONFIG_H
#  error CWinTrace cannot be used with CTrace. Please choose one.
#endif

#ifndef _WIN32
#  error CWinTrace can only be used on windows. Use CTrace instead.
#endif

#define _CWTR_STR(x) #x
#define CWTR_STR _CWTR_STR

#define CWTR_VERSION_MAJOR 1
#define CWTR_VERSION_MINOR 0
#define CWTR_VERSION_PATCH 0
#define CWTR_VERSION_STATE "stable"

#define CWTR_VERSION_MAKE_STR(major, minor, patch) \
	CWTR_STR(major) "." \
	CWTR_STR(minor) "." \
	CWTR_STR(patch) "-" \
	CWTR_VERSION_STATE

#define CWTR_VERSION_STR \
	CWTR_VERSION_MAKE_STR(CWTR_VERSION_MAJOR, CWTR_VERSION_MINOR, CWTR_VERSION_PATCH)

#define CWTR_VERSION_MAKE(major, minor, patch) \
	((major) << 16) | ((minor) << 8) | (patch))

 /*------------------------------------------------------------------------------
	 Linker settings
 ------------------------------------------------------------------------------*/

#ifndef CWTRAPI
#  define CWTRAPI
#endif

#ifndef CWTRCALL
#  define CWTRCALL
#endif

 /*------------------------------------------------------------------------------
	 Other settings
 ------------------------------------------------------------------------------*/

#ifndef CWTR_THIS_FILE
#  define CWTR_THIS_FILE __FILE__
#endif

#ifndef CWTR_THIS_LINE
#  define CWTR_THIS_LINE __LINE__
#endif

#ifndef CWTR_THIS_FUNC
#  define CWTR_THIS_FUNC __FUNCTION__
#endif

#endif /* CWTRACE_CONFIG_H */