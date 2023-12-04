#pragma once

#include "Resources.h"

#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

enum class TextureType {

    UNKNOWN = -1,   // NULL Type

    DIFFUSE,
    SPECULAR,
    AMBIENT,
    EMISSIVE,
    HEIGHT,
    NORMAL,
    SHININESS,
    OPACITY,
    DISPLACEMENT,
    LIGHTMAP,
    REFLECTION,

    NUM_TYPES       // Total Quantity of Types

};

class ResourceTexture : public Resource {
public:

	ResourceTexture(uint UID);

	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

private:

    GLuint ID;
    
    TextureType type;

    uint width; 
    uint height; 

    GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

};