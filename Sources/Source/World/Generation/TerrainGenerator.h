#ifndef TERRAINGENERATOR_H_INCLUDED
#define TERRAINGENERATOR_H_INCLUDED

#include "../../Util/Array2D.h"
#include "../../Util/Random.h"
#include "../../Maths/NoiseGenerator.h"
#include "../Chunk/Chunk.h"
#include "../WorldConstants.h"


class World;
class NoiseGenerator;
class Chunk;

class TerrainGenerator {
	public:
		TerrainGenerator(World& world);

		static NoiseGenerator m_noiseGenerator;

		void generateTerrain(Chunk& chunk);

		void getHeightmap();

		void setBlocks(int maxValue);

	private:
		World* m_world;
		Chunk* m_pChunk = nullptr;

		int maxValue;
		sf::Vector2i m_location;

		Array2D<int, CHUNK_SIZE> m_heightMap;
};

#endif // TERRAINGENERATOR_H_INCLUDED