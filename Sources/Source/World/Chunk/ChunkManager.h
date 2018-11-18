#ifndef CHUNKMANAGER_H_INCLUDED
#define CHUNKMANAGER_H_INCLUDED

#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "../../Maths/Vector2XZ.h"

#include "Chunk.h"

class World;

//using ChunkMap = std::unordered_map<VectorXZ, Chunk>;

class ChunkManager {
	public:
		ChunkManager(World& world);

		Chunk& getChunk(int x, int z);

		const std::unordered_map<VectorXZ, Chunk>& getChunks() const;

		bool makeMesh(int x, int z);

		void queueChunk(int x, int z);

		void update();

	private:
		std::unordered_map<VectorXZ, Chunk> m_chunks;
		//std::unordered_set<VectorXZ> m_queue;

		World* m_world;

};

#endif // CHUNKMANAGER_H_INCLUDED