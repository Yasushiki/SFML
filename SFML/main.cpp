#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "class/TileMap.hpp"

const int WIDTH = 480;
const int HEIGHT = 480;
const int SPEED = 15;

int main() {

	/// ウィンドウ ///

	//　メインウィンドウを作る
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), L"ゲーム", sf::Style::None);
	window.setFramerateLimit(30);

	//　ウィンドウ動きのプロパティ
	int x = 0, y = 0;
	bool up = false, down = false, left = false, right = false;
	window.setPosition(sf::Vector2i(x, y));
	


	/// 世界 ///

	// define the level with an array of tile indices
	std::ifstream file("mapa.txt");
	int level[60*33];

	for(int i = 0; i < 60 * 33; i++) {
		std::string a;
		file >> a;
		level[i] = std::stoi(a);
	}

	TileMap map;
	if(!map.load("resources/image/tileset.png", sf::Vector2u(32, 32), level, 60, 33)) {
		return -1;
	}

	file.close();
	


	///　スプライト　///

	//　キャラ
	sf::Texture charText;
	if(!charText.loadFromFile("resources/image/personagem.png")) {
		return EXIT_FAILURE;
	}	
	sf::Sprite charSprite(charText);
	charSprite.setPosition(sf::Vector2f(230.0f, 230.0f));



	/// 音 ///

	//　音楽をロードする
	sf::Music music;
	if(!music.openFromFile("resources/sound/gta-sanders.ogg")) {
		return EXIT_FAILURE;
	}

	/*music.play();*/
	

	//　ウィンドウループ
	while(window.isOpen()) {

		//　イベント処理
		sf::Event event;
		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) {
				window.close();
			}

			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Escape) {
					sf::sleep(sf::seconds(5));
				}
			}
		}


		//　ウィンドウを動く
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y > 0) {
			up = true;
		} else {
			up = false;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x > 0) {
			left = true;
		} else {
			left = false;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y < 1056 - HEIGHT) {
			down = true;
		} else {
			down = false;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x < 1920 - WIDTH) {
			right = true;
		} else {
			right = false;
		}

		if(up) {
			y += -SPEED;
			charSprite.move(0.0f, -SPEED/2);
			map.move(sf::Vector2f(0.0f, SPEED));
		}
		if(left) {
			x += -SPEED;
			charSprite.move(-SPEED/2, 0.0f);
			map.move(sf::Vector2f(SPEED, 0.0f));
		}
		if(down) {
			y += SPEED;
			charSprite.move(0.0f, SPEED/2);
			map.move(sf::Vector2f(0.0f, -SPEED));
		}
		if(right) {
			x += SPEED;
			charSprite.move(SPEED/2, 0.0f);
			map.move(sf::Vector2f(-SPEED, 0.0f));
		}
		
		//std::cout << charSprite.getPosition().x << " " << charSprite.getPosition().y << std::endl;

		if(charSprite.getPosition().x > WIDTH-20) {
			charSprite.setPosition(sf::Vector2f(WIDTH-20, charSprite.getPosition().y));
		} else if(charSprite.getPosition().x < 0) {
			charSprite.setPosition(sf::Vector2f(0, charSprite.getPosition().y));
		}
		if(charSprite.getPosition().y > HEIGHT-20) {
			charSprite.setPosition(sf::Vector2f(charSprite.getPosition().x, HEIGHT-20));
		}


		//sprite.setPosition(sf::Vector2f(-x, -y));
		window.setPosition(sf::Vector2i(x, y));

		//	マップを描く
		window.clear();
		window.draw(map);
		window.draw(charSprite);
		window.display();

	}

	return 0;
}