#pragma once
#include <windows.h>
#include <cstdlib>

// WideChar (UTF-16) to ANSI string conversion.
// Caller must free() the returned pointer.
inline char* WideCharToAnsi(const WCHAR* wideStr) {
    int size = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
    if (size == 0) return NULL;
    char* mbStr = (char*)malloc(size * sizeof(char));
    if (mbStr == NULL) return NULL;
    WideCharToMultiByte(CP_ACP, 0, wideStr, -1, mbStr, size, NULL, NULL);
    return mbStr;
}
