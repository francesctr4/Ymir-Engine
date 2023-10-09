#pragma once

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


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
    void UseShader();

    // Clear the Shader
    void ClearShader();

    // Utility Uniform Functions
    
    //void SetBool(const std::string& name, bool value) const;
    //void SetInt(const std::string& name, int value) const;
    //void SetFloat(const std::string& name, float value) const;

private:

    // Private methods to encapsulate Shader Functionality
    void AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
    std::string Shader::ReadShaderFile(const std::string& filename);

    // Shader Program Identificator (ID)
    GLuint shaderProgram;

};