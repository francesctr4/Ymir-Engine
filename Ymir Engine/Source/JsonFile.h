#pragma once

#include <string>
#include <fstream>

#include "External/Parson/parson.h"

#include "External/MathGeoLib/include/Math/float2.h"
#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float4.h"

#include "External/MathGeoLib/include/Math/float3x3.h"
#include "External/MathGeoLib/include/Math/float4x4.h"

#include "External/MathGeoLib/include/Math/Quat.h"

class JsonFile {
public:

    JsonFile();
    JsonFile(std::string route, std::string fileName);

    virtual ~JsonFile();

    void CreateJSON(std::string route, std::string fileName);

    // -------------------------- Support functions --------------------------------

    void SetInt(const char* key, int value);
    int GetInt(const char* key) const;

    void SetFloat(const char* key, float value);
    float GetFloat(const char* key) const;

    void SetDouble(const char* key, double value);
    double GetDouble(const char* key) const;

    void SetBoolean(const char* key, bool value);
    bool GetBoolean(const char* key) const;

    void SetString(const char* key, const char* string);
    std::string GetString(const char* key) const;

    void SetIntArray(const char* key, const int* array, size_t size);
    int* GetIntArray(const char* key) const;

    void SetFloatArray(const char* key, const float* array, size_t size);
    float* GetFloatArray(const char* key) const;

    void SetDoubleArray(const char* key, const double* array, size_t size);
    double* GetDoubleArray(const char* key) const;

    // -------------------------- MathGeoLib functions --------------------------------

    void SetFloat2(const char* key, const float2& value);
    float2 GetFloat2(const char* key) const;

    void SetFloat3(const char* key, const float3& value);
    float3 GetFloat3(const char* key) const;

    void SetFloat4(const char* key, const float4& value);
    float4 GetFloat4(const char* key) const;

    void SetMatrix3x3(const char* key, const float3x3& matrix);
    float3x3 GetMatrix3x3(const char* key) const;

    void SetMatrix4x4(const char* key, const float4x4& matrix);
    float4x4 GetMatrix4x4(const char* key) const;

    void SetQuat(const char* key, const Quat& quaternion);
    Quat GetQuat(const char* key) const;

private:

    JSON_Value* rootValue; // Private member to store JSON value
    JSON_Object* rootObject; // Private member to store JSON object

    void InitializeJSON(); // Helper function to initialize JSON object and value.
    void DeinitializeJSON(); // Helper function to deinitialize JSON object and value.

};