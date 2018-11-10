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

#ifndef CTRACE_CONFIG_H
#define CTRACE_CONFIG_H

#ifdef CWTRACE_CONFIG_H
#  error CTrace cannot be used with CWinTrace. Please choose one.
#endif

#define _CTR_STR(x) #x
#define CTR_STR _CTR_STR

#define CTR_VERSION_MAJOR 1
#define CTR_VERSION_MINOR 0
#define CTR_VERSION_PATCH 0
#define CTR_VERSION_STATE "stable"

#define CTR_VERSION_MAKE_STR(major, minor, patch) \
	CTR_STR(major) "." \
	CTR_STR(minor) "." \
	CTR_STR(patch) "-" \
	CTR_VERSION_STATE

#define CTR_VERSION_STR \
	CTR_VERSION_MAKE_STR(CTR_VERSION_MAJOR, CTR_VERSION_MINOR, CTR_VERSION_PATCH)

#define CTR_VERSION_MAKE(major, minor, patch) \
	((major) << 16) | ((minor) << 8) | (patch))

/*------------------------------------------------------------------------------
	Linker settings
------------------------------------------------------------------------------*/

#ifndef CTRAPI
#  define CTRAPI
#endif

#ifndef CTRCALL
#  define CTRCALL
#endif

/*------------------------------------------------------------------------------
	Other settings
------------------------------------------------------------------------------*/

#ifndef CTR_THIS_FILE
#  define CTR_THIS_FILE __FILE__
#endif

#ifndef CTR_THIS_LINE
#  define CTR_THIS_LINE __LINE__
#endif

#ifndef CTR_THIS_FUNC
#  define CTR_THIS_FUNC __FUNCTION__
#endif

#endif /* CTRACE_CONFIG_H */