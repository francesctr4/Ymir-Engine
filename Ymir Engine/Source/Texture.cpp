#include "Texture.h"
#include "Log.h"

#include "External/DevIL/include/ilu.h"
#include "External/DevIL/include/ilut.h"

#pragma comment( lib, "Source/External/DevIL/libx86/DevIL.lib" )
#pragma comment( lib, "Source/External/DevIL/libx86/ILU.lib" )
#pragma comment( lib, "Source/External/DevIL/libx86/ILUT.lib" )

Texture::Texture()
{
	ID = 0;
}

Texture::Texture(const std::string& path)
{
	ID = 0;

	LoadTexture(path);
}

Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture(const std::string& path)
{
	// 1. Load DevIL Image

	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);

	if (ilLoadImage(path.c_str())) {
		// Image loaded successfully
		LOG("Image loaded successfully at %s", path.c_str());
	}
	else {
		// Error loading the image
		ILenum error = ilGetError();
		LOG("Error in loading image: %s\n", iluErrorString(error));
		return;
	}

	// 2. Convert the Image to OpenGL Texture Format

	if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE)) {
		// Image converted successfully
		LOG("Image converted successfully at %s", path.c_str());
	}
	else {
		// Error converting the image
		ILenum error = ilGetError();
		LOG("Error converting the image: %s\n", iluErrorString(error));
		return;
	}

	// 3. Get Image Data

	ILubyte* imageData = ilGetData();
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);

	ID = ilutGLBindTexImage();

	// 4. Generate OpenGL Texture

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	// 5. Set Texture Parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	// 6. Clean Up

	glBindTexture(GL_TEXTURE_2D, 0);
	ilDeleteImages(1, &imageID);
	
}

void Texture::LoadCheckerImage()
{
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {

		for (int j = 0; j < CHECKERS_WIDTH; j++) {

			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;

			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;

		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);
}

void Texture::BindTexture(bool bind)
{
	if (bind) {

		glBindTexture(GL_TEXTURE_2D, ID);
		textureBinded = true;

	}
	else {

		glBindTexture(GL_TEXTURE_2D, 0);
		textureBinded = false;
	}
}

void Texture::ClearTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);

	if (ID != 0) {
		glDeleteTextures(1, &ID);
		ID = 0;
	}
}

bool Texture::IsLoaded()
{
	return ID;
}
