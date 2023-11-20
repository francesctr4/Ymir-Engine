#pragma once

#include <string>
#include <fstream>

#include "External/Parson/parson.h"

class JsonFile {
public:

    JsonFile();
    JsonFile(std::string route, std::string fileName);

    virtual ~JsonFile();

    void CreateJSON(std::string route, std::string fileName);

    void SetInt(const char* key, int value);
    void SetFloat(const char* key, float value);
    void SetBoolean(const char* key, bool value);
    void SetString(const char* key, const char* string);
    void SetArray(const char* key, const double* values, size_t size);
    //void SetMatrix();

private:

    JSON_Value* rootValue; // Private member to store JSON value
    JSON_Object* rootObject; // Private member to store JSON object

    void InitializeJSON(); // Helper function to initialize JSON object and value

};