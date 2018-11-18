#include "BlockDatabase.h"

// Create BlockData object, with textures
BlockDatabase::BlockDatabase()
:	textureAtlas	("Textures") {

	// create unique block types
	m_blocks[(int)BlockId::Air]     	= std::make_unique<DefaultBlock>("Air");
	m_blocks[(int)BlockId::Grass]   	= std::make_unique<DefaultBlock>("Grass");
	m_blocks[(int)BlockId::Dirt]   		= std::make_unique<DefaultBlock>("Dirt");
	m_blocks[(int)BlockId::Stone]   	= std::make_unique<DefaultBlock>("Stone");
	m_blocks[(int)BlockId::Bedrock]   	= std::make_unique<DefaultBlock>("Bedrock");

}

BlockDatabase& BlockDatabase::get() {
	static BlockDatabase d;
	return d;
}

const BlockType& BlockDatabase::getBlock(BlockId id) const {
	return *m_blocks[(int)id]; // get block type
}

const BlockData& BlockDatabase::getData (BlockId id) const {
	return m_blocks[(int)id]->getData(); // get block data
}
