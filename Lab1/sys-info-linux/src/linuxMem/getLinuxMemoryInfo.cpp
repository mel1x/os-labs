#include "getLinuxMemoryInfo.hpp"
#include <fstream>
#include <string>

std::wstring getRAMInfo() {
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        return L"Error";
    }
    
    std::string line, word;
    long long memTotal = 0, memAvailable = 0;
    
    while (file >> word) {
        if (word == "MemTotal:") {
            file >> memTotal;
            file >> word; // пропускаем "kB"
        }
        else if (word == "MemAvailable:") {
            file >> memAvailable;
            file >> word; // пропускаем "kB"
            break;
        }
    }
    file.close();
    
    long long totalMB = memTotal / 1024;
    long long freeMB = memAvailable / 1024;
    
    std::wstring result = std::to_wstring(freeMB) + L"MB free / " + 
                          std::to_wstring(totalMB) + L"MB total";
    return result;
}

std::wstring getSwapInfo() {
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        return L"Error";
    }
    
    std::string word;
    long long swapTotal = 0, swapFree = 0;
    
    while (file >> word) {
        if (word == "SwapTotal:") {
            file >> swapTotal;
            file >> word; // пропускаем "kB"
        }
        else if (word == "SwapFree:") {
            file >> swapFree;
            file >> word; // пропускаем "kB"
            break;
        }
    }
    file.close();
    
    long long totalMB = swapTotal / 1024;
    long long freeMB = swapFree / 1024;
    
    std::wstring result = std::to_wstring(freeMB) + L"MB free / " + 
                          std::to_wstring(totalMB) + L"MB total";
    return result;
}

std::wstring getVirtualMemoryInfo() {
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        return L"Error";
    }
    
    std::string word;
    long long virtualmemTotal = 0;
    
    while (file >> word) {
        if (word == "VmallocTotal:") {
            file >> virtualmemTotal;
            file >> word;
            break;
        }
    }
    file.close();
    
    std::wstring result = std::to_wstring(virtualmemTotal / 1024) + L" MB";
    return result;
}

std::wstring getLinuxMemoryInfo() {
    std::wstring result = L"";

    result += L"RAM: " + getRAMInfo() + L"\nSwap: " + getSwapInfo() + L"\nVirtual Memory: " + getVirtualMemoryInfo();
    return result; 
}