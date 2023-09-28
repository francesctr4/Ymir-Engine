#include "Log.h"

#include "Application.h"
#include "ModuleEditor.h"

char Logger::tmp_string[4096];
char Logger::tmp_string2[4096];

std::vector<std::string> Logger::debugStrings;

Logger::Logger(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

Logger::~Logger()
{

}

void Logger::log(const char file[], int line, const char* format, ...)
{
	static va_list  ap;

	// Construct the string from variable arguments

	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);

	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);

	//App.editor.debugstrings.pushback.tmp_string2;
	
	debugStrings.push_back(tmp_string2);

	OutputDebugString(tmp_string2);
}