#ifndef PLAYINGSTATE_H_INCLUDED
#define PLAYINGSTATE_H_INCLUDED

#include "StateBase.h"
#include "../Player/Player.h"

#include "../World/Chunk/Chunk.h"
#include "../World/World.h"

class StatePlaying : public StateBase {
	public:
		StatePlaying(Application& app, const Config& config);

		void handleEvent(sf::Event e) override;
		void handleInput() override;

		void update(float deltaTime) override;

		void render(RenderMaster& renderer) override;

		void onOpen() override;
		
	private:
		Player m_player;
		World m_world;

		sf::RectangleShape	m_crosshair;
        sf::Texture			m_chTexture;
        sf::Text			m_text;
        sf::Font 			m_font;
};

#endif // PLAYINGSTATE_H_INCLUDED