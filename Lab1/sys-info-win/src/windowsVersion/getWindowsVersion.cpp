#include "getWindowsVersion.hpp"
#include <windows.h>
#include <string>

std::wstring GetDisplayVersion() {
    HKEY hKey;
    wchar_t displayVersion[256] = L"";
    DWORD size = sizeof(displayVersion);

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                      0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegGetValueW(hKey, nullptr, L"DisplayVersion", RRF_RT_REG_SZ, nullptr, displayVersion, &size);
        RegCloseKey(hKey);
    }
    return std::wstring(displayVersion);
}

std::wstring getWindowsVersion() {
    HMODULE handleModule = GetModuleHandleW(L"ntdll.dll");

    if (handleModule) {
        RtlGetVersionPtr funcPointer = (RtlGetVersionPtr)GetProcAddress(handleModule, "RtlGetVersion");

        if (funcPointer != nullptr) {
            RTL_OSVERSIONINFOW OsVersionInfo = { 0 };
            OsVersionInfo.dwOSVersionInfoSize = sizeof(OsVersionInfo);

            if (STATUS_SUCCESS == funcPointer(&OsVersionInfo)) {
                DWORD BuildNumber = OsVersionInfo.dwBuildNumber;
                std::wstring result;

                if (BuildNumber >= 22000) {
                    result = L"OS: Windows " 
                        + std::to_wstring(11) 
                        + (OsVersionInfo.dwMinorVersion != 0? L"." + std::to_wstring(OsVersionInfo.dwMinorVersion) : L"") + L" "
                        + GetDisplayVersion()
                        + L"(Build " + std::to_wstring(BuildNumber) + L")";
                } else {
                    result = L"OS: Windows " 
                        + std::to_wstring(OsVersionInfo.dwMajorVersion) + L"." 
                        + (OsVersionInfo.dwMinorVersion != 0? std::to_wstring(OsVersionInfo.dwMinorVersion) : L"") + L" "
                        + GetDisplayVersion() 
                        + L"(Build " + std::to_wstring(BuildNumber) + L")";
                }

                return result;
            }
        }
    }

    std::wstring result = L"Failed to get Windows version.";
    return result;
}