#include <iostream>
#include <string>

using std::wcin;
using std::wcout;

namespace mix {

    std::wstring formatBool(bool state) {
        if (state) {
            return L"True";
        }
        return L"False";
    }

}