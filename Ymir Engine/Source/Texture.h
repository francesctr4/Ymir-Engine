#pragma once

#include <string>

#include "Globals.h"

class Texture {

    uint id;
    std::string type;
    std::string path; // With the path we can compare with other textures to not load already loaded textures

};