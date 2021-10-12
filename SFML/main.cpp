#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "class/TileMap.hpp"
#include "class/Character.hpp"

const int WIDTH = 480;
const int HEIGHT = 480;
const int SPEED = 15;

std::vector<sf::IntRect> createBlocks(std::vector<sf::Vector2f> blocks, sf::Vector2u size) {

	std::vector<sf::IntRect> blocksVector;

	for(auto block : blocks) {
		blocksVector.insert(blocksVector.end(), sf::IntRect(block.x, block.y, size.x, size.y));
	}

	return blocksVector;
}

//void colision(sf::IntRect &character, std::vector<sf::IntRect> blocksVector) {
//	
//	for(const auto& i : blocksVector) {
//		if(character.intersects(i)) {
//			character.top -= 1.0f;
//			std::cout << "colisão" << std::endl;
//		}
//	}
//
//}

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

	// タイルインデックスの配列でレベルを定義する
	std::ifstream file("mapa.txt");
	int level[60 * 33];

	//　.txtファイル内容を読み込んで、レベルを作る
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

	std::vector<sf::Vector2f> blocks = map.getBlocks();
	sf::Vector2u size = map.getSize();

	// create blocks
	std::vector<sf::IntRect> blocksVector = createBlocks(blocks, size);


	///　グラフィックス　///

	// キャラ
	Character personagem(sf::Vector2i(0, 0), sf::Vector2i(128, 128), "resources/image/personagem.png");



	/// 音 ///

	//　音楽をロードする
	/*sf::Music music;
	if(!music.openFromFile("resources/sound/gta-sanders.ogg")) {
		return EXIT_FAILURE;
	}

	music.play();*/


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

				if(event.key.code == sf::Keyboard::X) {
					personagem.setPosition(20, 20);
				}

				if(event.key.code == sf::Keyboard::Right) {
					personagem.move(SPEED / 2.5f, 0);
				}

				if(event.key.code == sf::Keyboard::Left) {
					personagem.move(-(SPEED / 2.5f), 0);
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

		std::cout << personagem.getCharacter().left << " " << personagem.getCharacter().top << std::endl;

		if(up) {
			y += -SPEED;
			//character.top -= SPEED / 2.5f;
			map.move(sf::Vector2f(0.0f, SPEED));
		}
		if(left) {
			x += -SPEED;
			//character.left -= SPEED / 2.5f;
			map.move(sf::Vector2f(SPEED, 0.0f));
		}
		if(down) {
			y += SPEED;
			//character.top += SPEED / 2.5f;
			map.move(sf::Vector2f(0.0f, -SPEED));
		}
		if(right) {
			x += SPEED;
			//character.left += SPEED / 2.5f;
			map.move(sf::Vector2f(-SPEED, 0.0f));
		}

		// 重力
		personagem.move(0, 1);

		// window colision
		if(personagem.getCharacter().left < 0) {
			personagem.setPosition(0, personagem.y);
		} else if(personagem.getCharacter().left > WIDTH - personagem.width) {
			personagem.setPosition(WIDTH - personagem.width, personagem.y);
		}
		if(personagem.getCharacter().top > HEIGHT - personagem.height) {
			personagem.setPosition(personagem.x, HEIGHT - personagem.height);
		}

		//colision(character, blocksVector);
		//
		//for(const auto& i : blocksVector) {
		//
		//	sf::IntRect collisionBlock;
		//
		//	bool checkCollision = character.intersects(i, collisionBlock);
		//
		//	if(checkCollision) {
		//		character.top = (collisionBlock.top - character.height);
		//	} else {
		//		character.top += 1.0f;
		//		break;
		//	}
		//
		//
		//}

		window.setPosition(sf::Vector2i(x, y));

		//	マップを描く
		window.clear();
		window.draw(map);
		window.draw(personagem.sprite);
		window.display();

	}

	return 0;
}