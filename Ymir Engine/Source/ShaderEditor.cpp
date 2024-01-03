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

	char nameBuffer[256]; // You can adjust the buffer size as needed

	// Copy the current name to the buffer
	strcpy(nameBuffer, shaderFileName.c_str());

	// Create an input text field in your ImGui window
	if (ImGui::InputText(" ", nameBuffer, sizeof(nameBuffer)))
	{
		// The input text has changed, update the name
		shaderFileName = nameBuffer;
	}

	ImGui::Spacing();

	ImGui::Separator();

	ImGui::Spacing();

	if (ImGui::Button("Create Shader"))
	{
		CreateShaderTXT();
	}

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.6f, 0.0f, 1.0f)); // Set button color to green

	if (ImGui::Button("Save Shader"))
	{
		SaveShaderTXT(textEditor.GetText(), shaderFileName);

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
		DeleteShaderTXT(shaderFileName);
	}

	ImGui::PopStyleColor();

	ImGui::Spacing();

	ImGui::Separator();

	ImGui::Spacing();

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

	//pathToRecompile = fullPath;

	// Open the file for writing
	std::ofstream outputFile(fullPath);

	// Check if the file is opened successfully
	if (!outputFile.is_open()) {
		// Handle the error (e.g., print an error message)
		std::cerr << "Error: Unable to open file for writing - " << fullPath << std::endl;
		ret = false;
	}

	// Write the shaderText to the file
	outputFile << shaderText;

	// Close the file
	outputFile.close();

	// Check if the file is closed successfully
	if (!outputFile) {
		// Handle the error (e.g., print an error message)
		std::cerr << "Error: Failed to write content to file - " << fullPath << std::endl;
		ret = false;
	}

	Shader* tmpShader = new Shader();
	tmpShader->LoadShader(fullPath);
	delete tmpShader;

	// Return true if the operation was successful
	return ret;
}

void ShaderEditor::DeleteShaderTXT(std::string fileName)
{
	std::string fullPath = SHADERS_ASSETS_PATH + fileName + ".glsl";

	textEditor.SetText("");
	shaderFileName = "";

	// Use std::filesystem::remove to delete the file
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
