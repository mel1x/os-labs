#include "getLinuxDrives.hpp"
#include <sys/statvfs.h>
#include <fstream>
#include <string>

void addDiskInfo(std::wstring& output) {
    std::ifstream file("/proc/mounts");
    if (!file.is_open()) {
        output += L"Error reading mounts\n";
        return;
    }
    
    std::string device, mountPoint, fsType, options;
    int dump, pass;
    
    while (file >> device >> mountPoint >> fsType >> options >> dump >> pass) {
        // Пропускаем виртуальные файловые системы
        if (fsType == "proc" || fsType == "sysfs" || fsType == "devpts" || 
            fsType == "tmpfs" || fsType == "devtmpfs" || fsType == "cgroup" ||
            fsType == "cgroup2" || fsType == "pstore" || fsType == "bpf" ||
            fsType == "tracefs" || fsType == "debugfs" || fsType == "mqueue" ||
            fsType == "hugetlbfs" || fsType == "securityfs" || fsType == "configfs") {
            continue;
        }
        
        struct statvfs stat;
        if (statvfs(mountPoint.c_str(), &stat) != 0) {
            continue;
        }
        
        unsigned long long totalSize = (stat.f_blocks * stat.f_frsize) / (1024 * 1024 * 1024);
        unsigned long long freeSize = (stat.f_bavail * stat.f_frsize) / (1024 * 1024 * 1024);
        
        if (totalSize == 0) {
            continue;
        }
        
        output += L"  ";
        
        for (char c : mountPoint) {
            output += static_cast<wchar_t>(c);
        }
        
        int spaces = 10 - mountPoint.length();
        if (spaces < 1) spaces = 1;
        for (int i = 0; i < spaces; i++) {
            output += L' ';
        }
        
        for (char c : fsType) {
            output += static_cast<wchar_t>(c);
        }
        
        spaces = 9 - fsType.length();
        if (spaces < 1) spaces = 1;
        for (int i = 0; i < spaces; i++) {
            output += L' ';
        }
        
        output += std::to_wstring(freeSize) + L"GB free / " + 
                  std::to_wstring(totalSize) + L"GB total\n";
    }
    
    file.close();
}

std::wstring getLinuxDrives() {
    std::wstring result = L"Drives:\n";

    addDiskInfo(result);
    return result;
}