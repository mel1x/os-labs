#include "getLinuxProcessorInfo.hpp"
#include <string>
#include <unistd.h>
#include <fstream>
#include <thread>

std::wstring getProcessorCount() {
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    if (count == -1) {
        return L"Unknown";
    }
    return std::to_wstring(count);
}

std::wstring getProcessorLoad() {
    std::ifstream file("/proc/loadavg");
    if (!file.is_open()) {
        return L"Error";
    }
    
    std::string load1, load5, load15;
    file >> load1 >> load5 >> load15;
    file.close();

    std::wstring result = L"1min: ";
    for (char c : load1) {
        result += static_cast<wchar_t>(c);
    }
    result += L" | 5min: ";
    for (char c : load5) {
        result += static_cast<wchar_t>(c);
    }
    result += L" | 15min: ";
    for (char c : load15) {
        result += static_cast<wchar_t>(c);
    }
    
    return result;
}


std::wstring getLinuxProcessorInfo() {
    std::wstring result = L"";

    result += L"Processors: " + getProcessorCount() + L"\nLoad AVG: " + getProcessorLoad();
    return result;
}