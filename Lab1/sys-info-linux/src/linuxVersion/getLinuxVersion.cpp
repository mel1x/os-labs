#include "getLinuxVersion.hpp"
#include <sys/utsname.h>
#include <fstream>
#include <string>

std::wstring stringToWstring(const std::string& str) {
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

std::wstring getLinuxVersion() {
    std::wifstream file("/etc/lsb-release");
    if (!file.is_open()) {
        return L"OS: Unknown OS\nKernel: Unknown Kernel";
    }

    std::wstring line;
    std::wstring osVersion = L"Unknown OS";
    while (std::getline(file, line)) {
        const std::wstring prefix = L"DISTRIB_DESCRIPTION=\"";
        if (line.compare(0, prefix.size(), prefix) == 0) {
            size_t start = prefix.size();
            size_t end = line.find(L'"', start);
            if (end != std::wstring::npos) {
                osVersion = line.substr(start, end - start);
            }
            break;
        }
    }

    struct utsname buffer;
    if (uname(&buffer) != 0) {
        return L"OS: " + osVersion + L"\nKernel: Unknown Kernel";
    }

    std::wstring kernelVersion = stringToWstring(buffer.release);
    std::wstring architecture = stringToWstring(buffer.machine);

    return L"OS: " + osVersion + L"\nKernel: Linux " + kernelVersion + L"\nArchitecture: " + architecture;
}