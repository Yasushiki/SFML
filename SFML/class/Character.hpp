#pragma once

// ヘッダー
#include <SFML/Graphics.hpp>
#include <string.h>

class Character { 

	public:
		
		Character(sf::Vector2i position, sf::Vector2i size, std::string texturePath);

		// change the character position
		void setPosition(int x, int y);
		void move(int offsetX, int offsetY);

		// getters
		sf::IntRect getCharacter() const { return character; }


		sf::Sprite sprite;

		int x;
		int y;


	private:
		
		bool loadTexture(std::string texturePath) { 
			if(!characterTexture.loadFromFile(texturePath)) {
				return EXIT_FAILURE;
			}
		}

		// setters
		void setCharacterRectangle(sf::IntRect character) {
			this->character = character;
		}


		sf::IntRect character;
		sf::Texture characterTexture;

};

