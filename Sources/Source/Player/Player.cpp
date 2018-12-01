#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player() 
:	Entity	({1000, 100, 1000}, {0, 180, 0}, {0.4, 1.0, 0.4}) {
	std::cout << "Loading Player..." << std::endl;
}

void Player::handleInput(const sf::RenderWindow& window) {
	keyboardInput(); // handle user keyboard input
	mouseInput(window); // handle user mouse input
}

void Player::update(float dt, World& world) {
    velocity += m_acceleration;
    m_acceleration = {0, 0, 0};

    if (godMode) {
    	position += velocity * dt;
    	velocity *= 0.95;
    } else {
		if (!m_isOnGround) {
			velocity.y -= 40 * dt;
		}
		m_isOnGround = false;

		position.x += velocity.x * dt;
		collide(world, {velocity.x, 0, 0}, dt);

		position.y += velocity.y * dt;
		collide(world, {0, velocity.y, 0}, dt);

		position.z += velocity.z * dt;
		collide(world, {0, 0, velocity.z}, dt);

		box.update(position);

		velocity.x *= 0.95f;
		velocity.z *= 0.95f;
	}
}

void Player::keyboardInput() {
	if (godMode) {
		speed = 2.0f; // update speed
	} else {
		speed = 0.1f; // update speed
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // FORWARD
		m_acceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
		m_acceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // BACKWARD
		m_acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
		m_acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // LEFT
		m_acceleration.x += -glm::cos(glm::radians(rotation.y)) * speed;
		m_acceleration.z += -glm::sin(glm::radians(rotation.y)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // RIGHT
		m_acceleration.x += glm::cos(glm::radians(rotation.y)) * speed;
		m_acceleration.z += glm::sin(glm::radians(rotation.y)) * speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // UP
		jump();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { // DOWN
		m_acceleration.y -= speed;
	}

	velocity += m_acceleration; // update velocity
}

void Player::mouseInput(const sf::RenderWindow& window) {
	static auto const BOUND = 80;
	static auto lastMousePosition = sf::Mouse::getPosition(window); // get mouse position
	auto change = sf::Mouse::getPosition() - lastMousePosition; // delta position

	// rotate camera
	rotation.y += change.x * 0.05;
	rotation.x += change.y * 0.05;

	if (rotation.x > BOUND) rotation.x = BOUND;
	else if (rotation.x < -BOUND) rotation.x = -BOUND;

	if (rotation.y > 360) rotation.y = 0;
	else if (rotation.y < 0) rotation.y = 360;

	auto cx = static_cast<int>(window.getSize().x / 2);
	auto cy = static_cast<int>(window.getSize().y / 2);

	sf::Mouse::setPosition({cx, cy}, window);

	lastMousePosition = sf::Mouse::getPosition();
}

void Player::collide(World& world, const glm::vec3& vel, float dt) {
	for (int x = position.x - box.dimensions.x; x < position.x + box.dimensions.x; x++) {
		for (int y = position.y - box.dimensions.y; y < position.y + box.dimensions.y; y++) {
			for (int z = position.z - box.dimensions.z; z < position.z + box.dimensions.z; z++) {
				auto block = world.getBlock(x, y, z);

				if (block != BlockId::Air) {

					if (vel.x > 0) {
						position.x = x - box.dimensions.x;
					}
					if (vel.x < 0) {
						position.x = x + box.dimensions.x + 1;
					}
					if (vel.y > 0) {
						position.y = y - box.dimensions.y;
						velocity.y = 0;
					}
					if (vel.y < 0) {
						position.y = y + box.dimensions.y + 1;
						velocity.y = 0;
						m_isOnGround = true;
					}
					if (vel.z > 0) {
						position.z = z - box.dimensions.z;
					}
					if (vel.z < 0) {
						position.z = z + box.dimensions.z + 1;
					}
				}
			}
		}
	}

}

void Player::jump() {
	if (godMode) {
		m_acceleration.y += speed;
	} else {
		if (m_isOnGround) {
			m_isOnGround = false;
			m_acceleration.y += speed * 50;
		}
	}
}

void Player::toggleGodMode() {
	godMode = !godMode;
}
