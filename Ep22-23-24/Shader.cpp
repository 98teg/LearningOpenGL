#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include "Renderer.hpp"

Shader::Shader(const std::string& filepath_vertex, const std::string& filepath_fragment){
	SetRendererID(0);

	std::string vertexShader = ReadShader(filepath_vertex);
	std::string fragmentShader = ReadShader(filepath_fragment);

	SetRendererID(CreateShader(vertexShader, fragmentShader));
}

Shader::~Shader(){
	GLCall(glDeleteProgram(GetRendererID()));
}

void Shader::Bind() const{
	GLCall(glUseProgram(GetRendererID()));
}

void Shader::Unbind() const{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int v){
	GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3){
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix){
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

std::string Shader::ReadShader(const std::string& filepath){
	std::ifstream stream(filepath);
	std::string shader;

	std::string line;
	while(getline(stream, line)){
		shader = shader + line + '\n';
	}

	return shader;
}

unsigned int Shader::CompileShader(	unsigned int type,
									const std::string &source){
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if(result == GL_FALSE){
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*) alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(	const std::string& vertexShader,
									const std::string& fragmentShader){
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::GetUniformLocation(const std::string& name){
	if(UniformLocationCacheHas(name))
		return UniformLocationCacheGet(name);

	GLCall(int location = glGetUniformLocation(GetRendererID(), name.c_str()));
	if(location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	UniformLocationCacheAdd(name, location);

	return location;
}
