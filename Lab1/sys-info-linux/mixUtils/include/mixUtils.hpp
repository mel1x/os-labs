#pragma once
#include <iostream>
#include <string>
#include <locale>
#include "mixutils/types.hpp"
#include "mixutils/input.hpp"
#include "mixutils/setRuLocale.hpp"

using std::wcout;

namespace mix {

    template<typename First, typename... Rest>
    inline void print(const First& first, const Rest&... rest) {
        wcout << first;
        if constexpr (sizeof...(Rest) > 0) {
            ((wcout << L' ' << rest), ...);
        }
        wcout << std::endl;
    }
    inline void print() { wcout << L'\n'; }

}

#include "../src/mixUtils.cpp"