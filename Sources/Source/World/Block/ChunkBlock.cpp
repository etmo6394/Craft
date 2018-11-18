#include "ChunkBlock.h"

#include "BlockDatabase.h"

// Create ChunkBlock object, with id
ChunkBlock::ChunkBlock(Block_t id)
:	id	(id) {
}

ChunkBlock::ChunkBlock(BlockId id)
:	id	(static_cast<Block_t>(id)) {
}

const BlockDataHolder& ChunkBlock::getData() const {
	return BlockDatabase::get().getData((BlockId)id).getBlockData(); // get block data
}

const BlockType& ChunkBlock::getType() const {
	return BlockDatabase::get().getBlock((BlockId)id); // get block type
}