#include "Shader.h"
#include "ShaderLoader.h"

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile) 
:		m_id		(loadShaders(vertexFile, fragmentFile)) {
	useProgram(); // install program object (vertex/fragment shaders)
}

void Shader::loadInt(GLuint location, int value) {
    glUniform1i(location, value); // specify the value of a uniform variable for the current program object
}

void Shader::loadFloat(GLuint location, float value) {
    glUniform1f(location, value);// specify the value of a uniform variable for the current program object
}

void Shader::loadVector2(GLuint location, const glm::vec2& vect) {
    glUniform2f(location, vect.x, vect.y);// specify the value of a uniform variable for the current program object
}

void Shader::loadVector3(GLuint location, const glm::vec3& vect) {
    glUniform3f(location, vect.x, vect.y, vect.z);// specify the value of a uniform variable for the current program object
}

void Shader::loadVector4(GLuint location, const glm::vec4& vect) {
    glUniform4f(location, vect.x, vect.y, vect.z, vect.w);// specify the value of a uniform variable for the current program object
}

void Shader::loadMatrix4(GLuint location, const glm::mat4& matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));// specify the value of a uniform variable for the current program object
}

Shader::~Shader() {
	glDeleteProgram(m_id); // delete program object
}

void Shader::useProgram() const {
	glUseProgram(m_id); // install program object (vertex/fragment shaders)
}