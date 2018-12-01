#include "SkyboxRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Maths/Matrix.h"

SkyboxRenderer::SkyboxRenderer() {
	std::cout << "Loading Skybox..." << std::endl;
	constexpr GLfloat SIZE = 500;

	std::vector<GLfloat> vertexCoords { // vertex coordimates
		// Back
		 SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		 SIZE,  SIZE, -SIZE,

		// Front
		-SIZE, -SIZE, SIZE,
		 SIZE, -SIZE, SIZE,
		 SIZE,  SIZE, SIZE,
		-SIZE,  SIZE, SIZE,

		// Right
		SIZE, -SIZE,  SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE,  SIZE, -SIZE,
		SIZE,  SIZE,  SIZE,

		// Left
		-SIZE, -SIZE, -SIZE, 
		-SIZE, -SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE, SIZE, -SIZE,

		// Top
		-SIZE, SIZE,  SIZE,
		 SIZE, SIZE,  SIZE,
		 SIZE, SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,

		// Bottom
		-SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE
	};

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

    m_skyboxModel.genVAO();
    m_skyboxModel.addVBO(3, vertexCoords);
    m_skyboxModel.addEBO(indices);

    std::vector<std::string> faces {
        "right",
        "left",
        "top",
        "bottom",
        "front",
        "back"
    };
	m_cubeTexture.loadCubemap(faces);
}

void SkyboxRenderer::add() {

}

void SkyboxRenderer::render(const Camera& camera) {
	m_shader.useProgram();
	m_skyboxModel.bindVAO(); // activate VAO
	m_cubeTexture.bindTexture();

	m_shader.loadViewMatrix(camera.getViewMatrix());
	m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
	glDrawElements(GL_TRIANGLES, m_skyboxModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr); // render primitives from array data
	//glDrawArrays(GL_TRIANGLES, 0, m_skyboxModel.getIndicesCount());
	// glDepthMask(GL_TRUE);
}