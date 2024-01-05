#include "ShaderEditor.h"
#include "Log.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"

ShaderEditor::ShaderEditor()
{
	// Set Text Editor Language for editing the shaders, in this case, we are using GLSL.
	codeLanguage = TextEditor::LanguageDefinition::GLSL();
	textEditor.SetLanguageDefinition(codeLanguage);

	// Initialize Shader File Name
	shaderFileName = "";
}

ShaderEditor::~ShaderEditor()
{

}

bool ShaderEditor::Init()
{
	bool ret = true;

	return ret;
}

bool ShaderEditor::Update()
{
	bool ret = true;

	ImGui::Spacing();

	ImGui::Text("File Name: ");
	ImGui::SameLine();

	// Buffers for handling the input text field
	char nameBuffer[256];
	strcpy(nameBuffer, shaderFileName.c_str());

	// Input text field for the name of the shader file
	if (ImGui::InputText(" ", nameBuffer, sizeof(nameBuffer)))
	{
		// The input text has changed, update the name
		shaderFileName = nameBuffer;
	}

	ImGui::Spacing();

	ImGui::Separator();

	// -------------- Shader Editor Functionality --------------

	ImGui::Spacing();

	if (ImGui::Button("Create Shader"))
	{
		// Creates a new shader on the text editor with the default shader base applied
		CreateShaderTXT();
	}

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.6f, 0.0f, 1.0f)); // Set button color to green

	if (ImGui::Button("Save Shader"))
	{
		// 1. Save the shader file and update the changes in the assets file
		SaveShaderTXT(textEditor.GetText(), shaderFileName);

		// 2. Recompile the shaders
		for (auto it = External->renderer3D->models.begin(); it != External->renderer3D->models.end(); ++it) {

			for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {

				(*jt).loadedShader = false;

			}

		}

	}

	ImGui::PopStyleColor();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.0f, 0.0f, 1.0f)); // Set button color to red

	if (ImGui::Button("Delete Shader"))
	{
		// Delete the shader file from the text editor, the files and the memory
		DeleteShaderTXT(shaderFileName);
	}

	ImGui::PopStyleColor();

	ImGui::Spacing();

	ImGui::Separator();

	ImGui::Spacing();

	// Render the Shader Editor
	textEditor.Render("Shader Editor");

	return ret;
}

void ShaderEditor::CreateShaderTXT()
{
	textEditor.SetText(DefaultShader::Source);
	shaderFileName = "New Shader";
}

bool ShaderEditor::SaveShaderTXT(std::string shaderText, std::string fileName)
{
	bool ret = true;

	std::string fullPath = SHADERS_ASSETS_PATH + fileName + ".glsl";

	// Open the file for writing
	std::ofstream outputFile(fullPath);

	// Check if the file is opened successfully
	if (!outputFile.is_open()) {
		// Handle the error
		LOG("Error: Unable to open file for writing - %s", fullPath.c_str());
		ret = false;
	}

	// Write the shaderText to the file
	outputFile << shaderText;

	// Close the file
	outputFile.close();

	// Check if the file is closed successfully
	if (!outputFile) {
		// Handle the error
		LOG("Error: Failed to write content to file - %s", fullPath.c_str());
		ret = false;
	}

	// Load Shader into memory to be able to be selected on the inspector
	Shader* tmpShader = new Shader();
	tmpShader->LoadShader(fullPath);
	delete tmpShader;

	return ret;
}

void ShaderEditor::DeleteShaderTXT(std::string fileName)
{
	std::string fullPath = SHADERS_ASSETS_PATH + fileName + ".glsl";

	// Reset variables when deleting the current shader
	textEditor.SetText("");
	shaderFileName = "";

	// Using std::filesystem::remove to delete the file
	if (std::filesystem::remove(fullPath))
	{
		// File deletion successful
		LOG("File deleted successfully: %s", fullPath.c_str());
	}
	else
	{
		// File deletion failed
		LOG("Error: Unable to delete file: %s", fullPath.c_str());
	}

	// Use find to locate the element in loadedShaders
	auto it = Shader::loadedShaders.find(fullPath);

	// Erase the shader from memory
	if (it != Shader::loadedShaders.end())
	{
		// Element found, erase it from the map
		Shader::loadedShaders.erase(it);
		LOG("Shader entry removed from loadedShaders: %s", fullPath.c_str());
	}

}

void ShaderEditor::LoadShaderTXT(std::string filePath)
{
	std::ifstream file;

	file.open(filePath);

	if (!file.is_open()) {

		LOG("Error: Unable to open file.");

	}

	std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	// Retrieve the shader file contents for the Shader Editor
	shaderFileName = std::filesystem::path(filePath).stem().string();
	textEditor.SetText(fileContents);
}
