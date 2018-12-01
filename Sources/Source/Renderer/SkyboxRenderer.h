#ifndef SKYBOXRENDERER_H_INCLUDED
#define SKYBOXRENDERER_H_INCLUDED

#include <vector>
#include <glad.h>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/SkyboxShader.h"
#include "../Texture/CubeTexture.h"

class Camera;
class Entity;

class SkyboxRenderer {
	public:
		SkyboxRenderer();

		void add();

		void render(const Camera& camera);

	private:
		Model m_skyboxModel;
		SkyboxShader m_shader;
		CubeTexture m_cubeTexture;
};

#endif // SKYBOXRENDERER_H_INCLUDED