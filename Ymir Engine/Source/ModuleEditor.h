#ifndef MODULE_EDITOR
#define MODULE_EDITOR

#include "Module.h"
#include "Globals.h"
#include <vector>

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	virtual ~ModuleEditor();

	bool Init() override;
	void DrawEditor();
	bool CleanUp() override;

	void AddFPS(const float aFPS);
	void AddDT(const float aDT);
	void AddMS(const float aMS);

	void RequestBrowser(const char* url);

public:

	std::vector<float> FPSvec;
	std::vector<float> DTvec;
	std::vector<float> MSvec;

	bool UpdateAndRenderAdditionalPlatformWindows = false;

};

#endif // MODULE_EDITOR