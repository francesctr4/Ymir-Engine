#pragma once

#include <string>

#include "External/Glew/include/glew.h"
#include "External/SDL/include/SDL_opengl.h"
#include <gl/GL.h>

#include "Globals.h"

#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

class Texture {
public:

    Texture();
    Texture(const std::string& path);
    virtual ~Texture();

    void LoadCheckerImage();
    void LoadTexture(const std::string& path);

    void BindTexture(bool bind);

    void ClearTexture();

public:

    GLuint ID;
    std::string type;
    std::string path; // With the path we can compare with other textures to not load already loaded textures

    uint u;
    uint v;

private:

    GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

};