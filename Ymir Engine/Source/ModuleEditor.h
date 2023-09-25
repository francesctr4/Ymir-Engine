#ifndef MODULE_EDITOR
#define MODULE_EDITOR

#include "Module.h"
#include "Globals.h"
#include <vector>

class ModuleEditor : public Module
{
public:

	explicit ModuleEditor(Application* app, bool start_enabled = true);
	virtual ~ModuleEditor();

	bool Init() override;
	void DrawEditor();
	bool CleanUp() override;

	void AddFPS(const float aFPS);

private:

	//std::vector<float> mFPSLog;
	
	bool UpdateAndRenderAdditionalPlatformWindows = false;

};

#endif // MODULE_EDITOR