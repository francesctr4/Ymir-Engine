#ifndef MODULE_EDITOR
#define MODULE_EDITOR

#include "Module.h"
#include "Globals.h"
#include <vector>
#include <string>

class ModuleEditor : public Module
{
public:

	// Constructor
	ModuleEditor(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleEditor();

	// Module functions
	bool Init() override;
	bool CleanUp() override;

	// Draws the editor on the window
	void DrawEditor();

	// Functions related to Framerate Histograms
	void AddFPS(const float aFPS);
	void AddDT(const float aDT);
	void AddMS(const float aMS);

	// Function to encapsulate website redirection OnClick()
	void RequestBrowser(const char* url);

	// Window checkbox toggle encapsulation
	void ToggleFullscreen(bool fullscreen);
	void ToggleResizable(bool resizable);
	void ToggleBorderless(bool borderless);
	void ToggleFullscreenDesktop(bool fullscreenDesktop);
	void ToggleLightMode(bool lightMode);

	// Hardware Detection
	void ShowPlatformInfo();
	void ShowCPUInfo();
	void ShowGPUInfo();
	void ShowRAMInfo();
	void ShowDiskInfo();

	// Function to encapsulate About modal window
	void AboutModalWindowContent();

	// Function to encapsulate Reading files (to read LICENSE)
	std::string ModuleEditor::ReadFile(const std::string& filename);

	// TODO: Function to show log output on the editor
	void RedirectLogOutput();

public:

	// Enables ImGui to render additional data
	bool UpdateAndRenderAdditionalPlatformWindows = false;

	// Vectors related to Framerate Histograms
	std::vector<float> FPSvec;
	std::vector<float> DTvec;
	std::vector<float> MSvec;

	// Window checkbox toggle booleans
	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fullscreenDesktop = false;
	bool lightMode = false;
	bool showImGuiDemo = false;

	// Window sliders
	int windowWidth = 0;
	int windowHeight = 0;
	float opacity = 0.0f;

	// About modal window inside help menu
	bool showAboutPopUp = false;
	std::string licenseFileContents;

};

#endif // MODULE_EDITOR