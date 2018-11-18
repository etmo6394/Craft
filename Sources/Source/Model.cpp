#include "Model.h"

Model::Model(const Mesh& mesh) {
	addData(mesh); // add vert/tex/ind data to model
}

Model::~Model() {
	deleteData(); // delete data from model
}

Model::Model(Model&& other)
:   m_vao           (other.m_vao)
,   m_vboCount      (other.m_vboCount)
,   m_indicesCount  (other.m_indicesCount)
,   m_buffers       (std::move(other.m_buffers)) {
    other.m_vao             = 0;
    other.m_vboCount        = 0;
    other.m_indicesCount    = 0;
}

Model& Model::operator=(Model&& other) {
    m_vao = other.m_vao;
    m_vboCount = other.m_vboCount;
    m_indicesCount = other.m_indicesCount;
    m_buffers = std::move(other.m_buffers);
    other.m_vao             = 0;
    other.m_vboCount        = 0;
    other.m_indicesCount    = 0;
    return *this;
}

void Model::bindVAO() const {
	glBindVertexArray(m_vao); // activate VAO
}

void Model::addData(const Mesh& mesh) {
	if (m_vao != 0) // Vertex Array Object (which VBO connected to which attrib)
		deleteData();

	m_indicesCount = mesh.indices.size();

	glGenVertexArrays(1, &m_vao); // create new VAO
	glBindVertexArray(m_vao); // activate VAO

	addVBO(3, mesh.vertexPositions); // add VBO vert pos
	addVBO(2, mesh.textureCoords); // add VBO tex coords
	addEBO(mesh.indices); // add EBO ind
}

void Model::addVBO(int dimensions, const std::vector<GLfloat>& data) {
	GLuint vbo; // Vertex Buffer Object (vertices for use in vertex shader)
	glGenBuffers(1, &vbo); // generate name for new buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // activate buffer
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW); // upload data to buffer

	glVertexAttribPointer(static_cast<GLuint>(m_vboCount), dimensions, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0); // define array of vertex attrib data
	glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount++)); // enable vertex attribute

	m_buffers.push_back(vbo); // attach buffer to active array
}

void Model::addEBO(const std::vector<GLuint>& indices) {
	GLuint ebo; // Element Buffer Object (source of ind during rendering)
	glGenBuffers(1, &ebo); // generate name for new buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); // activate buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW); // upload data to buffer
}

void Model::deleteData() {
	glDeleteVertexArrays(1, &m_vao); // delete vert arrays
	glDeleteBuffers(static_cast<GLsizei>(m_buffers.size()), m_buffers.data()); // delete buffers

	m_buffers.clear(); // clear buffers

	m_vboCount = 0;
	m_vao = 0;
	m_indicesCount = 0;
}

int Model::getIndicesCount() const {
	return m_indicesCount;
}