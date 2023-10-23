#include "Shader.h"
#include "Log.h"
#include "Globals.h"

Shader::Shader()
{
	shaderProgram = 0;
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

void Shader::UseShader(bool toggle)
{
	if (toggle) {

		glUseProgram(shaderProgram);

	}
	else {

		glUseProgram(0);

	}
}

void Shader::ClearShader()
{
	glUseProgram(0);

	if (shaderProgram != 0) {

		glDeleteProgram(shaderProgram);
		shaderProgram = 0;

	}

	LOG("Successfully cleared shader");
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

void Shader::SetShaderUniforms()
{
	float4x4 projection;
	glGetFloatv(GL_PROJECTION_MATRIX, projection.ptr());
	this->SetMatrix4x4("projection", projection.Transposed()); // Note: Transpose the matrix when passing to shader

	float4x4 view;
	glGetFloatv(GL_MODELVIEW_MATRIX, view.ptr());
	this->SetMatrix4x4("view", view.Transposed()); // Note: Transpose the matrix when passing to shader

	float3 translate(0,0,0);

	float4x4 translationMatrix = {

		1, 0, 0, translate.x,
		0, 1, 0, translate.y,
		0, 0, 1, translate.z,
		0, 0, 0, 1

	};

	float3 Xaxis(1, 0, 0);
	float3 Yaxis(0, 1, 0);
	float3 Zaxis(0, 0, 1);
	
	float angle = PI / 2.0f;

	Quat q(Xaxis,angle);
	float4x4 rotationMatrix = q.ToFloat4x4();

	float3 scale(1,1,1);

	float4x4 scaleMatrix = {

		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1

	};

	float4x4 model = float4x4::identity;
	model = model * translationMatrix * rotationMatrix * scaleMatrix;
	this->SetMatrix4x4("model", model);

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

float4x4 Shader::CreateRotationMatrix(Quat rotation)
{



	return float4x4();
}

float4x4 Shader::CreateScaleMatrix(float3 scale)
{



	return float4x4();
}
