#include "JsonFile.h"
#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <filesystem>
#include "PhysfsEncapsule.h"
#include "Log.h"
#include "Application.h"
#include "ModuleScene.h"

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

void JsonFile::DeleteJSON(const std::string& route)
{
    // Check if the file exists before attempting to delete
    if (PhysfsEncapsule::FileExists(route))
    {
        // Delete the file
        PhysfsEncapsule::DeleteFilePhysFS(route);

    }
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

// -------------------------- Scene Serialization functions --------------------------------

// ---------- Individual Elements

void JsonFile::SetComponent(const char* key, const Component& component)
{
    JSON_Value* componentValue = json_value_init_object();
    JSON_Object* componentObject = json_value_get_object(componentValue);

    switch (component.ctype)
    {
    case NONE:
        // Handle NONE case (if needed)
        break;

    case TRANSFORM:
        json_object_set_string(componentObject, "Type", "Transform");
        // Additional properties specific to the Transform component can be added here
        break;

    case MESH:
        json_object_set_string(componentObject, "Type", "Mesh");
        // Additional properties specific to the Mesh component can be added here
        break;

    case MATERIAL:
        json_object_set_string(componentObject, "Type", "Material");
        // Additional properties specific to the Material component can be added here
        break;

    case CAMERA:
        json_object_set_string(componentObject, "Type", "Camera");
        // Additional properties specific to the Camera component can be added here
        break;
    }

    // Add the component object to the main object
    json_object_set_value(rootObject, key, componentValue);
}

Component* JsonFile::GetComponent(const char* key) const
{
    JSON_Value* componentValue = json_object_get_value(rootObject, key);

    if (componentValue != nullptr && json_value_get_type(componentValue) == JSONObject) {

        JSON_Object* componentObject = json_value_get_object(componentValue);

        // Create a new Component
        Component* component = new Component();

        // Get common properties
        std::string type = json_object_get_string(componentObject, "Type");

        if (type == "Transform") {

            component->ctype = ComponentType::TRANSFORM;

        }

        if (type == "Mesh") {

            component->ctype = ComponentType::MESH;

        }

        if (type == "Material") {

            component->ctype = ComponentType::MATERIAL;

        }

        if (type == "Camera") {

            component->ctype = ComponentType::CAMERA;

        }       

        return component;
    }

    return nullptr;
}

void JsonFile::SetGameObject(const char* key, const GameObject& gameObject)
{
    JSON_Value* gameObjectValue = json_value_init_object();
    JSON_Object* gameObjectObject = json_value_get_object(gameObjectValue);

    // Set Name

    json_object_set_string(gameObjectObject, "Name", gameObject.name.c_str());

    // Set Position

    //JSON_Value* positionValue = json_value_init_array();
    //JSON_Array* positionArray = json_value_get_array(positionValue);
    //json_array_append_number(positionArray, gameObject.mTransform->translation.x);
    //json_array_append_number(positionArray, gameObject.mTransform->translation.y);
    //json_array_append_number(positionArray, gameObject.mTransform->translation.z);
    //json_object_set_value(gameObjectObject, "Position", positionValue);

    // Set Rotation

    //JSON_Value* rotationValue = json_value_init_array();
    //JSON_Array* rotationArray = json_value_get_array(rotationValue);
    //json_array_append_number(rotationArray, gameObject.mTransform->rotation.x);
    //json_array_append_number(rotationArray, gameObject.mTransform->rotation.y);
    //json_array_append_number(rotationArray, gameObject.mTransform->rotation.z);
    //json_object_set_value(gameObjectObject, "Rotation", rotationValue);

    // Set Scale

    /*JSON_Value* scaleValue = json_value_init_array();
    JSON_Array* scaleArray = json_value_get_array(scaleValue);
    json_array_append_number(scaleArray, gameObject.mTransform->scale.x);
    json_array_append_number(scaleArray, gameObject.mTransform->scale.y);
    json_array_append_number(scaleArray, gameObject.mTransform->scale.z);
    json_object_set_value(gameObjectObject, "Scale", scaleValue);*/

    // Set UID

    json_object_set_number(gameObjectObject, "UID", gameObject.UID);

    // Set Parent UID

    if (gameObject.mParent != nullptr) {

        json_object_set_number(gameObjectObject, "Parent UID", gameObject.mParent->UID);

    }

    // Set Children UID

    std::vector<int> childrenUID;

    for (auto& child : gameObject.mChildren) {

        childrenUID.push_back(child->UID);

    }

    if (!childrenUID.empty()) {

        JSON_Value* childrenValue = json_value_init_array();
        JSON_Array* childrenArray = json_value_get_array(childrenValue);

        for (const auto& childUID : childrenUID) {

            json_array_append_number(childrenArray, childUID);

        }

        json_object_set_value(gameObjectObject, "Children UID", childrenValue);

    }

    // Save Components Info

    JSON_Value* componentsValue = json_value_init_array();
    JSON_Array* componentsArray = json_value_get_array(componentsValue);

    for (const auto& component : gameObject.mComponents) {

        JSON_Value* componentValue = json_value_init_object();
        JSON_Object* componentObject = json_value_get_object(componentValue);

        // Call the existing SetGameObject function to set individual GameObject properties
        SetComponent(componentObject, *component);

        // Add the GameObject to the hierarchy array
        json_array_append_value(componentsArray, componentValue);
    }

    // Add the hierarchy array to the main object
    json_object_set_value(gameObjectObject, "Components", componentsValue);

    // Add the GameObject to the main array
    json_object_set_value(rootObject, key, gameObjectValue);
}

GameObject* JsonFile::GetGameObject(const char* key) const
{
    JSON_Value* gameObjectValue = json_object_get_value(rootObject, key);

    if (gameObjectValue != nullptr && json_value_get_type(gameObjectValue) == JSONObject) {
        JSON_Object* gameObjectObject = json_value_get_object(gameObjectValue);

        // Create a new GameObject
        GameObject* gameObject = new GameObject();

        // Get Name
        const char* name = json_object_get_string(gameObjectObject, "Name");
        gameObject->name = (name != nullptr) ? name : "";

        // Get UID
        gameObject->UID = static_cast<int>(json_object_get_number(gameObjectObject, "UID"));

        // Get Parent UID
        if (json_object_has_value_of_type(gameObjectObject, "Parent UID", JSONNumber)) {
            gameObject->mParent->UID = static_cast<int>(json_object_get_number(gameObjectObject, "Parent UID"));
        }

        // Get Children UID
        if (json_object_has_value_of_type(gameObjectObject, "Children UID", JSONArray)) {
            JSON_Array* childrenArray = json_object_get_array(gameObjectObject, "Children UID");
            size_t numChildren = json_array_get_count(childrenArray);

            for (size_t i = 0; i < numChildren; ++i) {
                int childUID = static_cast<int>(json_array_get_number(childrenArray, i));
                // You need to find the corresponding child GameObject using the UID
                // and add it to gameObject->mChildren.
                // Assuming you have a function like FindGameObjectByUID, implement it accordingly.
                //gameObject->mChildren.push_back(FindGameObjectByUID(childUID));
            }

        }

        // Get Components
        if (json_object_has_value_of_type(gameObjectObject, "Components", JSONArray)) {
            JSON_Array* componentsArray = json_object_get_array(gameObjectObject, "Components");
            size_t numComponents = json_array_get_count(componentsArray);

            for (size_t i = 0; i < numComponents; ++i) {
                JSON_Value* componentValue = json_array_get_value(componentsArray, i);

                if (json_value_get_type(componentValue) == JSONObject) {
                    JSON_Object* componentObject = json_value_get_object(componentValue);

                    // Create a new Component
                    Component* component = new Component();

                    // Call the existing GetComponent function to retrieve individual Component properties
                    GetComponent(componentObject, *component);

                    // Add the Component to the GameObject's components vector
                    gameObject->mComponents.push_back(component);
                }
            }
        }

        return gameObject;
    }

    return nullptr;
}

// ---------- Save Scene 

void JsonFile::SetHierarchy(const char* key, const std::vector<GameObject*>& gameObjects)
{
    JSON_Value* hierarchyValue = json_value_init_array();
    JSON_Array* hierarchyArray = json_value_get_array(hierarchyValue);

    for (const auto& gameObject : gameObjects) {

        JSON_Value* gameObjectValue = json_value_init_object();
        JSON_Object* gameObjectObject = json_value_get_object(gameObjectValue);

        // Call the existing SetGameObject function to set individual GameObject properties
        SetGameObject(gameObjectObject, *gameObject);

        // Add the GameObject to the hierarchy array
        json_array_append_value(hierarchyArray, gameObjectValue);
    }

    // Add the hierarchy array to the main object
    json_object_set_value(rootObject, key, hierarchyValue);
}

void JsonFile::SetGameObject(JSON_Object* gameObjectObject, const GameObject& gameObject)
{
    // Set Name
    json_object_set_string(gameObjectObject, "Name", gameObject.name.c_str());

    // Set Position
    //JSON_Value* positionValue = json_value_init_array();
    //JSON_Array* positionArray = json_value_get_array(positionValue);
    //json_array_append_number(positionArray, gameObject.mTransform->translation.x);
    //json_array_append_number(positionArray, gameObject.mTransform->translation.y);
    //json_array_append_number(positionArray, gameObject.mTransform->translation.z);
    //json_object_set_value(gameObjectObject, "Position", positionValue);

    // Set Rotation
    //JSON_Value* rotationValue = json_value_init_array();
    //JSON_Array* rotationArray = json_value_get_array(rotationValue);
    //json_array_append_number(rotationArray, gameObject.mTransform->rotation.x);
    //json_array_append_number(rotationArray, gameObject.mTransform->rotation.y);
    //json_array_append_number(rotationArray, gameObject.mTransform->rotation.z);
    //json_object_set_value(gameObjectObject, "Rotation", rotationValue);

    // Set Scale
    //JSON_Value* scaleValue = json_value_init_array();
    //JSON_Array* scaleArray = json_value_get_array(scaleValue);
    //json_array_append_number(scaleArray, gameObject.mTransform->scale.x);
    //json_array_append_number(scaleArray, gameObject.mTransform->scale.y);
    //json_array_append_number(scaleArray, gameObject.mTransform->scale.z);
    //json_object_set_value(gameObjectObject, "Scale", scaleValue);

    // Set UID
    json_object_set_number(gameObjectObject, "UID", gameObject.UID);

    // Set Parent UID
    if (gameObject.mParent != nullptr) {
        json_object_set_number(gameObjectObject, "Parent UID", gameObject.mParent->UID);
    }

    // Set Children UID
    std::vector<int> childrenUID;
    for (const auto& child : gameObject.mChildren) {
        childrenUID.push_back(child->UID);
    }

    if (!childrenUID.empty()) {
        JSON_Value* childrenValue = json_value_init_array();
        JSON_Array* childrenArray = json_value_get_array(childrenValue);

        for (const auto& childUID : childrenUID) {
            json_array_append_number(childrenArray, childUID);
        }

        json_object_set_value(gameObjectObject, "Children UID", childrenValue);
    }

    // Save Components Info

    JSON_Value* componentsValue = json_value_init_array();
    JSON_Array* componentsArray = json_value_get_array(componentsValue);

    for (const auto& component : gameObject.mComponents) {

        JSON_Value* componentValue = json_value_init_object();
        JSON_Object* componentObject = json_value_get_object(componentValue);

        // Call the existing SetGameObject function to set individual GameObject properties
        SetComponent(componentObject, *component);

        // Add the GameObject to the hierarchy array
        json_array_append_value(componentsArray, componentValue);
    }

    // Add the hierarchy array to the main object
    json_object_set_value(gameObjectObject, "Components", componentsValue);

}

void JsonFile::SetComponent(JSON_Object* componentObject, const Component& component)
{
    if (component.ctype == ComponentType::NONE) {

        // Handle NONE case (if needed)

    }
    else if (component.ctype == ComponentType::TRANSFORM) {

        json_object_set_string(componentObject, "Type", "Transform");

        CTransform* ctransform = (CTransform*)&component;

        json_object_set_number(componentObject, "Active", ctransform->active);

        // Translation

        JSON_Value* translationArrayValue = json_value_init_array();
        JSON_Array* translationArray = json_value_get_array(translationArrayValue);

        json_array_append_number(translationArray, ctransform->translation.x);
        json_array_append_number(translationArray, ctransform->translation.y);
        json_array_append_number(translationArray, ctransform->translation.z);

        json_object_set_value(componentObject, "Translation", translationArrayValue);

        // Rotation

        JSON_Value* rotationArrayValue = json_value_init_array();
        JSON_Array* rotationArray = json_value_get_array(rotationArrayValue);

        json_array_append_number(rotationArray, ctransform->rotation.x);
        json_array_append_number(rotationArray, ctransform->rotation.y);
        json_array_append_number(rotationArray, ctransform->rotation.z);

        json_object_set_value(componentObject, "Rotation", rotationArrayValue);

        // Scale

        JSON_Value* scaleArrayValue = json_value_init_array();
        JSON_Array* scaleArray = json_value_get_array(scaleArrayValue);

        json_array_append_number(scaleArray, ctransform->scale.x);
        json_array_append_number(scaleArray, ctransform->scale.y);
        json_array_append_number(scaleArray, ctransform->scale.z);

        json_object_set_value(componentObject, "Scale", scaleArrayValue);

    }
    else if (component.ctype == ComponentType::MESH) {

        json_object_set_string(componentObject, "Type", "Mesh");

        CMesh* cmesh = (CMesh*)&component;

        json_object_set_number(componentObject, "Active", cmesh->active);
        
        json_object_set_number(componentObject, "Vertex Count", cmesh->nVertices);
        json_object_set_number(componentObject, "Index Count", cmesh->nIndices);

    }
    else if (component.ctype == ComponentType::MATERIAL) {

        json_object_set_string(componentObject, "Type", "Material");

        CMaterial* cmaterial = (CMaterial*)&component;

        json_object_set_number(componentObject, "Active", cmaterial->active);

    }
    else if (component.ctype == ComponentType::CAMERA) {

        json_object_set_string(componentObject, "Type", "Camera");

        CCamera* ccamera = (CCamera*)&component;

        json_object_set_number(componentObject, "Active", ccamera->active);

        // Right

        JSON_Value* rightArrayValue = json_value_init_array();
        JSON_Array* rightArray = json_value_get_array(rightArrayValue);

        json_array_append_number(rightArray, ccamera->GetRight().x);
        json_array_append_number(rightArray, ccamera->GetRight().y);
        json_array_append_number(rightArray, ccamera->GetRight().z);

        json_object_set_value(componentObject, "Right", rightArrayValue);

        // Up

        JSON_Value* upArrayValue = json_value_init_array();
        JSON_Array* upArray = json_value_get_array(upArrayValue);

        json_array_append_number(upArray, ccamera->GetUp().x);
        json_array_append_number(upArray, ccamera->GetUp().y);
        json_array_append_number(upArray, ccamera->GetUp().z);

        json_object_set_value(componentObject, "Up", upArrayValue);

        // Front

        JSON_Value* frontArrayValue = json_value_init_array();
        JSON_Array* frontArray = json_value_get_array(frontArrayValue);

        json_array_append_number(frontArray, ccamera->GetFront().x);
        json_array_append_number(frontArray, ccamera->GetFront().y);
        json_array_append_number(frontArray, ccamera->GetFront().z);

        json_object_set_value(componentObject, "Front", frontArrayValue);

        // FOV

        json_object_set_number(componentObject, "FOV", ccamera->GetVerticalFOV());

        // Near Plane

        json_object_set_number(componentObject, "Near Plane", ccamera->GetNearPlane());

        // Far Plane

        json_object_set_number(componentObject, "Far Plane", ccamera->GetFarPlane());

        // Enable/Disable Frustum Culling

        json_object_set_number(componentObject, "Frustum Culling", ccamera->enableFrustumCulling);

        // Enable/Disable Bounding Boxes

        json_object_set_number(componentObject, "Draw Bounding Boxes", ccamera->drawBoundingBoxes);

    }

}

// ---------- Load Scene

std::vector<GameObject*> JsonFile::GetHierarchy(const char* key) const
{
    std::vector<GameObject*> gameObjects;

    JSON_Value* hierarchyValue = json_object_get_value(rootObject, key);

    if (hierarchyValue != nullptr && json_value_get_type(hierarchyValue) == JSONArray) {

        JSON_Array* hierarchyArray = json_value_get_array(hierarchyValue);

        size_t numGameObjects = json_array_get_count(hierarchyArray);

        gameObjects.reserve(numGameObjects);

        for (size_t i = 0; i < numGameObjects; ++i) {

            JSON_Value* gameObjectValue = json_array_get_value(hierarchyArray, i);

            if (json_value_get_type(gameObjectValue) == JSONObject) {

                JSON_Object* gameObjectObject = json_value_get_object(gameObjectValue);

                // Create a new GameObject
                GameObject* gameObject = new GameObject();

                // Call a function to extract individual GameObject properties
                GetGameObject(gameObjects, gameObjectObject, *gameObject);

                // Add the GameObject to the vector
                gameObjects.push_back(gameObject);

            }

        }

    }

    return gameObjects;
}

void JsonFile::GetGameObject(const std::vector<GameObject*>& gameObjects, const JSON_Object* gameObjectObject, GameObject& gameObject) const
{
    // Get Name

    const char* name = json_object_get_string(gameObjectObject, "Name");
    gameObject.name = (name != nullptr) ? name : "";

    // Get Position, Rotation, Scale (TODO)

    // Get UID

    gameObject.UID = json_object_get_number(gameObjectObject, "UID");

    // Get Parent UID

    if (json_object_has_value_of_type(gameObjectObject, "Parent UID", JSONNumber)) {

        int parentUID = static_cast<int>(json_object_get_number(gameObjectObject, "Parent UID"));

        // You need to find the corresponding parent GameObject using the UID
        // and set it to gameObject.mParent.

        GameObject* parent = GameObject::GetGameObjectFromUID(gameObjects, parentUID);
        gameObject.SetParent(parent);

    }

    // Get Children UID

    if (json_object_has_value_of_type(gameObjectObject, "Children UID", JSONArray)) {

        JSON_Array* childrenArray = json_object_get_array(gameObjectObject, "Children UID");

        size_t numChildren = json_array_get_count(childrenArray);

        gameObject.mChildren.reserve(numChildren);

        for (size_t i = 0; i < numChildren; ++i) {

            int childUID = static_cast<int>(json_array_get_number(childrenArray, i));
            // You need to find the corresponding child GameObject using the UID
            // and add it to gameObject.mChildren.
            GameObject* childGO = new GameObject();
            childGO->UID = childUID;
            gameObject.mChildren.push_back(childGO);

        }

    }

    // Get Components Info

    if (json_object_has_value_of_type(gameObjectObject, "Components", JSONArray)) {

        JSON_Array* componentsArray = json_object_get_array(gameObjectObject, "Components");
        size_t numComponents = json_array_get_count(componentsArray);

        for (size_t i = 0; i < numComponents; ++i) {

            JSON_Value* componentValue = json_array_get_value(componentsArray, i);

            if (json_value_get_type(componentValue) == JSONObject) {

                JSON_Object* componentObject = json_value_get_object(componentValue);

                // Create a new Component
                Component* component = new Component();

                // Call the existing GetComponent function to extract individual Component properties
                GetComponent(componentObject, *component);

                // Add the Component to the GameObject's components vector
                gameObject.mComponents.push_back(component);

            }

        }

    }

}

void JsonFile::GetComponent(const JSON_Object* componentObject, Component& component) const {

    // Get common properties
    std::string type = json_object_get_string(componentObject, "Type");

    if (type == "Transform") {

        component.ctype = ComponentType::TRANSFORM;

    }
    else if (type == "Mesh") {

        component.ctype = ComponentType::MESH;

    }
    else if (type == "Material") {

        component.ctype = ComponentType::MATERIAL;

    }
    else if (type == "Camera") {

        component.ctype = ComponentType::CAMERA;

    }

}