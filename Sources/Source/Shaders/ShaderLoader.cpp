#include "ShaderLoader.h"

#include "../Util/FileUtil.h"

#include <glad.h>
#include <stdexcept>

namespace {
	GLuint compileShader(const GLchar* source, GLenum shaderType) {
		auto shaderID = glCreateShader(shaderType); // create shader object

		glShaderSource(shaderID, 1, &source, nullptr); // specify shader source
		glCompileShader(shaderID); // compile shader

		GLint isSuccess = 0;
		GLchar infoLog[512];

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess); // return shader compile status
		if (!isSuccess) {
			glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
			throw std::runtime_error("Unable to load a shader" + std::string(infoLog));
		}
		return shaderID;
	}

	GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
		auto id = glCreateProgram(); // create program object

		glAttachShader(id, vertexShaderID); // attach vertex shader to program object
		glAttachShader(id, fragmentShaderID); // attach fragment shader to program object

		glLinkProgram(id); // link program object

		return id;
	}
}

GLuint loadShaders(const std::string& vertexShader, const std::string& fragmentShader) {
	auto vertexSource = getFileContents("Shaders/" + vertexShader + ".glsl"); // vertex shader file source
	auto fragmentSource = getFileContents("Shaders/" + fragmentShader + ".glsl"); // fragment shader file source

	auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER); // compile vertex shader
	auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER); // compile fragment shader

	auto shaderID = linkProgram(vertexShaderID, fragmentShaderID); // link fragment and vertex shader programs

	glDeleteShader(vertexShaderID); // delete vertex shader
	glDeleteShader(fragmentShaderID); // delete fragment shader

	return shaderID;
}