#include "Shader.h"
#include "Log.h"
#include "Globals.h"

#include "Application.h"
#include "ModuleEditor.h"

std::map<std::string, Shader*> Shader::loadedShaders;

Shader::Shader()
{
	shaderProgram = 0;
	normalMap = false;
	selected = false;
}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	shaderProgram = 0;

	LoadShader(vertexShaderPath, fragmentShaderPath);
}

Shader::~Shader()
{
	ClearShader();
}

void Shader::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	shaderProgram = glCreateProgram();

	if (shaderProgram == 0) {

		LOG("Error creating shader program.");
		return;
	}
	else {

		LOG("Shader program created successfully.");

	}

	std::string vs, fs;

	vs = ReadShaderFile(vertexShaderPath);
	AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	fs = ReadShaderFile(fragmentShaderPath);
	AddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (success == 0) {

		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);

		LOG("Error linking shader program: '%s'\n", errorLog);
		return;
	}
	else {

		LOG("Shader program linked successfully.");

	}

	glValidateProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);

	if (!success) {

		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);

		LOG("Invalid shader program: '%s\n", errorLog);
		return;
	}
	else {

		LOG("Successfully loaded shader.");

	}

}

void Shader::LoadShader(const std::string& shaderFilePath)
{
	path = shaderFilePath;

	shaderProgram = glCreateProgram();

	if (shaderProgram == 0) {

		LOG("Error creating shader program.");
		return;
	}
	else {

		LOG("Shader program created successfully.");

	}

	// Retrieve the shaderString
	std::string shaderString = ReadShaderFile(shaderFilePath);

	ExtractUniformsFromShaderCode(shaderString);

	// Define regex objects to match specific patterns in the shader string
	std::smatch match;

	// Strings to store extracted components of the shader
	std::string version, vertexShaderCode, fragmentShaderCode;

	/* Use regex search to extract the components of the shader and
	store them in the respective strings */

	if (std::regex_search(shaderString, match, versionRegex)) {
		version = match.str();
	}

	if (std::regex_search(shaderString, match, vertexShaderRegex)) {
		vertexShaderCode = match[1];
	}

	if (std::regex_search(shaderString, match, fragmentShaderRegex)) {
		fragmentShaderCode = match[1];
	}

	/* Concatenate the version string with the code string and add the respective
	shader to the shader program using the AddShader function */

	std::string vs = version + vertexShaderCode;
	AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	std::string fs = version + fragmentShaderCode;
	AddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (success == 0) {

		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);

		LOG("Error linking shader program: '%s'\n", errorLog);
		return;
	}
	else {

		LOG("Shader program linked successfully.");

	}

	glValidateProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);

	if (!success) {

		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);

		LOG("Invalid shader program: '%s\n", errorLog);
		return;
	}
	else {

		LOG("Successfully loaded shader.");

	}

	loadedShaders[path] = this;

}

void Shader::LoadShaderFromString(const std::string& shaderString)
{
	shaderProgram = glCreateProgram();

	if (shaderProgram == 0) {

		LOG("Error creating shader program.");
		return;
	}
	else {

		LOG("Shader program created successfully.");

	}

	// Define regex objects to match specific patterns in the shader string
	std::smatch match;

	// Strings to store extracted components of the shader
	std::string version, vertexShaderCode, fragmentShaderCode;

	/* Use regex search to extract the components of the shader and 
	store them in the respective strings */

	if (std::regex_search(shaderString, match, versionRegex)) { 
		version = match.str(); 
	}

	if (std::regex_search(shaderString, match, vertexShaderRegex)) {
		vertexShaderCode = match[1];
	}

	if (std::regex_search(shaderString, match, fragmentShaderRegex)) {
		fragmentShaderCode = match[1];
	}

	/* Concatenate the version string with the code string and add the respective 
	shader to the shader program using the AddShader function */

	std::string vs = version + vertexShaderCode;
	AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	std::string fs = version + fragmentShaderCode;
	AddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (success == 0) {

		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);

		LOG("Error linking shader program: '%s'\n", errorLog);
		return;
	}
	else {

		LOG("Shader program linked successfully.");

	}

	glValidateProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);

	if (!success) {

		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);

		LOG("Invalid shader program: '%s\n", errorLog);
		return;
	}
	else {

		LOG("Successfully loaded shader.");

	}
}

bool Shader::IsValid()
{
	return (shaderProgram != 0);
}

void Shader::UseShader(bool toggle)
{
	if (toggle) {

		glUseProgram(shaderProgram);

	}
	else {

		glUseProgram(0);

	}

	for (size_t i = 0; i < uniforms.size(); i++)
	{
		BindUniform(&uniforms[i]);
	}

}

void Shader::ClearShader()
{
	glUseProgram(0);

	if (shaderProgram != 0) {

		glDeleteProgram(shaderProgram);
		shaderProgram = 0;

		LOG("Successfully cleared shader");

	}

}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::SetMatrix4x4(const std::string& name, float4x4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_TRUE, value.ptr());
}

void Shader::Translate(float3 translation)
{
	this->translation = translation;
}

void Shader::Rotate(float3 rotation)
{
	this->rotation = rotation;
}

void Shader::Scale(float3 scale)
{
	this->scale = scale;
}

void Shader::SetShaderUniforms()
{
	float4x4 projection;
	glGetFloatv(GL_PROJECTION_MATRIX, projection.ptr());
	this->SetMatrix4x4("projection", projection.Transposed()); // Note: Transpose the matrix when passing to shader
	this->projection = projection;

	float4x4 view;
	glGetFloatv(GL_MODELVIEW_MATRIX, view.ptr());
	this->SetMatrix4x4("view", view.Transposed()); // Note: Transpose the matrix when passing to shader
	this->view = view;

	translationMatrix = CreateTranslationMatrix(translation);
	rotationMatrix = CreateRotationMatrix(rotation);
	scaleMatrix = CreateScaleMatrix(scale);

	float4x4 model = float4x4::identity;
	model = model * translationMatrix * rotationMatrix * scaleMatrix;
	this->SetMatrix4x4("model", model);
	this->model = model;

	ToggleNormalMap(normalMap);

	this->SetBool("selected", selected);

	// Water Shader

	this->SetFloat("time", TimeManager::graphicsTimer.ReadSec());
	//this->SetFloat("speed", waterShaderSpeed);

}

void Shader::ToggleNormalMap(bool value)
{
	this->SetBool("displayNormalMap", value);
}

void Shader::AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
	GLuint ShaderObj = glCreateShader(shaderType);

	if (ShaderObj == 0) {

		LOG("Error creating shader type %d\n", shaderType);
		return;
	}

	const GLchar* p[1];
	p[0] = pShaderText;

	GLint Lengths[1];
	Lengths[0] = (GLint)strlen(pShaderText);

	glShaderSource(ShaderObj, 1, p, Lengths);

	glCompileShader(ShaderObj);

	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

	if (!success) {

		GLchar InfoLog[1024];

		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);

		LOG("Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
		return;
	}

	glAttachShader(shaderProgram, ShaderObj);
}

std::string Shader::ReadShaderFile(const std::string& filename) {

	std::ifstream file;

	file.open(filename);

	if (!file.is_open()) {

		LOG("Error: Unable to open file.");

	}

	std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	return fileContents;
}

void Shader::ExtractUniformsFromShaderCode(const std::string& shaderCode)
{
	std::istringstream iss(shaderCode);
	std::string line;

	while (std::getline(iss, line)) {
		std::istringstream lineStream(line);
		std::string token;

		while (lineStream >> token) {
			if (token == "uniform") {
				std::string type, name;
				lineStream >> type >> name;

				// Remove trailing semicolon from the name
				if (!name.empty() && name.back() == ';') {

					name.pop_back();

				}

				// Ignore "time" uniform
				if (name == "time") {
					continue;
				}

				// Extract type and name information and add to the shader

				if (type == "int") {

					this->AddUniform(name, new int(0.5), UniformType::i1, 1);

				}
				else if (type == "float") {

					this->AddUniform(name, new float(0.5), UniformType::f1, 1);

				}

				// You can add more types if necessary, i will just leave support for int and float uniforms.

			}

		}

	}

	// Use std::remove_if along with erase to remove uniforms not present in the shader code
	uniforms.erase(std::remove_if(uniforms.begin(), uniforms.end(),
		[&shaderCode](const auto& uniform) {
			return shaderCode.find(uniform.name) == std::string::npos;
		}),
		uniforms.end());

}

float4x4 Shader::CreateTranslationMatrix(float3 translation)
{
	float4x4 translationMatrix = {

		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1

	};

	return translationMatrix;
}

float4x4 Shader::CreateRotationMatrix(float3 rotation)
{
	Quat rotationQuaternion = Quat::FromEulerXYZ(DEGTORAD * rotation.x, DEGTORAD * rotation.y, DEGTORAD * rotation.z);

	rotationQuaternion.Normalize();

	float4x4 rotationMatrix = rotationQuaternion.ToFloat4x4();

	return rotationMatrix;
}

float4x4 Shader::CreateScaleMatrix(float3 scale)
{
	float4x4 scaleMatrix = {

		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1

	};

	return scaleMatrix;
}

void Shader::AddUniform(std::string name, void* value, UniformType type, int nElements)
{
	// Check if a uniform with the same name already exists
	for (Uniform& existingUniform : uniforms) {
		if (existingUniform.name == name) {
			// Handle the case where the uniform with the same name is found
			// For example, update the existing uniform with the new information
			existingUniform.value = value;
			existingUniform.type = type;
			existingUniform.nElements = nElements;
			return;
		}
	}

	// If no existing uniform with the same name is found, add a new one
	uniforms.push_back(Uniform(name, value, type, nElements));
}

void Shader::DeleteUniform(std::string name)
{
	for (auto& it = uniforms.begin(); it != uniforms.end(); ++it)
	{
		if (it->name == name) {

			uniforms.erase(it);

		}

	}

}

void Shader::BindUniform(Uniform* uniform) 
{
	int uniformLocation = glGetUniformLocation(shaderProgram, uniform->name.c_str());

	switch (uniform->type) {

		case UniformType::f1:

			glUniform1f(uniformLocation, *(GLfloat*)uniform->value);
			break;

		case UniformType::f1v:

			glUniform1fv(uniformLocation, uniform->nElements, (GLfloat*)uniform->value);
			break;

		case UniformType::i1:

			glUniform1i(uniformLocation, *(GLint*)uniform->value);
			break;

		case UniformType::i1v:

			glUniform1iv(uniformLocation, uniform->nElements, (GLint*)uniform->value);
			break;

		case UniformType::f2:

			glUniform2f(uniformLocation, *(GLfloat*)uniform->value, *((GLfloat*)uniform->value + 1));
			break;

		case UniformType::f2v:

			glUniform2fv(uniformLocation, uniform->nElements, (GLfloat*)uniform->value);
			break;

		case UniformType::i2:

			glUniform2i(uniformLocation, *(GLint*)uniform->value, *((GLint*)uniform->value + 1));
			break;

		case UniformType::i2v:

			glUniform2iv(uniformLocation, uniform->nElements, (GLint*)uniform->value);
			break;

		case UniformType::f3:

			glUniform3f(uniformLocation, *(GLfloat*)uniform->value, *((GLfloat*)uniform->value + 1), *((GLfloat*)uniform->value + 2));
			break;

		case UniformType::f3v:

			glUniform3fv(uniformLocation, uniform->nElements, (GLfloat*)uniform->value);
			break;

		case UniformType::i3:

			glUniform3i(uniformLocation, *(GLint*)uniform->value, *((GLint*)uniform->value + 1), *((GLint*)uniform->value + 2));
			break;

		case UniformType::i3v:

			glUniform3iv(uniformLocation, uniform->nElements, (GLint*)uniform->value);
			break;

		case UniformType::f4:

			glUniform4f(uniformLocation, *(GLfloat*)uniform->value, *((GLfloat*)uniform->value + 1), *((GLfloat*)uniform->value + 2), *((GLfloat*)uniform->value + 3));
			break;

		case UniformType::f4v:

			glUniform4fv(uniformLocation, uniform->nElements, (GLfloat*)uniform->value);
			break;

		case UniformType::i4:

			glUniform4i(uniformLocation, *(GLint*)uniform->value, *((GLint*)uniform->value + 1), *((GLint*)uniform->value + 2), *((GLint*)uniform->value + 3));
			break;

		case UniformType::i4v:

			glUniform4iv(uniformLocation, uniform->nElements, (GLint*)uniform->value);
			break;

		case UniformType::f2mat:

			glUniformMatrix2fv(uniformLocation, uniform->nElements, false, (GLfloat*)uniform->value);
			break;

		case UniformType::f3mat:

			glUniformMatrix3fv(uniformLocation, uniform->nElements, false, (GLfloat*)uniform->value);
			break;

		case UniformType::f4mat:

			glUniformMatrix4fv(uniformLocation, uniform->nElements, false, (GLfloat*)uniform->value);
			break;

	}

}

void Shader::SetUniformValue(const std::string& name, const void* newValue) {

	for (Uniform& uniform : uniforms) {
		if (uniform.name == name) {
			// Copy the new value to the existing memory location
			std::memcpy(uniform.value, newValue, GetUniformSize(uniform.type, uniform.nElements));
			return;
		}
	}

	// Handle error if the uniform name is not found
	std::cerr << "Uniform not found: " << name << std::endl;
}

size_t Shader::GetUniformSize(UniformType type, int nElements) {
	// Implement logic to calculate size based on type and elements
	// You may need to adjust this based on your specific needs
	size_t elementSize = 0;
	switch (type) {
	case UniformType::f1:
		elementSize = sizeof(float);
		break;
	case UniformType::f2:
		elementSize = 2 * sizeof(float);
		break;
		// Add cases for other types as needed
	}

	return elementSize * nElements;
}