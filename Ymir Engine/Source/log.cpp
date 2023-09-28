#include "Log.h"

char Log::tmp_string[4096];
char Log::tmp_string2[4096];

std::vector<std::string> Log::debugStrings;

void Log::log(const char file[], int line, const char* format, ...)
{
	static va_list ap;

	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);

	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	
	debugStrings.push_back(tmp_string2);

	OutputDebugString(tmp_string2);
}