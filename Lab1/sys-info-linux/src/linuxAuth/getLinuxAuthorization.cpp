#include "getLinuxAuthorization.hpp"
#include <unistd.h>
#include <string>
#include <pwd.h>

std::wstring to_wstring(const char* str) {
    std::wstring wstr;
    while (*str) {
        wstr += static_cast<wchar_t>(*str++);
    }
    return wstr;
}

std::wstring getUserName() {
    char* login = getlogin();
    if (login) {
        return to_wstring(login);
    }
    return L"Unknown user";
}

std::wstring getHostName() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return to_wstring(hostname);
    }
    return L"Unknown hostname";
}

std::wstring getLinuxAuthorization() {
    std::wstring result = L"";

    result += L"User: " + getUserName() + L"\nHostname: " + getHostName();
    return result;
}