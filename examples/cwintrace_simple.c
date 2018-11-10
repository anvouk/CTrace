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

#pragma comment(lib, "CWinTrace.lib")
#include <cwintrace/wintrace.h>

int main(void)
{
	ctr_wintrace_begin(stdout);

	CWTRACE_ENTER_FN();
	CWTRACED(_T("Hello %s!"), _T("Debug"));
	CWTRACEI(_T("Hello %s!"), _T("Info"));
	CWTRACEW(_T("Hello %s!"), _T("Warning"));
	CWTRACEE(_T("Hello %s!"), _T("Error"));
	CWTRACEF(_T("Hello %s!"), _T("Fatal"));
	
	TCHAR winerr[128];
	if (!ctr_get_winerr_str(winerr, 128)) {
		CWTRACEW(_T("Couldn't get Windows error."));
	} else {
		CWTRACED(_T("Winerr: %s"), winerr);
	}

	CWTRACE_EXIT_FN();

	ctr_wintrace_end();
	getchar();
}