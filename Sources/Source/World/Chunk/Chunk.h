#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <vector>
#include "ChunkSection.h"
#include "../../Util/NonCopyable.h"

class RenderMaster;
class Camera;
class NoiseGenerator;
class TerrainGenerator;

class Chunk : public IChunk {
	public:
		Chunk() = default;
		Chunk(const sf::Vector2i& location, World& world);

		bool makeMesh();

		ChunkBlock getBlock(int x, int y, int z) const override;
		void setBlock(int x, int y, int z, ChunkBlock block) override;

		bool outOfBounds(int x, int y, int z) const;

		void drawChunks(RenderMaster& renderer, const Camera& camera) const;

		ChunkSection& getSection(int index);

		sf::Vector2i getLocation();

		bool hasLoaded() const;
		void load(TerrainGenerator& generator);

	private:
		std::vector<ChunkSection> m_chunks;
		sf::Vector2i m_location;

		World* m_pWorld;

		bool m_isLoaded = false;
};

#endif // CHUNK_H_INCLUDED