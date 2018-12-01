#include "RenderMaster.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Application.h"
#include "../Context.h"

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Chunk/ChunkSection.h"

void RenderMaster::drawQuad(const glm::vec3& pos) {
	m_quadRenderer.add(pos); // add quad object at position
}

void RenderMaster::drawCube(const glm::vec3& pos) {
	m_cubeRenderer.add(pos); // add cube object at position
}

void RenderMaster::drawChunk(const ChunkSection& chunk) {
	m_chunkRenderer.add(chunk.m_mesh);
}

void RenderMaster::drawGUI(const sf::Drawable& drawable) {
	m_GUIRenderer.add(drawable);
}

void RenderMaster::drawSkybox() {
	m_skyboxRenderer.add();
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera) {
	glClearColor(0.1, 0.5, 1.0, 1.0); // set clear color
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // set bitplane to clear color

    glEnable(GL_DEPTH_TEST); // enable depth comparisons
    glEnable(GL_CULL_FACE);

	m_chunkRenderer.render(camera); // render cube, as viewed by camera
	glDisable(GL_CULL_FACE);
	m_skyboxRenderer.render(camera);
	glEnable(GL_CULL_FACE);
	m_GUIRenderer.render(window);

	window.display(); // display objects on window
}