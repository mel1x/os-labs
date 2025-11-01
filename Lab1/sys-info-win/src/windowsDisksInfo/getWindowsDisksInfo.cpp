#include "getWindowsDisksInfo.hpp"
#include <windows.h>
#include <string>

std::wstring getWindowsDisksInfo() {
    wchar_t drives[MAX_PATH] = {0};
    std::wstring result = L"Drives:\n";

    if (GetLogicalDriveStringsW(MAX_PATH, drives)) {
        wchar_t* drive = drives;

        while (*drive) {
            ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalFreeBytes;

            if (GetDiskFreeSpaceExW(drive, &freeBytesAvailable, &totalNumberOfBytes, &totalFreeBytes)) {
                UINT driveType = GetDriveTypeW(drive);
                std::wstring fsType = L"Unknown";

                if (driveType == DRIVE_FIXED) {
                    wchar_t volumeName[MAX_PATH];
                    wchar_t fileSystemType[MAX_PATH];
                    if (GetVolumeInformationW(drive, volumeName, MAX_PATH, NULL, NULL, NULL, fileSystemType, MAX_PATH)) {
                        fsType = fileSystemType;
                    }
                }

                result += L"- " + std::wstring(drive) + L" (" + fsType + L") : "
                       + std::to_wstring(totalFreeBytes.QuadPart / (1024 * 1024 * 1024)) + L" GB free / "
                       + std::to_wstring(totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024)) + L" GB total\n";
            }
            drive += wcslen(drive) + 1;
        }
    }
    

    return result;
}