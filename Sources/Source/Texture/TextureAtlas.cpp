#include "TextureAtlas.h"
#include <array>

TextureAtlas::TextureAtlas(const std::string& textureFilename) {
	sf::Image i;
	// load specified texture from file
	if (!i.loadFromFile("Res/Textures/" + textureFilename + ".png")) {
		throw std::runtime_error("Unable to load image: " + textureFilename);
	}

	loadFromImage(i);

	m_imageSize = 256;
	m_individualTextureSize = 16;
}

std::vector<GLfloat> TextureAtlas::getTexture(const sf::Vector2i& coords) {
	static const GLfloat TEX_PER_ROW = (GLfloat)m_imageSize / (GLfloat)m_individualTextureSize; // textures per row
	static const GLfloat INDV_TEX_SIZE = 1.0f / TEX_PER_ROW; // texture size
	static const GLfloat PIXEL_SIZE = 1.0f / (float)m_imageSize; // pixel size

	GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;
	GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;

    GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;
    GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;

	return { // coords of texture
		xMax, yMax,
		xMin, yMax,
		xMin, yMin,
		xMax, yMin
	};
}