#include "Camera.h"
#include <iostream>
#include "Maths/Matrix.h"

// Create new Camera object, with config and proj matrix objects
Camera::Camera(const Config& config) noexcept
:	m_config	(config) {
	m_projectionMatrix = makeProjectionMatrix(config);

	position = {1, 1, 1}; // set camera position
	//TODO: find out why camera position isn't initializing correctly
}

void Camera::update() noexcept {
	// update camera position and rotation

	position = m_pEntity->position;
	rotation = m_pEntity->rotation;


	m_viewMatrix = makeViewMatrix(*this); // create view matrix (World Coords -> Camera Coords)
	m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix; // create projection view matrix (World Coords -> Homogeneous Coords)

}

void Camera::hookEntity(const Entity& entity) noexcept {
    m_pEntity = &entity; // hook entity
}

const glm::mat4& Camera::getViewMatrix() const noexcept {
	return m_viewMatrix; // view matrix (World Coords -> Camera Coords)
}

const glm::mat4& Camera::getProjectionMatrix() const noexcept {
	return m_projectionMatrix; // projection matrix (Camera Coords -> Homogeneous Coords)
}

const glm::mat4& Camera::getProjectionViewMatrix() const noexcept {
	return m_projectionViewMatrix; // projection view matrix (World Coords -> Homogeneous Coords)
}

