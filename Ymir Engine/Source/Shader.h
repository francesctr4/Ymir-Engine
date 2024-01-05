#ifndef __SHADER__
#define __SHADER__

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

// Definitions to access the paths quickly
#define SHADER_VS_FS "Assets/Shaders/MyShader.glsl"
#define WATER_SHADER "Assets/Shaders/WaterShader.glsl"

// Regex utils to retrieve code from unique-file shaders
const std::regex versionRegex("#version\\s+\\d+\\s+core");
const std::regex vertexShaderRegex("#ifdef VERTEX_SHADER([\\s\\S]+?)#endif");
const std::regex fragmentShaderRegex("#ifdef FRAGMENT_SHADER([\\s\\S]+?)#endif");

enum class UniformType {

    NONE = -1,

    boolean, // bool
    f1, // float
    f1v, 
    i1, // int
    i1v, 
    f2, // vec2
    f2v, 
    i2, // ivec2
    i2v, 
    f3, // vec3
    f3v, 
    i3, // ivec3
    i3v, 
    f4, // vec4
    f4v, 
    i4, // ivec4
    i4v, 
    f2mat, // mat2
    f3mat, // mat3
    f4mat, // mat4

    ALL

};

struct Uniform {

    Uniform() : value(nullptr), name(""), type(UniformType::NONE), nElements(0) {}
    Uniform(std::string name, void* value, UniformType type, int nElements)
        : value(value), name(name), type(type), nElements(nElements) {}

    std::string name;
    void* value;
    UniformType type;
    int nElements;

};

class Shader
{
public:

    // Shader constructors
    Shader();
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    // Shader destructor
    virtual ~Shader();

    /* Functions to load the shader. Recommended to use "void LoadShader(const std::string& shaderFilePath);"
    The Shader Pipeline of the engine is managed using single file shaders. */
    void LoadShader(const std::string& shaderFilePath);

    void LoadShaderFromString(const std::string& shaderString);
    void LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

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

    // Functions to manage Shader Transformations
    void Translate(float3 translation);
    void Rotate(float3 rotation);
    void Scale(float3 scale);

    // Function to set shader uniforms that are essential (matrices, time, etc.)
    void SetShaderUniforms();

    // Uniform Management Functions
    void AddUniform(std::string name, void* value, UniformType type, int nElements);
    void DeleteUniform(std::string name);
    void SetUniformValue(const std::string& name, const void* newValue);
    static size_t GetUniformSize(UniformType type);

public:

    // Shader Program Identificator (ID)
    GLuint shaderProgram;
    std::string path;

    // Shader Uniforms Vector
    std::vector<Uniform> uniforms;

    // Essential Uniforms
    bool selected;
    float4x4 projection;
    float4x4 view;
    float4x4 model;

    // Shader Transformations Management
    float3 translation = { 0, 0, 0 };
    float3 rotation = { 0,0,0 };
    float3 scale = { 1,1,1 };

    // Static map to keep track of the already loaded shaders in the engine
    static std::map<std::string, Shader*> loadedShaders;

    // Static map to convert uniform type to string
    static std::map<UniformType, std::string> uniformTypeToString;

private:

    // Private methods to encapsulate Shader Functionality
    void AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
    std::string ReadShaderFile(const std::string& filename);

    // Private method to link code uniforms to shader uniforms  
    void BindUniform(Uniform* uniform);

    // Private method to read the uniforms directly from shader code
    void ExtractUniformsFromShaderCode(const std::string& shaderCode);

    // Private methods to create the transformations matrices
    float4x4 CreateTranslationMatrix(float3 translation);
    float4x4 CreateRotationMatrix(float3 rotation);
    float4x4 CreateScaleMatrix(float3 scale);

private:

    // Transformation matrices handlers
    float4x4 translationMatrix;
    float4x4 rotationMatrix;
    float4x4 scaleMatrix;

};

#endif // __SHADER__