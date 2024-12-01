#include "Objetivos.h"


Objetivos::Objetivos(Vector2f pos) {
	srand(time(NULL));
	num_peligrosidad = rand() % 99;
	if (num_peligrosidad <= 65) {
		peligroso = true;
	}
	else {
		peligroso = false;
	}
	cout << "peligrosidad  " << num_peligrosidad;
	sp_objetivo = new Sprite;
	tx_objetivo = new Texture;
	rectangulo_obj = new IntRect;
	tx_objetivo->loadFromFile("arquero.png");
	sp_objetivo->setTexture(*tx_objetivo);
	sp_objetivo->setPosition(Vector2f(pos.x, pos.y));




}
Objetivos::Objetivos() {

}
Objetivos::~Objetivos() {
	delete sp_objetivo;
	delete tx_objetivo;
	delete rectangulo_obj;
}



void Objetivos::cambiar_objetivo(Vector2f nueva_posicion) {
	num_peligrosidad = rand() % 99;
	if (num_peligrosidad <= 65) {
		peligroso = true;
		tx_objetivo->loadFromFile("arquero.png");
		sp_objetivo->setTexture(*tx_objetivo);
	}
	else {
		peligroso = false;
		tx_objetivo->loadFromFile("arquero2.png");
		sp_objetivo->setTexture(*tx_objetivo);
	}
	sp_objetivo->setPosition(nueva_posicion);
}

Sprite Objetivos::get_sprite() {
	return *sp_objetivo;
}
bool Objetivos::get_peligrosidad() {
	return peligroso;
}
