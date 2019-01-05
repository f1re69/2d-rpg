#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;
void gestion_clavier();

#pragma region variables
sf::RenderWindow window;
sf::Texture perso;
sf::Sprite spritePerso;
sf::Vector2i anim(1, 10);
sf::Clock clockTime;
enum Direction { Down = 10, Up = 8, Left = 9, Right = 11 };	// emplacement pixel top left du sprite de d�part multipli� par BLOCKSIZE
int speed = 4;
const int BLOCKSIZE = 64;
const int BLOCKSIZE_WIDTH_MOVMENT = 9;
const int MAX_SPEED = 12;
const int MIN_SPEED = 5;
bool updateFps = true;	// si false, animation stopp�e 
#pragma endregion variables

int main() {

	// Cr�ation de la fen�tre (800x600 avec un titre "Tuto SFML"
	window.create (sf::VideoMode(800, 600), "Tuto SFML");
	// 60 fps
	window.setFramerateLimit(60);

	// Chargement des sprites
	if (!perso.loadFromFile("sprites.png")) {
		cout << "impossible de charger le sprite" << endl;
	}
	perso.setSmooth(true);
	spritePerso.setTexture(perso);
	
	

	while (window.isOpen()) {

		if (updateFps) {	
		
			// Une image toutes les 50ms
			if (clockTime.getElapsedTime().asMilliseconds() >= 50) {
				anim.x++;
				//cout << clockTime.getElapsedTime().asMilliseconds() << endl << "anim.x : " << anim.x << endl;
				if (anim.x * BLOCKSIZE >= BLOCKSIZE * BLOCKSIZE_WIDTH_MOVMENT) {
					anim.x = 0;
				}
				clockTime.restart();
			}
		}

		else {
			// Repositionnement de l'image � la position 0
			while (anim.x != 0) {
				if (clockTime.getElapsedTime().asMilliseconds() >= 30) {
					anim.x++;
					if (anim.x * BLOCKSIZE >= BLOCKSIZE * BLOCKSIZE_WIDTH_MOVMENT) {
						anim.x = 0;
					}
					clockTime.restart();
				}
			}
		}

		spritePerso.setTextureRect(sf::IntRect(anim.x * BLOCKSIZE, anim.y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE));
		window.draw(spritePerso);
		window.display();
		
		sf::Event event;

		// Test des �venements
		while (window.pollEvent(event)) {

			// Fermeture de la fen�tre lors du clique sur la croix rouge
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		gestion_clavier();

		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))

		window.clear();

	}


	return 0;
}

// Gestion des event clavier : D�placement up,down,left,right ...
void gestion_clavier() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		updateFps = true;
		anim.y = Up;
		spritePerso.move(0, -speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		updateFps = true;
		anim.y = Down;
		spritePerso.move(0, speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		updateFps = true;
		anim.y = Left;
		spritePerso.move(-speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		updateFps = true;
		anim.y = Right;
		spritePerso.move(speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		updateFps = false;
		if (speed + 1 < MAX_SPEED) {
			speed += 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		updateFps = false;
		if (speed - 1 > MIN_SPEED) {
			speed -= 1;
		}
	}
	// !updateFps = Le personnage arr�te de se d�placer 
	else {
		updateFps = false;
	}
}
