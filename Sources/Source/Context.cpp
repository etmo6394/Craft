#include "Context.h"

#include <glad.h>

Context::Context(const Config& config) {
	// initialize context window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 4;
	settings.minorVersion = 6;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	sf::VideoMode winMode(config.windowX, config.windowY);
	window.create(winMode, "Craft", sf::Style::Close, settings);

	if (!gladLoadGL()) {
        
        exit(-1);
    }

	glViewport(0, 0, window.getSize().x, window.getSize().y);
	glCullFace(GL_BACK);

    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}