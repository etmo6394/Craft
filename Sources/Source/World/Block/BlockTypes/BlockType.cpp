#include "BlockType.h"

// Create BlockType object, with block data
BlockType::BlockType(const std::string& fileName)
:   m_data  (fileName)
{

}

const BlockData& BlockType::getData() const
{
    return m_data; // get block data
}