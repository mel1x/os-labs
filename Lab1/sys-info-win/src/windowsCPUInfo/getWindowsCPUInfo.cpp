#include "getWindowsCPUInfo.hpp"
#include <windows.h>
#include <string>

std::wstring getWindowsCPUInfo() {
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);

    std::wstring result = L"CPU Architecture: ";

    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            result += L"x64 (AMD or Intel)";
            break;
        case PROCESSOR_ARCHITECTURE_ARM64:
            result += L"ARM64";
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            result += L"x86 (32-bit)";
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            result += L"ARM";
            break;
        default:
            result += L"Unknown architecture";
            break;
    }

    result += L"\nCPU Cores: " + std::to_wstring(sysInfo.dwNumberOfProcessors);

    return result;
}