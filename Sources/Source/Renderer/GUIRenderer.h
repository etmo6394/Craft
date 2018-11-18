#ifndef GUIRENDERER_H_INCLUDED
#define GUIRENDERER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class GUIRenderer {
	public:
		void add(const sf::Drawable& drawable);

		void render(sf::RenderWindow& window);

	private:
		std::vector<const sf::Drawable*> m_draws;
};

#endif // GUIRENDERER_H_INCLUDED
