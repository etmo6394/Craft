#include "BasicShader.h"

// Create BasicShader object, with shader object
BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile)
:   Shader(vertexFile, fragmentFile) {
    getUniforms(); // find locations of uniform variables
}

void BasicShader::loadProjectionViewMatrix(const glm::mat4& pvMatrix) {
    loadMatrix4(m_locationProjectionViewMatrix, pvMatrix); // load projection view matrix (World Coords -> Homogeneous Coords)
}

void BasicShader::loadModelMatrix(const glm::mat4& matrix) {
    loadMatrix4(m_locationModelMatrix, matrix); // load model matrix (Model Coords -> World Coords)
}

void BasicShader::getUniforms() {
    useProgram(); // install program object (vertex/fragment shaders)
    m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMatrix"); // find location of projviewmatrix uniform variable
    m_locationModelMatrix          = glGetUniformLocation(m_id, "modelMatrix");// find location of modelmatrix uniform variable
}