#ifndef __DEFAULT_SHADER__
#define __DEFAULT_SHADER__

#include <string>

/* This is the default shader, which is the minimum amount of GLSL code in order to
use the shader on the engine and render models correctly on screen. */

namespace DefaultShader {

	static std::string Source = R"(#version 450 core

#ifdef VERTEX_SHADER

	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aNormal;
	layout(location = 2) in vec2 aTexCoords;

	out vec2 TexCoords;

	uniform mat4 projection;
	uniform mat4 view;
	uniform mat4 model;

	void main()
	{
		gl_Position = projection * view * model * vec4(aPos, 1.0f);
		TexCoords = aTexCoords;
	}

#endif 

#ifdef FRAGMENT_SHADER

	in vec2 TexCoords;

	out vec4 FragColor;

	uniform sampler2D texture_diffuse1;

	void main()
	{
		FragColor = texture(texture_diffuse1, TexCoords);
	}

#endif)";

}

#endif // __DEFAULT_SHADER__