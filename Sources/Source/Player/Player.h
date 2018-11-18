#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include <SFML/Graphics.hpp>
#include <vector>

#include "../World/World.h"
#include "../Entity.h"

class World;

class Player : public Entity {
	public:
		Player();

		void handleInput(const sf::RenderWindow& window);

		void update(float dt, World& world);

		void collide(World& world, const glm::vec3& vel, float dt);

		void jump();

		void toggleGodMode();

	private:
		void keyboardInput();
		void mouseInput(const sf::RenderWindow& window);

		glm::vec3 m_acceleration;
		float speed;

		bool m_isOnGround = false;
		bool godMode = false;
};

#endif // PLAYER_H_DEFINED