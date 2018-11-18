#include "Application.h"
#include <iostream>
#include "States/PlayingState.h"

// Constuct Application object, with context, camera, and config objects
Application::Application(const Config& config)
:   m_context   (config)
,   m_camera    (config)
,   m_config    (config) 
,	m_player	() {

	pushState<StatePlaying>(*this, config);

}

void Application::runLoop() {

	sf::Clock dtTimer;

	while (m_context.window.isOpen() && !m_states.empty()) {
		auto deltaTime = dtTimer.restart();
		auto& state = *m_states.back();

		state.handleInput();
		state.update(deltaTime.asSeconds());
		m_camera.update(); // update camera

		state.render(m_masterRenderer); // add objects to be rendered
		m_masterRenderer.finishRender(m_context.window, m_camera); // render current state

		handleEvents();
		if (m_isPopState) {
			m_isPopState = false;
			m_states.pop_back();
		}
	}
}

void Application::handleEvents() {
	sf::Event e;
	while(m_context.window.pollEvent(e)) {
		switch(e.type) {
			case sf::Event::Closed:
				m_context.window.close();
				break;

			case sf::Event::KeyPressed:
				switch (e.key.code) {
					case sf::Keyboard::Escape:
						m_context.window.close();
						break;
					case sf::Keyboard::G:
						m_player.toggleGodMode();
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}
}

void Application::popState() {
	m_isPopState = true;
}

void Application::turnOffMouse() {
    m_context.window.setMouseCursorVisible(false);
}

void Application::turnOnMouse() {
    m_context.window.setMouseCursorVisible(true);
}