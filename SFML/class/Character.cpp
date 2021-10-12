#include "Character.hpp"
#include <iostream>

Character::Character(sf::Vector2i position, sf::Vector2i size, std::string texturePath) {

	// create the character rectangle
	sf::IntRect character(position, size);
	Character::setCharacterRectangle(character);

	// character properties
	x = position.x;
	y = position.y;
	width = size.x;
	height = size.y;

	// load character texture
	Character::loadTexture(texturePath);

	// create a sprite of the texture
	sprite.setTexture(characterTexture);
	sprite.setTextureRect(character);

}

void Character::setPosition(int x, int y) {

	character.left = x;
	character.top = y;

	this->x = character.left;
	this->y = character.top;

	sprite.setPosition(sf::Vector2f(x, y));

}

void Character::move(int offsetX, int offsetY) {

	character.left += offsetX;
	character.top += offsetY;

	this->x = character.left;
	this->y = character.top;

	sprite.move(sf::Vector2f(offsetX, offsetY));

}
