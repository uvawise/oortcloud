#pragma once
//-------------------------------------------------------------------------------------------------
// <copyright file="conutil.h" company="Microsoft">
//    Copyright (c) Microsoft Corporation.  All rights reserved.
//
//    The use and distribution terms for this software are covered by the
//    Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
//    which can be found in the file CPL.TXT at the root of this distribution.
//    By using this software in any fashion, you are agreeing to be bound by
//    the terms of this license.
//
//    You must not remove this notice, or any other, from this software.
// </copyright>
// 
// <summary>
//    Console helper functions.
// </summary>
//-------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#define ConsoleExitOnFailure(x, c, f) if (FAILED(x)) { ConsoleWriteError(x, c, f); ExitTrace(x, f); goto LExit; }
#define ConsoleExitOnFailure1(x, c, f, s) if (FAILED(x)) { ConsoleWriteError(x, c, f, s, NULL); ExitTrace1(x, f, s); goto LExit; }
#define ConsoleExitOnFailure2(x, c, f, s, t) if (FAILED(x)) { ConsoleWriteError(x, c, f, s, t); ExitTrace2(x, f, s, t); goto LExit; }
#define ConsoleExitOnFailure3(x, c, f, s, t, u) if (FAILED(x)) { ConsoleWriteError(x, c, f, s, t, u); ExitTrace3(x, f, s, t, u); goto LExit; }

#define ConsoleExitOnLastError(x, c, f) { x = ::GetLastError(); x = HRESULT_FROM_WIN32(x); if (FAILED(x)) { ConsoleWriteError(x, c, f); ExitTrace(x, f); goto LExit; } }
#define ConsoleExitOnLastError1(x, c, f, s) { x = ::GetLastError(); x = HRESULT_FROM_WIN32(x); if (FAILED(x)) { ConsoleWriteError(x, c, f, s, NULL); ExitTrace1(x, f, s); goto LExit; } }
#define ConsoleExitOnLastError2(x, c, f, s, t) { x = ::GetLastError(); x = HRESULT_FROM_WIN32(x); if (FAILED(x)) { ConsoleWriteError(x, c, f, s, t); ExitTrace2(x, f, s, t); goto LExit; } }
#define ConsoleExitOnLastError3(x, c, f, s, t, u) { x = ::GetLastError(); x = HRESULT_FROM_WIN32(x); if (FAILED(x)) { ConsoleWriteError(x, c, f, s, t, u); ExitTrace3(x, f, s, t, u); goto LExit; } }

#define ConsoleExitOnNull(p, x, e, c, f) if (NULL == p) { x = e; ConsoleWriteError(x, c, f); ExitTrace(x, f); goto LExit; }
#define ConsoleExitOnNull1(p, x, e, c, f, s) if (NULL == p) { x = e; ConsoleWriteError(x, c, f, s, NULL); ExitTrace1(x, f, s); goto LExit; }
#define ConsoleExitOnNull2(p, x, e, c, f, s, t) if (NULL == p) { x = e; ConsoleWriteError(x, c, f, s, t); ExitTrace2(x, f, s, t); goto LExit; }
#define ConsoleExitOnNull3(p, x, e, c, f, s, t, u) if (NULL == p) { x = e; ConsoleWriteError(x, c, f, s, t, u); ExitTrace2(x, f, s, t, u); goto LExit; }


// the following macros need to go away
#define ConsoleTrace(l, f) { ConsoleWriteLine(CONSOLE_COLOR_NORMAL, f); Trace(l, f); }
#define ConsoleTrace1(l, f, s) { ConsoleWriteLine(CONSOLE_COLOR_NORMAL, f, s); Trace1(l, f, s); }
#define ConsoleTrace2(l, f, s, t) { ConsoleWriteLine(CONSOLE_COLOR_NORMAL, f, s, t); Trace2(l, f, s, t); }
#define ConsoleTrace3(l, f, s, t, u) { ConsoleWriteLine(CONSOLE_COLOR_NORMAL, f, s, t, u); Trace3(l, f, s, t, u); }

#define ConsoleWarning(f) { ConsoleWriteLine(CONSOLE_COLOR_YELLOW, f); Trace(REPORT_STANDARD, f); }
#define ConsoleWarning1(f, s) { ConsoleWriteLine(CONSOLE_COLOR_YELLOW, f, s); Trace1(REPORT_STANDARD, f, s); }
#define ConsoleWarning2(f, s, t) { ConsoleWriteLine(CONSOLE_COLOR_YELLOW, f, s, t); Trace2(REPORT_STANDARD, f, s, t); }
#define ConsoleWarning3(f, s, t, u) { ConsoleWriteLine(CONSOLE_COLOR_YELLOW, f, s, t, u); Trace3(REPORT_STANDARD, f, s, t, u); }

#define ConsoleError(x, f) { ConsoleWriteError(x, CONSOLE_COLOR_RED, f); TraceError(x, f); }
#define ConsoleError1(x, f, s) { ConsoleWriteError(x, CONSOLE_COLOR_RED, f, s); TraceError1(x, f, s); }
#define ConsoleError2(x, f, s, t) { ConsoleWriteError(x, CONSOLE_COLOR_RED, f, s, t); TraceError2(x, f, s, t); }
#define ConsoleError3(x, f, s, t, u) { ConsoleWriteError(x, CONSOLE_COLOR_RED, f, s, t, u); TraceError3(x, f, s, t, u); }


// enums
enum CONSOLE_COLOR { CONSOLE_COLOR_NORMAL, CONSOLE_COLOR_RED, CONSOLE_COLOR_YELLOW, CONSOLE_COLOR_GREEN };

// structs

// functions
HRESULT ConsoleInitialize();
void ConsoleUninitialize();

void ConsoleGreen();
void ConsoleRed();
void ConsoleYellow();
void ConsoleNormal();

HRESULT ConsoleWrite(
	CONSOLE_COLOR cc,
	__in_z __format_string LPCSTR szFormat,
	...
	);
HRESULT ConsoleWriteLine(
	CONSOLE_COLOR cc,
	__in_z __format_string LPCSTR szFormat,
	...
	);
HRESULT ConsoleWriteError(
	HRESULT hrError,
	CONSOLE_COLOR cc,
	__in_z __format_string LPCSTR szFormat,
	...
	);

HRESULT ConsoleReadW(
	__deref_out_z LPWSTR* ppwzBuffer
	);

HRESULT ConsoleReadStringA(
	__deref_out_ecount_part(cchCharBuffer,*pcchNumCharReturn) LPSTR* szCharBuffer,
	CONST DWORD cchCharBuffer,
	__out DWORD* pcchNumCharReturn
	);
HRESULT ConsoleReadStringW(
	__deref_out_ecount_part(cchCharBuffer,*pcchNumCharReturn) LPWSTR* szCharBuffer,
	CONST DWORD cchCharBuffer,
	__out DWORD* pcchNumCharReturn
	);

HRESULT ConsoleReadNonBlockingW(
	__deref_out_ecount_opt(*pcchSize) LPWSTR* ppwzBuffer,
	__out DWORD* pcchSize,
	BOOL fReadLine
	);

HRESULT ConsoleSetReadHidden(void);
HRESULT ConsoleSetReadNormal(void);

#ifdef __cplusplus
}
#endif

