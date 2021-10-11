#pragma once

// ヘッダー
#include <SFML/Graphics.hpp>
#include <string.h>

class Character { 

	public:
		
		Character(sf::Vector2i position, sf::Vector2i size, std::string texturePath);

		// change the character position
		void setPosition(sf::Vector2i position);


		// getters
		sf::IntRect getCharacter() const { return character; }


		sf::Sprite sprite;


	private:
		
		bool loadTextureFail() { return EXIT_FAILURE; }

		// setters
		void setCharacterRectangle(sf::IntRect character) {
			this->character = character;
		}


		sf::IntRect character;

};

