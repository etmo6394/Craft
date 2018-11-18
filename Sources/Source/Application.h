#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <glad.h>

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "States/StateBase.h"
#include "Renderer/RenderMaster.h"
#include "Context.h"
#include "Camera.h"
#include "Player/Player.h"


class Application {
	public:
		Application(const Config& config);

		void runLoop();

		template<typename T, typename... Args>
		void pushState(Args&&... args) {
			m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
			auto& s = m_states.back();
			s->onOpen();
		}

		void popState();

		Camera& getCamera() { return m_camera; }

		Player& getPlayer() { return m_player; }

		const sf::RenderWindow& getWindow() const { return m_context.window; }

		void turnOffMouse();
        void turnOnMouse ();

	private:
		void handleEvents();

		std::vector<std::unique_ptr<StateBase>> m_states;

		Context m_context;
		RenderMaster m_masterRenderer;
		Camera m_camera;
		Player m_player;

		const Config& m_config;

		bool m_isPopState = false;

};

#endif // APPLICATION_H_INCLUDED