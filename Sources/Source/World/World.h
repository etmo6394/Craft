#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>

#include "Chunk/Chunk.h"
#include "../Camera.h"
#include "../Player/Player.h"
#include "Chunk/ChunkManager.h"
#include "Generation/TerrainGenerator.h"

class RenderMaster;
class Camera;
class Player;

class World {
	public:
		World(const Camera& camera, Player& player);

		ChunkBlock getBlock(int x, int y, int z);
		void setBlock(int x, int y, int z, ChunkBlock block);

		void renderWorld(RenderMaster& master, const Camera& camera);

		void update(const Camera& camera, const Player& player);

		void setSpawn(const Player& player);

		bool inLoadRadius(int x, int y, const Player& player);

		void updateChunks();

		// ChunkManager& getChunkManager();

		// static VectorXZ getBlockXZ(int x, int z);
        // static VectorXZ getChunkXZ(int x, int z);

	private:
		glm::vec3 m_spawnCoords;

		int renderDistance = 2;

		std::unordered_set<sf::Vector3i> m_rebuildChunks;

		ChunkManager 		m_chunkManager;
		TerrainGenerator 	m_terrainGenerator;

		std::unordered_map<sf::Vector3i, ChunkSection*> m_chunkUpdates;

};

#endif // WORLD_H_INCLUDED