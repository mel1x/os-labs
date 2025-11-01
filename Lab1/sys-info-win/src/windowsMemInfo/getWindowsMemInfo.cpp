#include "getWindowsMemInfo.hpp"
#include <windows.h>
#include <string>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

std::wstring getPageFile() {
    PERFORMANCE_INFORMATION perfInfo;
    perfInfo.cb = sizeof(PERFORMANCE_INFORMATION);
    std::wstring result = L"";

    if (GetPerformanceInfo(&perfInfo, sizeof(PERFORMANCE_INFORMATION))) {
        SIZE_T pageFileSizeMB = (perfInfo.CommitLimit * perfInfo.PageSize) / (1024 * 1024);
        result += L"Page File Size: " + std::to_wstring(pageFileSizeMB) + L" MB\n";
    } else {
        result += L"Page File Size: Failed to get performance info\n";
    }
    
    return result;
}

std::wstring getWindowsMemInfo() {
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);

    std::wstring result = L"";

    if (GlobalMemoryStatusEx(&memStatus)) {
        result += L"RAM: " 
            + std::to_wstring((memStatus.ullTotalPhys - memStatus.ullAvailPhys) / (1024 * 1024)) + L" MB / "
            + std::to_wstring(memStatus.ullTotalPhys / (1024 * 1024)) + L" MB\n";

        result += L"Virtual Memory: " 
            + std::to_wstring(memStatus.ullAvailVirtual / (1024 * 1024 * 1024)) + L" GB\n";

        double physUsedPercent = (1.0 - double(memStatus.ullAvailPhys) / memStatus.ullTotalPhys) * 100.0;
        result += L"Memory Load: " + std::to_wstring(static_cast<int>(physUsedPercent)) + L"%\n";

        result += getPageFile();

    } else {
        result += L"RAM: Failed to get memory status.\n";
        result += L"Virtual Memory: Failed to get memory status.\n";
        result += L"Memory Load: Failed to get memory status.\n";
        result += getPageFile();
    }

    return result;
}