#pragma once
#include <windows.h>
#include <string>

typedef LONG NTSTATUS, *PNTSTATUS;
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

std::wstring GetDisplayVersion();
std::wstring getWindowsVersion();

#include "getWindowsVersion.cpp"