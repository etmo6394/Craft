#include "CubeTexture.h"

CubeTexture::CubeTexture() {
    std::vector<std::string> faces {
        "right",
        "left",
        "top",
        "bottom",
        "front",
        "back"
    };
    loadCubemap(faces);
}

CubeTexture::~CubeTexture() {
    glDeleteTextures(1, &m_id); // delete texture
}

void CubeTexture::loadCubemap(std::vector<std::string> faces) {
    loadFromFile(faces);
}

void CubeTexture::loadFromFile(std::vector<std::string> faces) {
	// load texture from file
    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
    for (int j = 0; j < faces.size(); j++) {
       sf::Image i;
	   if (!i.loadFromFile("Res/Textures/Skybox/Skybox3/" + faces[j] + ".png")) {
		  throw std::runtime_error("Unable to load CubeTexture: " + faces[j]);
	   }
       glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, 
            0, GL_RGBA, i.getSize().x, i.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr());
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeTexture::bindTexture() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id); // bind named texture to texturing target
}