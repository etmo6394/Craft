#include "BasicTexture.h"


BasicTexture::BasicTexture(const std::string& file) {
	loadFromFile(file); // load texture from file
}

void BasicTexture::loadFromImage(const sf::Image& i) {
	glGenTextures(1, &m_id); // generate texture name
	glActiveTexture(GL_TEXTURE0); // select active texture
	glBindTexture(GL_TEXTURE_2D, m_id); // bind named texture to texturing target

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr()); // specify 2d texture image

    glGenerateMipmap(GL_TEXTURE_2D); // gen mipmaps (lower resolutions of same image)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); // minify texture - choose mipmap closest to size of tex pixel
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // magnify texture - nearest tex element
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // wrap texture - clamp to edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // wrap texture - clamp to edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1); // highest defined mipmap level

}

void BasicTexture::loadFromFile(const std::string& file) {
	// load texture from file
	sf::Image i;
	if (!i.loadFromFile("Res/Textures/" + file + ".png")) {
		throw std::runtime_error("Unable to load BasicTexture: " + file);
	}

	loadFromImage(i);
}

BasicTexture::~BasicTexture() {
	glDeleteTextures(1, &m_id); // delete texture
}

void BasicTexture::bindTexture() const {
	glBindTexture(GL_TEXTURE_2D, m_id); // bind named texture to texturing target
}