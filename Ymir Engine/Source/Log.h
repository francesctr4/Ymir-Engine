#pragma once

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>

#define LOG(format, ...) Log::log(__FILE__, __LINE__, format, __VA_ARGS__)

class Log {
public:

    Log() {}
    virtual ~Log() {}

    static void log(const char file[], int line, const char* format, ...);

public:

    static std::vector<std::string> debugStrings;

private:

    static char tmp_string[4096];
    static char tmp_string2[4096];

};