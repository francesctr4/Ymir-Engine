#ifndef MODULE_EDITOR
#define MODULE_EDITOR

#include "Module.h"
#include "Globals.h"
#include "Log.h"
#include "Primitive.h"
#include <vector>
#include <string>

class GameObject;

enum GizmoOperation
{
	TRANSLATE,
	ROTATE,
	SCALE
};

enum GizmoMode
{
	LOCAL,
	WORLD
};

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

	// Manages the docking functionality with the main window
	void WindowDockSpaceManagement();

	// OpenGL settings checkbox toggle encapsulation
	void Toggle_GL_DepthTesting(bool depthTesting);
	void Toggle_GL_FaceCulling(bool faceCulling);
	void Toggle_GL_Lighting(bool lighting);
	void Toggle_GL_ColorMaterial(bool colorMaterial);
	void Toggle_GL_TextureMapping2D(bool textureMapping2D);
	void Toggle_GL_TextureMapping3D(bool textureMapping3D);
	void Toggle_GL_Blending(bool blending);
	void Toggle_GL_MSAA(bool msaa);
	void Toggle_GL_StencilTesting(bool stencilTesting);
	void Toggle_GL_ScissorTesting(bool scissorTesting);
	void Toggle_GL_AlphaTesting(bool alphaTesting);
	void Toggle_GL_PointSprites(bool pointSprites);
	void Toggle_GL_Fog(bool fog);
	void Toggle_GL_PointSmooth(bool pointSmooth);
	void Toggle_GL_LineSmooth(bool lineSmooth);
	void Toggle_GL_Normalization(bool normalization);
	void Toggle_GL_PolygonOffset(bool polygonOffset);
	void Toggle_GL_WireframeMode(bool wireframe);

	// Functions related to Framerate Histograms
	void AddFPS(const float aFPS);
	void AddDT(const float aDT);
	void AddMS(const float aMS);

	// Function to encapsulate website redirection OnClick()
	void RequestBrowser(const char* url);

	// Window settings checkbox toggle encapsulation
	void ToggleFullscreen(bool fullscreen);
	void ToggleResizable(bool resizable);
	void ToggleBorderless(bool borderless);
	void ToggleFullscreenDesktop(bool fullscreenDesktop);

	// Renderer3D settings checkbox toggle encapsulation
	void ToggleVSync(bool vsync);

	// Editor settings checkbox toggle encapsulation
	void ToggleLightMode(bool lightMode);

	// Meshes normal settings checkbox toggle encapsulation
	void ToggleMeshesVertexNormals(bool showVertexNormals);
	void ToggleMeshesFaceNormals(bool showFaceNormals);

	// Hardware Detection
	void ShowPlatformInfo();
	void ShowCPUInfo();
	void ShowGPUInfo();
	void ShowRAMInfo();
	void ShowDiskInfo();

	// Function to encapsulate About modal window
	void AboutModalWindowContent();

	// Function to encapsulate Reading files
	std::string ReadFile(const std::string& filename);

	// Function to show log output on the editor
	void RedirectLogOutput();

	// Function to show memleaks file output on the editor
	void MemoryLeaksOutput();

	// Function to show memleaks file output on the editor
	void AssimpLogOutput();

	// Function to encapsulate GameObjects hierarchy
	void DrawHierarchy();
	void CreateHierarchyTree(GameObject* node);
	void DestroyHierarchyTree(GameObject* node);

	// Function to encapsulate GameObjects inspector
	void DrawInspector();

	// Function to manage Gizmo
	void ManipulateGizmo(const float* viewMatrix, const float* projectionMatrix, GizmoOperation operation, GizmoMode mode, float* modelMatrix, float* deltaMatrix = 0, float* snap = 0);

public:

	// Enables ImGui to render additional data
	bool UpdateAndRenderAdditionalPlatformWindows = false;

	// Booleans to Open/Close Editor windows
	bool showApplication = false;
	bool showConsole = true;
	bool showMemoryLeaks = false;
	bool showAssimpLog = false;
	bool showHierarchy = true;
	bool showInspector = true;

	// OpenGL settings checkbox toggle booleans
	bool gl_DepthTesting = true;
	bool gl_FaceCulling = true;
	bool gl_Lighting = true;
	bool gl_ColorMaterial = true;
	bool gl_TextureMapping2D = true;
	bool gl_TextureMapping3D = false;
	bool gl_Blending = false;
	bool gl_MSAA = false;
	bool gl_StencilTesting = false;
	bool gl_ScissorTesting = false;
	bool gl_AlphaTesting = false;
	bool gl_PointSprites = false;
	bool gl_Fog = false;
	bool gl_PointSmooth = false;
	bool gl_LineSmooth = false;
	bool gl_Normalization = false;
	bool gl_PolygonOffset = false;
	bool gl_WireframeMode = false;

	// Vectors related to Framerate Histograms
	std::vector<float> FPSvec;
	std::vector<float> DTvec;
	std::vector<float> MSvec;

	// Window settings checkbox toggle booleans
	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fullscreenDesktop = false;

	// Renderer3D settings checkbox toggle booleans
	bool vsync = true;

	// Editor settings checkbox toggle booleans
	bool lightMode = false;
	bool showImGuiDemo = false;

	// Window sliders
	int windowWidth = 0;
	int windowHeight = 0;
	float opacity = 0.0f;

	// About modal window inside help menu
	bool showAboutPopUp = false;
	std::string licenseFileContents;

	// Memory Leaks file
	std::string memleaksFileContents;

	// Assimp Log file
	std::string AssimpLogFileContents;

	// 3D Meshes Configuration
	bool showVertexNormals = false;
	bool showFaceNormals = false;

};

#endif // MODULE_EDITOR