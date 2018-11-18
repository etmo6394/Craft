#include "ChunkRenderer.h"

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Block/BlockDatabase.h"

#include "../Camera.h"

void ChunkRenderer::add(const ChunkMesh& mesh) {
	m_chunks.push_back(&mesh);
}

void ChunkRenderer::render(const Camera& camera) {
	if (m_chunks.empty()) {
        return;
    }

	glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);

	m_shader.useProgram(); // install program object (vertex/fragment shaders)
	BlockDatabase::get().textureAtlas.bindTexture(); // bind named texture to texturing target

	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix()); // load projection view matrix (World Coords -> Homogeneous Coords)

	for (const ChunkMesh* mesh : m_chunks) {
		const ChunkMesh& m = *mesh;

		m.getModel().bindVAO(); // activate VAO
		glDrawElements(GL_TRIANGLES, m.getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr); // render primitives from array data
	}

	m_chunks.clear(); // clear cube object
}