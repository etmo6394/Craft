#ifndef CUBETEXTURE_H_INCLUDED
#define CUBETEXTURE_H_INCLUDED

#include <glad.h>
#include <string>
#include <SFML/Graphics.hpp>

#include "../Util/NonCopyable.h"

class CubeTexture : public NonCopyable {
	public:
		//CubeTexture() = default;
		CubeTexture();

		~CubeTexture();

		void loadCubemap(std::vector<std::string> faces);

		void loadFromFile(std::vector<std::string> faces);

		void bindTexture() const;

	private:
		GLuint m_id;
};

#endif // CUBETEXTURE_H_INCLUDED