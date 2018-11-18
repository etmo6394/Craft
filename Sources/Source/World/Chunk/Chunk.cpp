#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../../Renderer/RenderMaster.h"
#include "../../Util/Random.h"
#include "../../Camera.h"
#include "../../Maths/NoiseGenerator.h"


Chunk::Chunk(const sf::Vector2i& location, World& world)
:	m_location	(location)
,	m_pWorld	(&world) {

}

bool Chunk::makeMesh() {
	for (auto& chunk : m_chunks) {
		if (!chunk.hasMesh()) {
			chunk.makeMesh();
			return true;
		}
	}
	return false;
}

ChunkBlock Chunk::getBlock(int x, int y, int z) const {
	if (outOfBounds(x, y, z)) {
		return BlockId::Air;
	}

	// chunk coords -> chunk section coords
	int bY = y % CHUNK_SIZE;
	return m_chunks.at(y / CHUNK_SIZE).getBlock(x, bY, z);
}

void Chunk::setBlock(int x, int y, int z, ChunkBlock block) {
	if (outOfBounds(x, y, z)) {
		return;
	}

	// chunk coords -> chunk section coords
	int bY = y % CHUNK_SIZE;
	m_chunks.at(y / CHUNK_SIZE).setBlock(x, bY, z, block);
}

bool Chunk::outOfBounds(int x, int y, int z) const {
	if (x > CHUNK_SIZE) return true;
	if (z > CHUNK_SIZE) return true;

	if (x < 0 || y < 0 || z < 0) return true;

	if (y >= (int)m_chunks.size() * CHUNK_SIZE) return true;

	return false;
}

void Chunk::drawChunks(RenderMaster& renderer, const Camera& camera) const {
	for (const auto& chunk : m_chunks) {
		if (chunk.hasMesh()) {
			renderer.drawChunk(chunk);
		}
	} 
}

bool Chunk::hasLoaded() const {
	return m_isLoaded;
}

void Chunk::load() {
	static int seed = RandomSingleton::get().intInRange(444,444444);
	NoiseGenerator temp_noiseGen(seed);
	std::array<int, CHUNK_AREA> heightMap;
	int maxValue = 0;

	// load chunk sections
	for (int y = 0; y < 8; y++) {
		m_chunks.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
	}

	// generate heightmap
	for (int x = 0; x < 16; x++) {
		for (int z = 0; z < 16; z++) {
			int h = temp_noiseGen.getHeight(x, z, m_location.x, m_location.y);
			heightMap[x * CHUNK_SIZE + z] = h;

			maxValue = std::max(maxValue, h);
		}
	}
	//int height = m_chunks.size() * CHUNK_SIZE - 1;

	// set block types
	for (int y = 0; y < maxValue + 1; y++) {
		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 16; z++) {
				if (y > heightMap[x * CHUNK_SIZE + z]) {
					setBlock(x, y, z, BlockId::Air);
				} else if (y == heightMap[x * CHUNK_SIZE + z]) {
					setBlock(x, y, z, BlockId::Grass);
				} else if (y > heightMap[x * CHUNK_SIZE + z] - 3) {
					setBlock(x, y, z, BlockId::Dirt);
				} else if (y > 2) {
					setBlock(x, y, z, BlockId::Stone);
				} else {
					setBlock(x, y, z, BlockId::Bedrock);
				}
			}
		}
	}
	m_isLoaded = true;
}

ChunkSection& Chunk::getSection(int index) {
    while (index >= m_chunks.size()) {
        m_chunks.emplace_back(sf::Vector3i(m_location.x, m_chunks.size(), m_location.y), *m_pWorld);
    }
    return m_chunks.at(index);
}