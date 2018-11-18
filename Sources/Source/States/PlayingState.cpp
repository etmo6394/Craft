#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"
#include "../Application.h"

#include <iostream>

// Create StatePlaying object, with StateBase object
StatePlaying::StatePlaying(Application& app, const Config& config)
:	StateBase	(app) 
,	m_world		(app.getCamera(), app.getPlayer()) {
	app.getCamera().hookEntity(app.getPlayer()); // link camera to player

	m_chTexture.loadFromFile("Res/Textures/ch.png");
	m_crosshair.setTexture(&m_chTexture);
	m_crosshair.setSize({21, 21});
	m_crosshair.setOrigin(m_crosshair.getGlobalBounds().width / 2, m_crosshair.getGlobalBounds().height / 2);
	m_crosshair.setPosition(app.getWindow().getSize().x / 2, app.getWindow().getSize().y / 2);

	if (!m_font.loadFromFile("Res/Fonts/SFPixelate.ttf")) {
		throw std::runtime_error("Unable to load font");
	}
	m_text.move(10, 10);
	m_text.setFont(m_font);

	m_text.setCharacterSize(25);
	m_text.setFillColor(sf::Color::Black);
	//m_text.setPosition(app.getWindow().getSize().x / 4, app.getWindow().getSize().y / 4);
}

void StatePlaying::handleEvent(sf::Event e) {

}

void StatePlaying::handleInput() {
	m_pApplication->getPlayer().handleInput(m_pApplication->getWindow()); // handle user keyboard/mouse input
}

void StatePlaying::update(float deltaTime) {
	m_text.setString("X: " + std::to_string((int)m_pApplication->getPlayer().position.x) + "\nY: " + std::to_string((int)m_pApplication->getPlayer().position.y) + "\nZ: " + std::to_string((int)m_pApplication->getPlayer().position.z));
	m_pApplication->getPlayer().update(deltaTime, m_world); // update player pos/vel
	m_world.update(m_pApplication->getCamera(), m_pApplication->getPlayer());
}

void StatePlaying::render(RenderMaster& renderer) {
	renderer.drawGUI(m_crosshair);
	renderer.drawGUI(m_text);
	m_world.renderWorld(renderer, m_pApplication->getCamera());
}

void StatePlaying::onOpen() {
	m_pApplication->turnOffMouse();
}