#pragma once

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "External/MathGeoLib/include/Math/float4x4.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define SHADER_VS "../Source/shader.vs"
#define SHADER_FS "../Source/shader.fs"

class Shader
{
public:

    // Shader constructors
    Shader();
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    // Shader destructor
    virtual ~Shader();

    // Load the Shader
    void LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    // Use the Shader
    void UseShader(bool toggle);

    // Clear the Shader
    void ClearShader();

    // Utility Uniform Functions
    
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;

    void SetMatrix4x4(const std::string& name, float4x4 value) const;

private:

    // Private methods to encapsulate Shader Functionality
    void AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
    std::string Shader::ReadShaderFile(const std::string& filename);

    // Shader Program Identificator (ID)
    GLuint shaderProgram;

};