#include <iostream>

#include "../mixUtils/include/mixUtils.hpp"
#include "linuxVersion/getLinuxVersion.hpp"
#include "linuxAuth/getLinuxAuthorization.hpp"
#include "linuxCPU/getLinuxProcessorInfo.hpp"
#include "linuxMem/getLinuxMemoryInfo.hpp"
#include "linuxMem/getLinuxDrives.hpp"


using mix::print;

int main() {
    print(getLinuxVersion()); // OS, Kernel, Architecture
    print(getLinuxAuthorization()); // Hostname, User
    print(getLinuxProcessorInfo()); // Processors, Load
    print(getLinuxMemoryInfo()); // RAM, Swap, Virtual Memory
    print(getLinuxDrives()); // Drives
}