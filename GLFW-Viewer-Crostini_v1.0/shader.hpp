#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

bool isCompiled(GLuint obj)
{
	int success;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
	if(!success)
		return false;

	return true;
}

GLuint VertShader(std::string source)
{
	GLuint vertexShader;
	std::ifstream file;
	file.open(source.c_str());

	if(!file.is_open())
	{
		std::cout << "Couldn't open file " << source << "because it was moved, deleted, or is being used in another process!" << std::endl;
		exit(-1);
	}

	std::string shaderContent, line;
	while(std::getline(file, line))
	{
		shaderContent += line + "\r\n";
	}
	file.close();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* sourceChars = shaderContent.c_str();
	glShaderSource(vertexShader, 1, &sourceChars, NULL);
	glCompileShader(vertexShader);

	if(!isCompiled(vertexShader))
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILE_STATUS: \n" << infoLog << std::endl;
		exit(-1);
	}

	return vertexShader;
}

GLuint FragShader(std::string source)
{
	GLuint fragShader;
	std::ifstream file;
	file.open(source.c_str());

	if(!file.is_open())
	{
		std::cout << "Couldn't open file " << source << " because it was moved, deleted or is being used by another process!" << std::endl;
		exit(-1);
	}

	std::string shaderContent, line;
	while(std::getline(file, line))
	{
		shaderContent += line + "\r\n";
	}
	file.close();

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* sourceChars = shaderContent.c_str();
	glShaderSource(fragShader, 1, &sourceChars, NULL);
	glCompileShader(fragShader);
	if(!isCompiled(fragShader))
	{
		char infoLog[512];
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILE_STATUS: \n" << infoLog << std::endl;
		exit(-1);
	}

	return fragShader;
}

GLuint CreateShader(std::string fragmentSource, std::string vertexSource)
{
	GLuint shader, vertex, fragment;

	std::cout << "Generating vertex shader..." << std::endl;
	vertex = VertShader(vertexSource);
	std::cout << "Generating fragment shader..." << std::endl;
	fragment = FragShader(fragmentSource);
	std:: cout << "Finalizing shader..." << std:: endl;
	shader = glCreateProgram();
	glAttachShader(shader, vertex);
	glAttachShader(shader, fragment);

	glLinkProgram(shader);

	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);

	if(!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_LINK_STATUS: \n" << infoLog << std::endl;
		exit(-1);
	}

	return shader;
}
