#include "Shader.h"
#include "Log.h"

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

}

void Shader::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	shaderProgram = glCreateProgram();

	if (shaderProgram == 0) {

		LOG("Error creating shader program.");

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

	glValidateProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);

	if (!success) {

		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);

		LOG("Invalid shader program: '%s\n", errorLog);
		return;
	}

	LOG("Successfully loaded shader");
}

void Shader::UseShader()
{
	glUseProgram(shaderProgram);

	LOG("Successfully using shader");
}

void Shader::ClearShader()
{
	glUseProgram(0);
	glDeleteProgram(shaderProgram);

	LOG("Successfully cleared shader");
}

//void Shader::SetBool(const std::string& name, bool value) const
//{
//	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
//}
//
//void Shader::SetInt(const std::string& name, int value) const
//{
//	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
//}
//
//void Shader::SetFloat(const std::string& name, float value) const
//{
//	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
//}

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