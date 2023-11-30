#pragma once

#include <string>

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>

#include "Globals.h"

#include "External/DevIL/include/ilu.h"
#include "External/DevIL/include/ilut.h"

#pragma comment( lib, "Source/External/DevIL/libx86/DevIL.lib" )
#pragma comment( lib, "Source/External/DevIL/libx86/ILU.lib" )
#pragma comment( lib, "Source/External/DevIL/libx86/ILUT.lib" )

#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

enum class TextureTypes {

    NONE = -1,
    DIFFUSE,
    SPECULAR,
    AMBIENT,
    EMISSIVE,
    HEIGHT,
    NORMALS,
    SHININESS,
    OPACITY,
    DISPLACEMENT,
    LIGHTMAP,
    REFLECTION,
    UNKNOWN

};

class Texture {
public:

    Texture();
    Texture(const std::string& path);
    virtual ~Texture();

    void LoadCheckerImage();
    void LoadTexture(const std::string& path);

    void BindTexture(bool bind);

    void ClearTexture();

    bool IsLoaded();

public:

    GLuint ID;

    uint UID;

    std::string path; // With the path we can compare with other textures to not load already loaded textures
    TextureTypes type;

    //uint width; 
    //uint height; 

private:

    GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
    bool textureBinded = false;

};