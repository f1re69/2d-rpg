#pragma once
class Personnage {

	sf::Texture perso;
	sf::Sprite spritePerso;
	string sprite = "sprites.png";

	if (!perso.loadFromFile("sprites.png")) {
		cout << "impossible de charger le sprite" << endl;
	}
	perso.setSmooth(true);
	spritePerso.setTexture(perso);
};

