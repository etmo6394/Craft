#include "World.h"

#include "../Renderer/RenderMaster.h"

#include "../Maths/Vector2XZ.h"
#include "../Maths/NoiseGenerator.h"
#include "../Util/Random.h"

#include <iostream>

namespace {
    constexpr int temp_worldSize = 8;

    VectorXZ getBlockXZ(int x, int z) {
    	return {
        	x % CHUNK_SIZE,
        	z % CHUNK_SIZE
    	};
	}

	VectorXZ getChunkXZ(int x, int z) {
    	return {
        	x / CHUNK_SIZE,
        	z / CHUNK_SIZE
    	};
	}

    bool isOutOfBounds(const VectorXZ& chunkPos)
    {
        if (chunkPos.x < 0) return true;
        if (chunkPos.z < 0) return true;
        //@TODO: fix OOB definition
        //if (chunkPos.x >= temp_worldSize) return true;
        //if (chunkPos.z >= temp_worldSize) return true;
        return false;
    }
}

World::World(const Camera& camera, Player& player) 
:	m_chunkManager	(*this) {

	static int seed = RandomSingleton::get().intInRange(444,444444);
	NoiseGenerator temp_noiseGen(seed);
	setSpawn(player, temp_noiseGen);
	player.position = m_spawnCoords;
	// m_chunkManager.getChunk((int)(player.position.x/16), (int)(player.position.z/16)).load(temp_noiseGen);

	for (int x = 0; x < temp_worldSize; x++) {
		for (int z = 0; z < temp_worldSize; z++) {
			// std::cout << (x + (int)(player.position.x/16)) << " " << (z + (int)(player.position.z/16)) << std::endl;
			int x_loc = x + (int)(player.position.x/16) - (int)(temp_worldSize/2);
			int z_loc = z + (int)(player.position.z/16) - (int)(temp_worldSize/2);

			m_chunkManager.getChunk(x_loc, z_loc).load(temp_noiseGen);
		}
	}
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
			if (m_chunkManager.makeMesh(x_loc, z_loc)) return;
		}
	}
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

void World::setSpawn(const Player& player, NoiseGenerator temp_noiseGen) {
	auto bp = getBlockXZ(player.position.x, player.position.z);
	auto cp = getChunkXZ(player.position.x, player.position.z);

	int h = temp_noiseGen.getHeight(bp.x, bp.z, cp.x, cp.z);
	//std::cout << cp.x << " " << cp.z << " " << bp.x << " " << bp.z << " " << h << std::endl;
	m_spawnCoords = {player.position.x, h + 2.0f, player.position.z};
}

bool World::inLoadRadius(int x, int y) {
	// if () {
	// 	return true;
	// }
	// return false;
}


// ChunkManager& World::getChunkManager() {
// 	return m_chunkManager;
// }