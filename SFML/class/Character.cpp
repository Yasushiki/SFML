#include "Character.hpp"
#include <iostream>

Character::Character(sf::Vector2i position, sf::Vector2i size, std::string texturePath) {

	// create the character rectangle
	sf::IntRect character(position, size);
	Character::setCharacterRectangle(character);

	// load character texture
	sf::Texture characterTexture;
	if(!characterTexture.loadFromFile(texturePath)) {
		Character::loadTextureFail();
	}

	// create a sprite of the texture
	sprite.setTexture(characterTexture);
	sprite.setTextureRect(character);

}

void Character::setPosition(sf::Vector2i position) {
	
	character.left = position.x;
	character.top = position.y;

}
