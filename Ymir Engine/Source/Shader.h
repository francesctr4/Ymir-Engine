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
#include <regex>

#define SHADER_VS "Assets/Shaders/VertexShader.glsl"
#define SHADER_FS "Assets/Shaders/FragmentShader.glsl"
#define SHADER_VS_FS "Assets/Shaders/MyShader.glsl"

// Regex utils to retrieve code from unique-file shaders
const std::regex versionRegex("#version\\s+\\d+\\s+core");
const std::regex vertexShaderRegex("#ifdef VERTEX_SHADER([\\s\\S]+?)#endif");
const std::regex fragmentShaderRegex("#ifdef FRAGMENT_SHADER([\\s\\S]+?)#endif");

class Shader
{
public:

    // Shader constructors
    Shader();
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    // Shader destructor
    virtual ~Shader();

    // Functions to load the Shader
    void LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void LoadShader(const std::string& shaderFilePath);
    void LoadShaderFromString(const std::string& shaderString);

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
    std::string ReadShaderFile(const std::string& filename);

    float4x4 CreateTranslationMatrix(float3 translation);
    float4x4 CreateRotationMatrix(float3 rotation);
    float4x4 CreateScaleMatrix(float3 scale);

private:

    float4x4 translationMatrix;
    float4x4 rotationMatrix;
    float4x4 scaleMatrix;

};