#include "JsonFile.h"
#include <vector>

JsonFile::JsonFile()
{
    rootValue = nullptr;
    rootObject = nullptr; 
}

JsonFile::JsonFile(std::string route, std::string fileName)
{
    CreateJSON(route, fileName);
}

JsonFile::~JsonFile()
{

}

void JsonFile::CreateJSON(std::string route, std::string fileName)
{
    // JSON parser quick implementation (Parson)

    InitializeJSON();

    SetString("name", "John Doe");
    SetInt("age", 30);
    SetBoolean("isStudent", true);
    std::vector<double> aa = { 2,3,4 };
    SetArray("array",aa.data(), aa.size());

    std::string fullRoute = route + fileName;

    FILE* file = fopen(fullRoute.c_str(), "w");
    if (file) {
        char* serialized_json = json_serialize_to_string_pretty(rootValue); // Pretty-printed JSON
        if (serialized_json) {
            fprintf(file, "%s\n", serialized_json);
            json_free_serialized_string(serialized_json);
        }
        fclose(file);
    }

    json_value_free(rootValue);
}

void JsonFile::SetInt(const char* key, int value) {

    json_object_set_number(rootObject, key, (int)value);

}

void JsonFile::SetFloat(const char* key, float value) {

    json_object_set_number(rootObject, key, (float)value);

}

void JsonFile::SetBoolean(const char* key, bool value) {

    json_object_set_boolean(rootObject, key, (bool)value);

}

void JsonFile::SetArray(const char* key, const double* values, size_t size) {

    JSON_Value* jsonArrayValue = json_value_init_array();
    JSON_Array* jsonArrayObject = json_value_get_array(jsonArrayValue);

    for (unsigned int i = 0; i < size; i++)
    {
        json_array_append_number(jsonArrayObject, values[i]);
    }

    json_object_set_value(rootObject, key, jsonArrayValue);

}

void JsonFile::SetString(const char* key, const char* string) {

    json_object_set_string(rootObject, key, string);

}

void JsonFile::InitializeJSON()
{
    rootValue = json_value_init_object();
    rootObject = json_value_get_object(rootValue);
}
