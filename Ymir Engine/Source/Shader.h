#pragma once

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float4x4.h"
#include "External/MathGeoLib/include/Math/Quat.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define SHADER_VS "Assets/Shaders/VertexShader.glsl"
#define SHADER_FS "Assets/Shaders/FragmentShader.glsl"

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

    void Translate(float3 translation);
    void Rotate(float3 rotation);
    void Scale(float3 scale);

    void SetShaderUniforms();

    void ToggleNormalMap(bool value);

public:

    // Shader Program Identificator (ID)
    GLuint shaderProgram;

    float3 translation = { 0, 0, 0 };
    float3 rotation = { 0,0,0 };
    float3 scale = { 1,1,1 };

    bool normalMap;
    bool selected;

    float4x4 projection;
    float4x4 view;
    float4x4 model;

private:

    // Private methods to encapsulate Shader Functionality
    void AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
    std::string Shader::ReadShaderFile(const std::string& filename);

    float4x4 CreateTranslationMatrix(float3 translation);
    float4x4 CreateRotationMatrix(float3 rotation);
    float4x4 CreateScaleMatrix(float3 scale);

private:

    float4x4 translationMatrix;
    float4x4 rotationMatrix;
    float4x4 scaleMatrix;

};