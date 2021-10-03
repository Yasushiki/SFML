#pragma once

// ÉwÉbÉ_Å[
#include <SFML/Graphics.hpp>
#include <vector>


class TileMap : public sf::Drawable, public sf::Transformable {

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            // apply the transform
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &m_tileset;

            // draw the vertex array
            target.draw(m_vertices, states);
        }

        void setSize(sf::Vector2u tileSize) {
            TileMap::size = tileSize;
        }

        void setBlocks(sf::Vector2f position) {
            blocks.insert(blocks.end(), position);
        }

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        sf::Vector2u size;

        std::vector<sf::Vector2f> blocks;

	public:
	
		bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

        // getters
        sf::Vector2u getSize() const { return size; }
        std::vector<sf::Vector2f> getBlocks() const { return blocks;  }
	    
};
