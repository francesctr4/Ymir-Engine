#ifndef __SHADER_EDITOR__
#define __SHADER_EDITOR__

#include "External/ImGuiTextEditor/include/TextEditor.h"

#include <string>
#include <filesystem>
#include "DefaultShader.h"

#define SHADERS_ASSETS_PATH "Assets/Shaders/"
#define SHADERS_LIBRARY_PATH "Library/Shaders/"

class ShaderEditor {
public:

	// Constructor & Destructor

	ShaderEditor();
	virtual ~ShaderEditor();

	// Main Functionality

	bool Init();
	bool Update();

	void LoadShaderTXT(std::string filePath);

private:

	// Shader File Management

	void CreateShaderTXT();
	bool SaveShaderTXT(std::string shaderText, std::string fileName);
	void DeleteShaderTXT(std::string fileName);

private:

	std::string inputText;
	char inputTextBuff[255] = { "" };

	TextEditor textEditor;
	TextEditor::LanguageDefinition codeLanguage;

	std::string txt = "";

	int txtNum = 0;
	int listLength = 0;

	std::string path = "";
	std::string shaderFileName = "";

	std::string pathToRecompile = "";

};

#endif // __SHADER_EDITOR__
