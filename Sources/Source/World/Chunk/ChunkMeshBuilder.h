#ifndef CHUNKMESHBUILDER_H_INCLUDED
#define CHUNKMESHBUILDER_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include <glad.h>

#include "../Block/ChunkBlock.h"

class ChunkSection;
class ChunkMesh;
class BlockData;
class BlockDataHolder;

class ChunkMeshBuilder {
	public:
		ChunkMeshBuilder(ChunkSection& chunk, ChunkMesh& mesh);

		void buildMesh();

	private:
		void tryAddFaceToMesh(const std::vector<GLfloat>& blockFace, const sf::Vector2i& textureCoords, const sf::Vector3i& blockPosition, const sf::Vector3i& blockFacing);

		bool shouldMakeFace(const sf::Vector3i& adjBlock, const BlockDataHolder& blockData);

		ChunkSection* m_pChunk = nullptr;
		ChunkMesh* m_pMesh = nullptr;

		const BlockDataHolder* m_pBlockData = nullptr;

		int faces;
};


// add to mesh

#endif // CHUNKMESHBUILDER_H_INCLUDED