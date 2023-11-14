#pragma once

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>

#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "glu32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Source/External/Glew/libx86/glew32.lib")

#include "External/DevIL/include/il.h"	
#include "External/DevIL/include/ilu.h"	

#include "External/MathGeoLib/include/Math/float3x3.h"
#include "External/MathGeoLib/include/Math/float4x4.h"

#ifdef _DEBUG
#pragma comment (lib, "Source/External/MathGeoLib/libx86/lib_Debug/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#else
#pragma comment (lib, "Source/External/MathGeoLib/libx86/lib_Release/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#endif // _DEBUG

#include <fstream>
#include <vector>
#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "Primitive.h"

#include "Model.h"
#include "Texture.h"
#include "Shader.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"

#define MAX_LIGHTS 8

class GameObject;

class ModuleRenderer3D : public Module
{
public:

	ModuleRenderer3D(Application* app, bool start_enabled = true);
	virtual ~ModuleRenderer3D();

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

	void OnResize(int width, int height);

	void DrawModels();
	void ClearModels();

	void EnableAssimpDebugger();
	void CleanUpAssimpDebugger();

	void HandleDragAndDrop();
	bool IsFileExtension(const char* directory, const char* extension);

	void ApplyCheckerTexture();
	void ClearActualTexture();

	void ReloadTextures();

	void DrawBoundingBox(float3* vertices, float3 color);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;

	CPlane Grid;
	bool showGrid = true;
	
	// You won't need this after using Frustum
	mat4x4 ProjectionMatrix;

	// 3D Models
	std::vector<Model> models;

	bool texturingEnabled = true;

	GLuint framebuffer = 0;

	GLuint textureColorbuffer = 0;

};