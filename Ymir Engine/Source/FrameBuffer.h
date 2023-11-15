#pragma once

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>

#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "glu32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Source/External/Glew/libx86/glew32.lib")

#include "Globals.h"
#include "Log.h"

class FrameBuffer {
public:

	FrameBuffer();

	void Load();

	void Render(bool toggle);

	void Delete();

public:

	GLuint FBO; // Frame Buffer Object
	GLuint TCB; // Texture Color Buffer
	GLuint RBO; // Render Buffer Object

};