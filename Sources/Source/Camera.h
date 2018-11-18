#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Maths/glm.h"
#include "Entity.h"
#include "Config.h"

class Camera : public Entity {
	public:
		Camera(const Config& config) noexcept;

		void update() noexcept;
		void hookEntity(const Entity& entity) noexcept;

		const glm::mat4& getViewMatrix() const noexcept;
		const glm::mat4& getProjectionMatrix() const noexcept;
		const glm::mat4& getProjectionViewMatrix() const noexcept;

	private:
		const Entity* m_pEntity;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionViewMatrix;

		Config m_config;
};


#endif // CAMERA_H_INCLUDED