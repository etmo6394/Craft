#include "TerrainGenerator.h"
#include <iostream>

namespace {
	static int seed = RandomSingleton::get().intInRange(444,444444);
}

NoiseGenerator TerrainGenerator::m_noiseGenerator(seed);

TerrainGenerator::TerrainGenerator(World& world) 
:	m_world	(&world) {
	std::cout << "Generating Terrain..." << std::endl;
}

void TerrainGenerator::generateTerrain(Chunk& chunk) {
	m_pChunk = &chunk;

	getHeightmap();
	setBlocks(maxValue);
}

void TerrainGenerator::getHeightmap() {
	maxValue = 0;

	m_location = m_pChunk->getLocation();

	// generate heightmap
	for (int x = 0; x < 16; x++) {
		for (int z = 0; z < 16; z++) {
			int h = m_noiseGenerator.getHeight(x, z, m_location.x, m_location.y);
			m_heightMap.get(x,z) = h;

			maxValue = std::max(maxValue, h);
		}
	}
}

void TerrainGenerator::setBlocks(int maxValue) {
	// set block types
	for (int y = 0; y < maxValue + 1; y++) {
		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 16; z++) {
				if (y > m_heightMap.get(x,z)) {
					m_pChunk->setBlock(x, y, z, BlockId::Air);
				} else if (y == m_heightMap.get(x,z)) {
					m_pChunk->setBlock(x, y, z, BlockId::Grass);
				} else if (y > m_heightMap.get(x,z) - 3) {
					m_pChunk->setBlock(x, y, z, BlockId::Dirt);
				} else if (y > 2) {
					m_pChunk->setBlock(x, y, z, BlockId::Stone);
				} else {
					m_pChunk->setBlock(x, y, z, BlockId::Bedrock);
				}
			}
		}
	}
}