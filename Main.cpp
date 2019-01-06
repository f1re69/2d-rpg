#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;
void gestion_clavier();

#pragma region variables
sf::RenderWindow window;
sf::Texture perso;
sf::Sprite spritePerso;
sf::Vector2i anim(1, 10);
sf::Clock clockTime;
sf::RectangleShape rect;
sf::RectangleShape rect2;
sf::View view;
enum Direction { Down = 10, Up = 8, Left = 9, Right = 11 };	// emplacement pixel top left du sprite de départ multiplié par BLOCKSIZE
int speed = 4;
const int SCREENW = 800;
const int SCREENH = 600;
const int BLOCKSIZE = 64;
const int BLOCKSIZE_WIDTH_MOVMENT = 9;
const int MAX_SPEED = 12;
const int MIN_SPEED = 5;
bool updateFps = true;	// si false, animation stoppée 
#pragma endregion variables

int main() {

	// Création de la fenêtre (800x600 avec un titre "Tuto SFML"
	window.create (sf::VideoMode(800, 600), "Tuto SFML");
	// 60 fps
	window.setFramerateLimit(60);
	rect.setFillColor(sf::Color(100, 250, 50));
	rect.setPosition(100, 100);
	rect.setSize(sf::Vector2f(64,64));

	rect2.setFillColor(sf::Color(100, 250, 50));
	rect2.setPosition(1000, 1000);
	rect2.setSize(sf::Vector2f(64, 64));
	// Chargement des sprites
	if (!perso.loadFromFile("sprites.png")) {
		cout << "impossible de charger le sprite" << endl;
	}
	perso.setSmooth(true);
	spritePerso.setTexture(perso);
	
	

	while (window.isOpen()) {
		sf::Event event;
		view.reset(sf::FloatRect(0,0, SCREENW, SCREENH));
		sf::Vector2f  position(SCREENW / 2, SCREENH / 2);
		position.x = spritePerso.getPosition().x + (BLOCKSIZE / 2 - SCREENW / 2);
		position.y = spritePerso.getPosition().y + (BLOCKSIZE / 2 - SCREENH / 2);
		if (position.x < 0) {
			position.x = 0;
		}
		if (position.y < 0) {
			position.y = 0;
		}
		view.reset(sf::FloatRect(position.x, position.y, SCREENW, SCREENH));


		spritePerso.setTextureRect(sf::IntRect(anim.x * BLOCKSIZE, anim.y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE));
		window.draw(rect);
		window.draw(rect2);
		window.draw(spritePerso);
		window.display();
		gestion_clavier();
		window.clear();
		window.setView(view);
		
		if ((abs((spritePerso.getPosition().x + (BLOCKSIZE / 2)) - (rect.getPosition().x + (BLOCKSIZE / 2))) < BLOCKSIZE) &&
			(abs((spritePerso.getPosition().y + (BLOCKSIZE / 2)) - (rect.getPosition().y + (BLOCKSIZE / 2))) < BLOCKSIZE)) {
			cout << "collision" << endl;
		}



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

		else if (anim.x != 0) {
			// Repositionnement de l'image à la position 0
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

		
		

		// Test des évenements
		while (window.pollEvent(event)) {

			// Fermeture de la fenêtre lors du clique sur la croix rouge
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		

	}


	return 0;
}

// Gestion des event clavier : Déplacement up,down,left,right ...
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

	// !updateFps = Le personnage arrête de se déplacer 
	else {
		updateFps = false;
	}

	if (spritePerso.getPosition().x <= 0) {
		spritePerso.setPosition(sf::Vector2f(0, spritePerso.getPosition().y));
	}
	if (spritePerso.getPosition().y <= 0) {
		spritePerso.setPosition(sf::Vector2f(spritePerso.getPosition().x, 0));
	}
}
