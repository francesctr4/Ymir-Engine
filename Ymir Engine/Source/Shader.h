#pragma once

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float4x4.h"
#include "External/MathGeoLib/include/Math/Quat.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#define SHADER_VS_FS "Assets/Shaders/MyShader.glsl"
#define WATER_SHADER "Assets/Shaders/WaterShader.glsl"

// Regex utils to retrieve code from unique-file shaders
const std::regex versionRegex("#version\\s+\\d+\\s+core");
const std::regex vertexShaderRegex("#ifdef VERTEX_SHADER([\\s\\S]+?)#endif");
const std::regex fragmentShaderRegex("#ifdef FRAGMENT_SHADER([\\s\\S]+?)#endif");

enum class UniformType {

    NONE = -1,

    f1, 
    f1v, 
    i1, 
    i1v, 
    f2, 
    f2v, 
    i2, 
    i2v, 
    f3, 
    f3v, 
    i3, 
    i3v, 
    f4, 
    f4v, 
    i4, 
    i4v, 
    f2mat, 
    f3mat, 
    f4mat,

    ALL

};

struct Uniform {

    Uniform(std::string name, void* value, UniformType valueType, int numberOfElements)
        : value(value), name(name), valueType(valueType), elements(numberOfElements) {}

    void* value;
    std::string name;
    UniformType valueType;
    int elements;

};

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

    // Function to evaluate the availability of the Shader
    bool IsValid();

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

    // Value pointer MUST be allocated in heap (new)
    void AddUniform(std::string name, void* value, UniformType type, int nElements);

    // Deleting uniform does not delete value allocation
    void DeleteUniform(std::string name);

public:

    // Shader Program Identificator (ID)
    GLuint shaderProgram;

    // Shader Uniforms
    std::vector<Uniform> uniforms;

    float3 translation = { 0, 0, 0 };
    float3 rotation = { 0,0,0 };
    float3 scale = { 1,1,1 };

    bool normalMap;
    bool selected;

    float4x4 projection;
    float4x4 view;
    float4x4 model;

    std::string path;

    // Static map to keep track of the already loaded shaders in the engine
    static std::map<std::string, Shader*> loadedShaders;

private:

    // Private methods to encapsulate Shader Functionality
    void AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
    std::string ReadShaderFile(const std::string& filename);

    // Private method to link code uniforms to shader uniforms  
    void BindUniform(Uniform* uniformPtr);

    float4x4 CreateTranslationMatrix(float3 translation);
    float4x4 CreateRotationMatrix(float3 rotation);
    float4x4 CreateScaleMatrix(float3 scale);

private:

    float4x4 translationMatrix;
    float4x4 rotationMatrix;
    float4x4 scaleMatrix;

};