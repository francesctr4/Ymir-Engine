#include "JsonEncapsule.h"

void JsonEncapsule::Example()
{
    // JSON parser quick implementation (Parson)

    if (PHYSFS_init(NULL) == 0) {
        // Handle initialization error
    }

    // Set the write directory (this is where you can create folders and files)
    if (PHYSFS_setWriteDir("./") == 0) {
        // Handle setting write directory error
        PHYSFS_deinit();
    }

    // Create a folder (directory)
    const char* folderName = "Library";
    if (PHYSFS_mkdir(folderName) == 0) {
        // Handle folder creation error
        // Note: If the folder already exists, PHYSFS_mkdir will return success.
        // You may want to check if the folder already exists before attempting to create it.
        PHYSFS_deinit();
    }

    JSON_Value* root_value = json_value_init_object();
    JSON_Object* root_object = json_value_get_object(root_value);

    json_object_set_string(root_object, "name", "John Doe");
    json_object_set_number(root_object, "age", 30);
    json_object_set_boolean(root_object, "isStudent", false);

    FILE* file = fopen("./Library/output.json", "w");
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
