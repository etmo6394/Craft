#ifndef CHUNKSECTION_H_INCLUDED
#define CHUNKSECTION_H_INCLUDED

#include <array>
#include <SFML/Graphics.hpp>

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"
#include "../Chunk/ChunkMeshBuilder.h"
#include "ChunkMesh.h"
#include "IChunk.h"
//#include "ChunkMeshBuilder.h"

#include "../Block/BlockData.h"

class World;


class ChunkSection : public IChunk {
	friend class Chunk;

	public:
		ChunkSection(const sf::Vector3i& location, World& world);

		void setBlock(int x, int y, int z, ChunkBlock block) override;
		ChunkBlock getBlock(int x, int y, int z) const override;

		const sf::Vector3i getLocation() const;

		bool hasMesh() const;
		void makeMesh();

		ChunkMesh m_mesh;

	private:

		sf::Vector3i toWorldPosition(int x, int y, int z) const;

		static bool outOfBounds(int value);
		static int getIndex(int x, int y, int z);


		std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;
		//ChunkMesh m_mesh;
		sf::Vector3i m_location;

		World* m_pWorld;
		bool m_hasMesh = false;
};

#endif // CHUNKSECTION_H_INCLUDED