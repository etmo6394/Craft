#ifndef CHUNKRENDERER_H_INCLUDED
#define CHUNKRENDERER_H_INCLUDED

#include <vector>

#include "../Shaders/ChunkShader.h"


class Camera;
class ChunkMesh;

class ChunkRenderer {
	public:

	void add(const ChunkMesh& mesh);

	void render(const Camera& camera);

	private:
	std::vector<const ChunkMesh*> m_chunks;

	ChunkShader m_shader;
};

#endif // CHUNKRENDERER_H_INCLUDED