#include <windows.h>
#include <iostream>

#include "../mixUtils/include/mixUtils.hpp"
#include "windowsVersion/getWindowsVersion.hpp"
#include "windowsCPUInfo/getWindowsCPUInfo.hpp"
#include "windowsMemInfo/getWindowsMemInfo.hpp"
#include "windowsDisksInfo/getWindowsDisksInfo.hpp"

using mix::print;

int main() {
    print(getWindowsVersion());
    print(getWindowsCPUInfo());
    print(getWindowsMemInfo());
    print(getWindowsDisksInfo());
}