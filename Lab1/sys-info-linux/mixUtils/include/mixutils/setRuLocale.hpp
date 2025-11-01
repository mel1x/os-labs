#pragma once
#include <iostream>
#include <locale>
#include <clocale>

#ifdef _WIN32
  #include <io.h>
  #include <fcntl.h>
#endif

namespace mix {

    inline void setRuLocale() {
    #ifdef _WIN32
        // Переводим wide-потоки в UTF-16. Это главное.
        _setmode(_fileno(stdin),  _O_U16TEXT);
        _setmode(_fileno(stdout), _O_U16TEXT);
        _setmode(_fileno(stderr), _O_U16TEXT);
    
        // Локаль по умолчанию системы (OK для форматирования чисел/дат).
        std::locale loc("");
        std::locale::global(loc);
        std::wcin.imbue(loc);
        std::wcout.imbue(loc);
        std::wcerr.imbue(loc);
    
        // setlocale — для C-API (wprintf/scanf и т.п.)
        std::setlocale(LC_ALL, "");
    #else
        std::setlocale(LC_ALL, "ru_RU.UTF-8");
        std::locale loc("ru_RU.UTF-8");
        std::locale::global(loc);
        std::wcin.imbue(loc);
        std::wcout.imbue(loc);
        std::wcerr.imbue(loc);
    #endif
    }

}