#ifndef RENDERMASTER_H_INCLUDED
#define RENDERMASTER_H_INCLUDED

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "GUIRenderer.h"
#include "SkyboxRenderer.h"
#include "../Config.h"

#include <SFML/Graphics.hpp>

class Camera;
class ChunkSection;

class RenderMaster {
	public:
		void drawQuad(const glm::vec3& pos);

		void drawCube(const glm::vec3& pos);

		void drawChunk(const ChunkSection& chunk);

		void drawGUI(const sf::Drawable& drawable);

		void drawSkybox();

		void finishRender(sf::RenderWindow& window, const Camera& camera);

	private:
		QuadRenderer m_quadRenderer;
		CubeRenderer m_cubeRenderer;
		ChunkRenderer m_chunkRenderer;

		GUIRenderer m_GUIRenderer;
		SkyboxRenderer m_skyboxRenderer;
};

#endif // RENDERMASTER_H_INCLUDED