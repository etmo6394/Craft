#include "ChunkSection.h"

#include "../Block/BlockId.h"
#include "../World.h"
#include "ChunkMeshBuilder.h"

#include <iostream>

ChunkSection::ChunkSection(const sf::Vector3i& location, World& world) 
:	m_location	(location) 
,	m_pWorld	(&world) {
	//static_assert(sizeof(m_blocks) == CHUNK_VOLUME, "wot");

}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block) {
	// if out of chunk, return
	//m_hasMesh = false;
	if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z)) {
		auto location = toWorldPosition(x, y, z);
		m_pWorld->setBlock(location.x, location.y, location.z, block);
		return;
	}

	m_blocks[getIndex(x, y, z)] = block; // set block
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const {
	// if out of chunk, return Air
	if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z)) {
		auto location = toWorldPosition(x, y, z);
		return m_pWorld->getBlock(location.x, location.y, location.z);
	}

	return m_blocks[getIndex(x, y, z)]; // return block
}

const sf::Vector3i ChunkSection::getLocation() const {
	return m_location;
}

bool ChunkSection::hasMesh() const {
    return m_hasMesh;
}

void ChunkSection::makeMesh() {
	ChunkMeshBuilder(*this, m_mesh).buildMesh();
	m_mesh.bufferMesh();
	m_hasMesh = true;
}

sf::Vector3i ChunkSection::toWorldPosition(int x, int y, int z) const {
	return {
		m_location.x * CHUNK_SIZE + x,
		m_location.y * CHUNK_SIZE + y,
		m_location.z * CHUNK_SIZE + z
	};
}


bool ChunkSection::outOfBounds(int value) {
	return value >= CHUNK_SIZE || value < 0; // OOB if out of chunk or under 0
}

int ChunkSection::getIndex(int x, int y, int z) {
	return (y * CHUNK_AREA) + (z * CHUNK_SIZE) + x; // return index of block
}