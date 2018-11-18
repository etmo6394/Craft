#include "ChunkShader.h"

// Create BasicShader object, with shader object
ChunkShader::ChunkShader()
:   BasicShader("ChunkVertex", "ChunkFragment") {
    getUniforms(); // find locations of uniform variables
}

void ChunkShader::getUniforms() {
    BasicShader::getUniforms();
}