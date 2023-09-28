#ifndef __LOG_H__
#define __LOG_H__

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "Module.h"

#define LOG(format, ...) Logger::log(__FILE__, __LINE__, format, __VA_ARGS__)

class Logger : public Module {
public:

    Logger(Application* app, bool start_enabled = true);
    virtual ~Logger();

    static void log(const char file[], int line, const char* format, ...);

public:

    static char tmp_string[4096];
    static char tmp_string2[4096];

    static std::vector<std::string> debugStrings;

};

#endif //__LOG_H__