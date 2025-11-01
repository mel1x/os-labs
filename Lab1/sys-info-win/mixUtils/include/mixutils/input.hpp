#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <type_traits>
#include <cwctype>
#include <locale>
#include <codecvt>

using std::wcin;
using std::wcout;
using std::wstring;
using std::is_same_v;
using std::wstring_view;

namespace mix {
    inline bool ends_with(wstring_view str, wstring_view suffix) {
        return str.size() >= suffix.size() &&
               str.substr(str.size() - suffix.size()) == suffix;
    }
    
    inline void print_prompt(wstring_view prompt) {
        if (prompt.empty()) return;
        wcout << prompt;
        if (ends_with(prompt, L": ") || ends_with(prompt, L"? ")) {
            return;
        }
        if (ends_with(prompt, L":") || ends_with(prompt, L"?")) {
            wcout << L' ';
        }
        else {
            wcout << L": ";
        }
    }
    
    inline void rtrim(wstring& s) {
        while (!s.empty() && iswspace(s.back())) s.pop_back();
    }
    
    inline void ltrim(wstring& s) {
        size_t i = 0;
        while (i < s.size() && iswspace(s[i])) ++i;
        if (i) s.erase(0, i);
    }
    
    inline std::string wstring_to_string(const wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }
    
    template <class T>
    T input(wstring_view prompt = L"Ввод: ")
    {
        for (;;) {
            print_prompt(prompt);
            wstring line;
            if (!std::getline(wcin, line)) {
                throw std::runtime_error("input: конец потока");
            }
            ltrim(line);
            rtrim(line);
            
            if constexpr (is_same_v<T, wstring>) {
                return line;
            }
            else if constexpr (is_same_v<T, std::string>) {
                return wstring_to_string(line);
            }
            else if constexpr (is_same_v<T, wchar_t>) {
                for (wchar_t ch : line) {
                    if (!iswspace(ch)) return ch;
                }
                wcout << L"Пусто. Попробуйте ещё раз.\n";
            }
            else {
                std::wistringstream iss{ line };
                T value{};  
                iss >> value;
                if (iss && (iss >> std::ws).eof()) {
                    return value;
                }
                wcout << L"Некорректный ввод. Попробуйте ещё раз.\n";
            }
        }
    }
}