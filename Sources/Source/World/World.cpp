#include "World.h"

#include "../Renderer/RenderMaster.h"

#include "../Maths/Vector2XZ.h"
#include "../Maths/NoiseGenerator.h"
#include "../Util/Random.h"

#include <cmath>
#include <iostream>

namespace {
    constexpr int temp_worldSize = 8;

    // return block coordinates from world coordinates
    VectorXZ getBlockXZ(int x, int z) {
    	return {
        	x % CHUNK_SIZE,
        	z % CHUNK_SIZE
    	};
	}

	// return chunk coordinates from world coordinates
	VectorXZ getChunkXZ(int x, int z) {
    	return {
        	x / CHUNK_SIZE,
        	z / CHUNK_SIZE
    	};
	}

	// out of bounds of world
    bool isOutOfBounds(const VectorXZ& chunkPos) {
        if (chunkPos.x < 0) return true;
        if (chunkPos.z < 0) return true;
        //@TODO: fix OOB definition - replace temp_worldSize w.r.t player
        //if (chunkPos.x >= temp_worldSize) return true;
        //if (chunkPos.z >= temp_worldSize) return true;
        return false;
    }
}

World::World(const Camera& camera, Player& player) 
:	m_chunkManager		(*this) 
,	m_terrainGenerator	(*this) {

	std::cout << "Building World..." << std::endl;
	setSpawn(player);
	player.position = m_spawnCoords;

	int x_loc = (int)(player.position.x/16);
	int z_loc = (int)(player.position.z/16);
	m_chunkManager.getChunk(x_loc, z_loc).load(m_terrainGenerator);
}

ChunkBlock World::getBlock(int x, int y, int z) {
	// world coords -> chunk column coords
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);

	if (isOutOfBounds(cp)) {
		return BlockId::Air;
	}
	return m_chunkManager.getChunk(cp.x, cp.z).getBlock(bp.x, y, bp.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block) {
	// world coords -> chunk column coords
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);

	if (isOutOfBounds(cp)) {
		return;
	}

	auto& chunk = m_chunkManager.getChunk(cp.x, cp.z);
	chunk.setBlock(bp.x, y, bp.z, block);

	if (chunk.hasLoaded()) {
		m_rebuildChunks.emplace(cp.x, y / CHUNK_SIZE, cp.z);
	}
}

void World::update(const Camera& camera, const Player& player) {
	for (int x = 0; x < temp_worldSize; x++) {
		for (int z = 0; z < temp_worldSize; z++) {
			int x_loc = x + (int)(player.position.x/16) - (int)(temp_worldSize/2);
			int z_loc = z + (int)(player.position.z/16) - (int)(temp_worldSize/2);

			// if (inLoadRadius(x_loc, z_loc, player)) {
			// 	//ChunkSection& section = m_chunkManager.getChunk(x_loc, z_loc).getSection(player.position.y/16);
			// 	//m_chunkUpdates.emplace(sf::Vector3i(x_loc, (int)(player.position.y/16), z_loc), section);
			//m_chunkManager.getChunk(x_loc, z_loc).load(m_terrainGenerator);
			// 	if (m_chunkManager.makeMesh(x_loc, z_loc)) return;
			// }

			// m_chunkManager.getChunk(x_loc, z_loc).load(m_terrainGenerator);
			 if (m_chunkManager.makeMesh(x_loc, z_loc)) return;
		}
	}
	updateChunks();
}

void World::renderWorld(RenderMaster& master, const Camera& camera) {
	for (auto& location : m_rebuildChunks) {
		ChunkSection& section = m_chunkManager.getChunk(location.x, location.z).getSection(location.y);
		section.makeMesh();
	}
	m_rebuildChunks.clear();

	const auto& chunkMap = m_chunkManager.getChunks();
	for (auto& chunk : chunkMap) {
		chunk.second.drawChunks(master, camera);
	}
}

void World::setSpawn(const Player& player) {
	auto bp = getBlockXZ(player.position.x, player.position.z);
	auto cp = getChunkXZ(player.position.x, player.position.z);

	int h = m_terrainGenerator.m_noiseGenerator.getHeight(bp.x, bp.z, cp.x, cp.z);
	m_spawnCoords = {player.position.x, h + 2.0f, player.position.z};
}

bool World::inLoadRadius(int x, int z, const Player& player) {
	if (((int)(player.position.x/16) + renderDistance < x) && ((int)(player.position.z/16) + renderDistance < z)) {
		return true;
	}
	return false;
}

void World::updateChunks() {

    for (auto& c : m_chunkUpdates)
    {
    	std::cout << m_chunkUpdates.size() << "\n";
        ChunkSection& s = *c.second;
        s.makeMesh();
    }
    m_chunkUpdates.clear();
}


// ChunkManager& World::getChunkManager() {
// 	return m_chunkManager;
// }