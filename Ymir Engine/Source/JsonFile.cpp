#include "JsonFile.h"
#include <vector>
#include "Log.h"

JsonFile::JsonFile()
{
    InitializeJSON();
}

JsonFile::JsonFile(std::string route, std::string fileName)
{
    InitializeJSON();
    CreateJSON(route, fileName);
}

JsonFile::~JsonFile()
{
    DeinitializeJSON();
}

void JsonFile::InitializeJSON()
{
    rootValue = json_value_init_object();
    rootObject = json_value_get_object(rootValue);
}

void JsonFile::DeinitializeJSON()
{
    if (rootValue != nullptr)
    {
        json_value_free(rootValue);
        rootValue = nullptr;
        rootObject = nullptr;
    }
}

void JsonFile::CreateJSON(std::string route, std::string fileName)
{
    std::string fullRoute = route + fileName;

    FILE* file;
    errno_t err = fopen_s(&file, fullRoute.c_str(), "w");

    if (err == 0 && file != nullptr) {

        char* serialized_json = json_serialize_to_string_pretty(rootValue);

        if (serialized_json) {

            fprintf(file, "%s\n", serialized_json);
            json_free_serialized_string(serialized_json);

        }

        fclose(file);

    }
    else {

        LOG("JsonFile: Failed to open file.");

    }

}

void JsonFile::ModifyJSON(std::string route, std::string fileName)
{

}

void JsonFile::DeleteJSON(std::string route, std::string fileName)
{

}

JsonFile* JsonFile::GetJSON(const std::string& route) {

    JsonFile* jsonFile = new JsonFile();

    // Load the existing JSON file

    jsonFile->rootValue = json_parse_file(route.c_str());

    // Error handling
    if (!jsonFile->rootValue) {

        LOG("Error: Unable to load JSON file from %s", route.c_str());

        delete jsonFile;

        return nullptr;
    }

    // Get the JSON object from the root value
    jsonFile->rootObject = json_value_get_object(jsonFile->rootValue);

    return jsonFile;
}

// -------------------------- Support functions --------------------------------

void JsonFile::SetInt(const char* key, int value) {

    json_object_set_number(rootObject, key, (int)value);

}

int JsonFile::GetInt(const char* key) const
{
    return (int)json_object_get_number(rootObject, key);
}

void JsonFile::SetFloat(const char* key, float value) {

    json_object_set_number(rootObject, key, (float)value);

}

float JsonFile::GetFloat(const char* key) const
{
    return (float)json_object_get_number(rootObject, key);
}

void JsonFile::SetDouble(const char* key, double value)
{
    json_object_set_number(rootObject, key, value);
}

double JsonFile::GetDouble(const char* key) const
{
    return json_object_get_number(rootObject, key);
}

void JsonFile::SetBoolean(const char* key, bool value) {

    json_object_set_boolean(rootObject, key, (bool)value);

}

bool JsonFile::GetBoolean(const char* key) const
{
    return (bool)json_object_get_boolean(rootObject, key);
}

void JsonFile::SetString(const char* key, const char* string) {

    json_object_set_string(rootObject, key, string);

}

std::string JsonFile::GetString(const char* key) const
{
    return json_object_get_string(rootObject, key);
}

void JsonFile::SetIntArray(const char* key, const int* array, size_t size) {

    JSON_Value* jsonArrayValue = json_value_init_array();
    JSON_Array* jsonArrayObject = json_value_get_array(jsonArrayValue);

    for (unsigned int i = 0; i < size; i++)
    {
        json_array_append_number(jsonArrayObject, array[i]);
    }

    json_object_set_value(rootObject, key, jsonArrayValue);

}

int* JsonFile::GetIntArray(const char* key) const {

    JSON_Value* jsonArrayValue = json_object_get_value(rootObject, key);

    if (jsonArrayValue == nullptr || json_value_get_type(jsonArrayValue) != JSONArray)
    {
        return nullptr;
    }

    JSON_Array* jsonArrayObject = json_value_get_array(jsonArrayValue);
    size_t size = json_array_get_count(jsonArrayObject);

    int* resultArray = new int[size + 1];

    for (size_t i = 0; i < size; i++)
    {
        resultArray[i] = static_cast<int>(json_array_get_number(jsonArrayObject, i));
    }

    resultArray[size] = -1;

    return resultArray;
}

void JsonFile::SetFloatArray(const char* key, const float* array, size_t size) {

    JSON_Value* jsonArrayValue = json_value_init_array();
    JSON_Array* jsonArrayObject = json_value_get_array(jsonArrayValue);

    for (unsigned int i = 0; i < size; i++)
    {
        json_array_append_number(jsonArrayObject, array[i]);
    }

    json_object_set_value(rootObject, key, jsonArrayValue);

}

float* JsonFile::GetFloatArray(const char* key) const {

    JSON_Value* jsonArrayValue = json_object_get_value(rootObject, key);

    if (jsonArrayValue == nullptr || json_value_get_type(jsonArrayValue) != JSONArray)
    {
        return nullptr;
    }

    JSON_Array* jsonArrayObject = json_value_get_array(jsonArrayValue);
    size_t size = json_array_get_count(jsonArrayObject);

    float* resultArray = new float[size + 1];

    for (size_t i = 0; i < size; i++)
    {
        resultArray[i] = static_cast<float>(json_array_get_number(jsonArrayObject, i));
    }

    resultArray[size] = -1;

    return resultArray;
}

void JsonFile::SetDoubleArray(const char* key, const double* array, size_t size)
{
    JSON_Value* jsonArrayValue = json_value_init_array();
    JSON_Array* jsonArrayObject = json_value_get_array(jsonArrayValue);

    for (unsigned int i = 0; i < size; i++)
    {
        json_array_append_number(jsonArrayObject, array[i]);
    }

    json_object_set_value(rootObject, key, jsonArrayValue);
}

double* JsonFile::GetDoubleArray(const char* key) const
{
    JSON_Value* jsonArrayValue = json_object_get_value(rootObject, key);

    if (jsonArrayValue == nullptr || json_value_get_type(jsonArrayValue) != JSONArray)
    {
        return nullptr;
    }

    JSON_Array* jsonArrayObject = json_value_get_array(jsonArrayValue);
    size_t size = json_array_get_count(jsonArrayObject);

    double* resultArray = new double[size + 1];

    for (size_t i = 0; i < size; i++)
    {
        resultArray[i] = static_cast<double>(json_array_get_number(jsonArrayObject, i));
    }

    resultArray[size] = -1;

    return resultArray;
}

// -------------------------- MathGeoLib functions --------------------------------

void JsonFile::SetFloat2(const char* key, const float2& value)
{
    JSON_Value* jsonFloat2Value = json_value_init_array();
    JSON_Array* jsonFloat2Array = json_value_get_array(jsonFloat2Value);

    json_array_append_number(jsonFloat2Array, value.x);
    json_array_append_number(jsonFloat2Array, value.y);

    json_object_set_value(rootObject, key, jsonFloat2Value);
}

float2 JsonFile::GetFloat2(const char* key) const
{
    JSON_Value* jsonFloat2Value = json_object_get_value(rootObject, key);

    if (jsonFloat2Value == nullptr || json_value_get_type(jsonFloat2Value) != JSONArray) {

        return float2();
    }

    JSON_Array* jsonFloat2Array = json_value_get_array(jsonFloat2Value);

    if (json_array_get_count(jsonFloat2Array) != 2) {

        return float2(); 
    }

    float2 resultFloat2;
    resultFloat2.x = static_cast<float>(json_array_get_number(jsonFloat2Array, 0));
    resultFloat2.y = static_cast<float>(json_array_get_number(jsonFloat2Array, 1));

    return resultFloat2;
}

void JsonFile::SetFloat3(const char* key, const float3& value)
{
    JSON_Value* jsonFloat3Value = json_value_init_array();
    JSON_Array* jsonFloat3Array = json_value_get_array(jsonFloat3Value);

    json_array_append_number(jsonFloat3Array, value.x);
    json_array_append_number(jsonFloat3Array, value.y);
    json_array_append_number(jsonFloat3Array, value.z);

    json_object_set_value(rootObject, key, jsonFloat3Value);
}

float3 JsonFile::GetFloat3(const char* key) const
{
    JSON_Value* jsonFloat3Value = json_object_get_value(rootObject, key);

    if (jsonFloat3Value == nullptr || json_value_get_type(jsonFloat3Value) != JSONArray) {

        return float3(); 
    }

    JSON_Array* jsonFloat3Array = json_value_get_array(jsonFloat3Value);

    if (json_array_get_count(jsonFloat3Array) != 3) {

        return float3(); 
    }

    float3 resultFloat3;
    resultFloat3.x = static_cast<float>(json_array_get_number(jsonFloat3Array, 0));
    resultFloat3.y = static_cast<float>(json_array_get_number(jsonFloat3Array, 1));
    resultFloat3.z = static_cast<float>(json_array_get_number(jsonFloat3Array, 2));

    return resultFloat3;
}

void JsonFile::SetFloat4(const char* key, const float4& value)
{
    JSON_Value* jsonFloat4Value = json_value_init_array();
    JSON_Array* jsonFloat4Array = json_value_get_array(jsonFloat4Value);

    json_array_append_number(jsonFloat4Array, value.x);
    json_array_append_number(jsonFloat4Array, value.y);
    json_array_append_number(jsonFloat4Array, value.z);
    json_array_append_number(jsonFloat4Array, value.w);

    json_object_set_value(rootObject, key, jsonFloat4Value);
}

float4 JsonFile::GetFloat4(const char* key) const
{
    JSON_Value* jsonFloat4Value = json_object_get_value(rootObject, key);

    if (jsonFloat4Value == nullptr || json_value_get_type(jsonFloat4Value) != JSONArray) {

        return float4(); 
    }

    JSON_Array* jsonFloat4Array = json_value_get_array(jsonFloat4Value);

    if (json_array_get_count(jsonFloat4Array) != 4) {
 
        return float4(); 
    }

    float4 resultFloat4;
    resultFloat4.x = static_cast<float>(json_array_get_number(jsonFloat4Array, 0));
    resultFloat4.y = static_cast<float>(json_array_get_number(jsonFloat4Array, 1));
    resultFloat4.z = static_cast<float>(json_array_get_number(jsonFloat4Array, 2));
    resultFloat4.w = static_cast<float>(json_array_get_number(jsonFloat4Array, 3));

    return resultFloat4;
}

void JsonFile::SetMatrix3x3(const char* key, const float3x3& matrix)
{
    JSON_Value* jsonMatrixValue = json_value_init_array();
    JSON_Array* jsonMatrixArray = json_value_get_array(jsonMatrixValue);

    for (unsigned int i = 0; i < 3; i++) { 

        JSON_Value* jsonRowValue = json_value_init_array();
        JSON_Array* jsonRowArray = json_value_get_array(jsonRowValue);

        for (unsigned int j = 0; j < 3; j++) {

            json_array_append_number(jsonRowArray, matrix[i][j]);

        }

        json_array_append_value(jsonMatrixArray, jsonRowValue);

    }

    json_object_set_value(rootObject, key, jsonMatrixValue);
}

float3x3 JsonFile::GetMatrix3x3(const char* key) const
{
    JSON_Value* jsonMatrixValue = json_object_get_value(rootObject, key);

    if (jsonMatrixValue == nullptr || json_value_get_type(jsonMatrixValue) != JSONArray) {

        return float3x3(); 
    }

    JSON_Array* jsonMatrixArray = json_value_get_array(jsonMatrixValue);

    if (json_array_get_count(jsonMatrixArray) != 3) {

        return float3x3();
    }

    float3x3 resultMatrix;

    for (size_t i = 0; i < 3; i++) {

        JSON_Array* jsonRowArray = json_array_get_array(jsonMatrixArray, i);

        if (json_array_get_count(jsonRowArray) != 3) {

            return float3x3();
        }

        for (size_t j = 0; j < 3; j++) {

            resultMatrix[i][j] = static_cast<float>(json_array_get_number(jsonRowArray, j));

        }

    }

    return resultMatrix;
}

void JsonFile::SetMatrix4x4(const char* key, const float4x4& matrix)
{
    JSON_Value* jsonMatrixValue = json_value_init_array();
    JSON_Array* jsonMatrixArray = json_value_get_array(jsonMatrixValue);

    for (unsigned int i = 0; i < 4; i++) { 

        JSON_Value* jsonRowValue = json_value_init_array();
        JSON_Array* jsonRowArray = json_value_get_array(jsonRowValue);

        for (unsigned int j = 0; j < 4; j++) { 

            json_array_append_number(jsonRowArray, matrix[i][j]);

        }

        json_array_append_value(jsonMatrixArray, jsonRowValue);

    }

    json_object_set_value(rootObject, key, jsonMatrixValue);
}

float4x4 JsonFile::GetMatrix4x4(const char* key) const
{
    JSON_Value* jsonMatrixValue = json_object_get_value(rootObject, key);

    if (jsonMatrixValue == nullptr || json_value_get_type(jsonMatrixValue) != JSONArray) {
   
        return float4x4(); 
    }

    JSON_Array* jsonMatrixArray = json_value_get_array(jsonMatrixValue);

    if (json_array_get_count(jsonMatrixArray) != 4) {
 
        return float4x4(); 
    }

    float4x4 resultMatrix;

    for (size_t i = 0; i < 4; i++) {

        JSON_Array* jsonRowArray = json_array_get_array(jsonMatrixArray, i);

        if (json_array_get_count(jsonRowArray) != 4) {
 
            return float4x4(); 
        }

        for (size_t j = 0; j < 4; j++) {

            resultMatrix[i][j] = static_cast<float>(json_array_get_number(jsonRowArray, j));

        }
    }

    return resultMatrix;
}

void JsonFile::SetQuat(const char* key, const Quat& quaternion)
{
    JSON_Value* jsonQuatValue = json_value_init_array();
    JSON_Array* jsonQuatArray = json_value_get_array(jsonQuatValue);

    json_array_append_number(jsonQuatArray, quaternion.w);
    json_array_append_number(jsonQuatArray, quaternion.x);
    json_array_append_number(jsonQuatArray, quaternion.y);
    json_array_append_number(jsonQuatArray, quaternion.z);

    json_object_set_value(rootObject, key, jsonQuatValue);
}

Quat JsonFile::GetQuat(const char* key) const
{
    JSON_Value* jsonQuatValue = json_object_get_value(rootObject, key);

    if (jsonQuatValue == nullptr || json_value_get_type(jsonQuatValue) != JSONArray) {

        return Quat(); 
    }

    JSON_Array* jsonQuatArray = json_value_get_array(jsonQuatValue);

    if (json_array_get_count(jsonQuatArray) != 4) {

        return Quat();
    }

    Quat resultQuat;
    resultQuat.w = static_cast<float>(json_array_get_number(jsonQuatArray, 0));
    resultQuat.x = static_cast<float>(json_array_get_number(jsonQuatArray, 1));
    resultQuat.y = static_cast<float>(json_array_get_number(jsonQuatArray, 2));
    resultQuat.z = static_cast<float>(json_array_get_number(jsonQuatArray, 3));

    return resultQuat;
}