#include "JsonEncapsule.h"

void JsonEncapsule::CreateJSON(std::string route, std::string fileName)
{
    // JSON parser quick implementation (Parson)

    JSON_Value* root_value = json_value_init_object();
    JSON_Object* root_object = json_value_get_object(root_value);

    json_object_set_string(root_object, "name", "John Doe");
    json_object_set_number(root_object, "age", 30);
    json_object_set_boolean(root_object, "isStudent", false);

    std::string fullRoute = route + fileName;

    FILE* file = fopen(fullRoute.c_str(), "w");
    if (file) {
        char* serialized_json = json_serialize_to_string_pretty(root_value); // Pretty-printed JSON
        if (serialized_json) {
            fprintf(file, "%s\n", serialized_json);
            json_free_serialized_string(serialized_json);
        }
        fclose(file);
    }

    json_value_free(root_value);
}
