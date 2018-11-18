#include "CubeRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Maths/Matrix.h"

// Create CubeRenderer object, with specified textures
CubeRenderer::CubeRenderer() 
: m_atlasTest ("Textures") {

	std::vector<GLfloat> vertexCoords { // vertex coordimates
		// Back
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		// Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		// Right
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		// Left
		0, 0, 0, 
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		// Top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		// Bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

	auto top = m_atlasTest.getTexture({0, 0}); // top texture
	auto side = m_atlasTest.getTexture({1, 0}); // side texture
	auto bottom = m_atlasTest.getTexture({2, 0}); // bottom texture

	// specify face texture coordinates
	std::vector<GLfloat> texCoords;
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), top.begin(), top.end());
	texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());

	std::vector<GLuint> indices { // which vertices to connect
		// Back
		0, 1, 2,
		2, 3, 0,

		// Front
		4, 5, 6,
		6, 7, 4,

		// Right
		8, 	9, 10,
		10, 11, 8,

		// Left
		12, 13, 14,
		14, 15, 12,

		// Top
		16, 17, 18,
		18, 19, 16,

		// Bottom
		20, 21, 22,
		22, 23, 20
	};

	m_cubeModel.addData({vertexCoords, texCoords, indices}); // add data to cube model (VAO, VBO, EBO)
}

void CubeRenderer::add(const glm::vec3& position) {
	m_cubes.push_back(position); // add cube object at position
}

void CubeRenderer::render(const Camera& camera) {
	if (m_cubes.empty()) {
        return;
    }
	//glEnable(GL_CULL_FACE);

	m_shader.useProgram(); // install program object (vertex/fragment shaders)
	m_cubeModel.bindVAO(); // activate VAO
	m_atlasTest.bindTexture(); // bind named texture to texturing target

	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix()); // load projection view matrix (World Coords -> Homogeneous Coords)

	for (auto& cube : m_cubes) {
		m_shader.loadModelMatrix(makeModelMatrix({cube, {0, 0, 0}})); // load model matrix (Model Coords -> World Coords)
		glDrawElements(GL_TRIANGLES, m_cubeModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr); // render primitives from array data
	}

	m_cubes.clear(); // clear cube object
}