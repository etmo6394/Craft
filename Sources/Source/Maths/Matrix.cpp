#include "Matrix.h"
#include <iostream>

#include "../Camera.h"
#include "../Entity.h"

#include "../Config.h"

// Model Coordinates:       vertices rel. center of object
// World Coordinates:       vertices rel. center of world
// Camera Coordinates:      vertices rel. camera
// Homogeneous Coordinates: vertices defined in small cube, all currently on screen


// Create Model Matrix (Model Coords -> World Coords)
glm::mat4 makeModelMatrix(const Entity& entity) {
    glm::mat4 matrix(1.0f);
    // std::cout << "entity: " << entity.position.x << " " << entity.position.y << " " << entity.position.z << std::endl;

    matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), {0, 0, 1});

    matrix = glm::translate(matrix, entity.position);



    return matrix;
}

// Create view matrix (World Coords -> Camera Coords)
glm::mat4 makeViewMatrix(const Camera& camera) {
    glm::mat4 matrix(1.0f);
    // std::cout << "camera: " << camera.position.x << " " << camera.position.y  << " " << camera.position.z << std::endl;

    matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), {0, 0, 1});

    matrix = glm::translate(matrix, -camera.position);

    return matrix;
}

// Create projection matrix (Camera Coords -> Homogeneous Coords)
glm::mat4 makeProjectionMatrix(const Config& config) {
    float x = (float)config.windowX;
    float y = (float)config.windowY;
    float fov = (float)config.fov;

	return glm::perspective(glm::radians(fov), x / y, 0.1f, 1000.0f);
}