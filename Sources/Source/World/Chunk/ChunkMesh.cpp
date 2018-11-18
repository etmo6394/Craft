#include "ChunkMesh.h"

#include <iostream>

// Create ChunkMesh object
void ChunkMesh::addFace(const std::vector<GLfloat>& blockFace, const std::vector<GLfloat>& textureCoords, const sf::Vector3i& chunkPosition, const sf::Vector3i& blockPosition) {
	// add face to chunk mesh
	faces++;
	auto& vertices = m_mesh.vertexPositions;
	auto& texCoords = m_mesh.textureCoords;
	auto& indices = m_mesh.indices;

	texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end()); // add texture coordinates
	
	// add face vertices
	for (int i = 0, index = 0; i < 4; ++i) {
		vertices.push_back(blockFace[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		vertices.push_back(blockFace[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		vertices.push_back(blockFace[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
	}

	// add indices
	indices.insert(indices.end(), 
	{
		m_indexIndex,
		m_indexIndex + 1,
		m_indexIndex + 2,

		m_indexIndex + 2,
		m_indexIndex + 3,
		m_indexIndex,
	});
	m_indexIndex += 4;
}

void ChunkMesh::bufferMesh() {
    // std::cout   << "Buffered"
    //             << "\nVertex:   " << m_mesh.vertexPositions.size()  / 3
    //             << "\nTextures: " << m_mesh.textureCoords.size()    / 2
    //             << "\nIndices:  " << m_mesh.indices.size()          / 1.5  << "\n";


	m_model.addData(m_mesh); // add data to mesh model (VAO, VBO, EBO)

	// clear mesh model
	m_mesh.vertexPositions.clear();
	m_mesh.textureCoords.clear();
	m_mesh.indices.clear();

	// resize meshmodel to fit size
	m_mesh.vertexPositions.shrink_to_fit();
	m_mesh.textureCoords.shrink_to_fit();
	m_mesh.indices.shrink_to_fit();

	m_indexIndex = 0; // reset index
}

const Model& ChunkMesh::getModel() const {
	return m_model; // get ChunkMesh model
}