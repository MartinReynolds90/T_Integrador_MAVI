#include "Vidas.h"

Vidas::Vidas() {
	cantidad_vidas = 3;
	sp_vidas = new Sprite;
	tx_vidas = new Texture;
	rectangulo_vidas = new IntRect(0, (32 * cantidad_vidas) - 32, 96, 32);
	tx_vidas->loadFromFile("vidas.png");
	sp_vidas->setTexture(*tx_vidas);
	sp_vidas->setTextureRect(*rectangulo_vidas);
	sp_vidas->setPosition(75, 10);

}

Vidas::~Vidas() {
	delete sp_vidas;
	delete tx_vidas;
	delete rectangulo_vidas;
}

int Vidas::consultar_vidas() {
	return cantidad_vidas;
}

void Vidas::restar_vidas() {
	cantidad_vidas--;
	rectangulo_vidas = new IntRect(0, (32 * cantidad_vidas) - 32, 96, 32);
	sp_vidas->setTextureRect(*rectangulo_vidas);
}
Sprite Vidas::get_sprite() {
	return *sp_vidas;
}
void Vidas::restablecer_vidas(int cantidad) {
	cantidad_vidas = cantidad;
	rectangulo_vidas = new IntRect(0, (32 * cantidad_vidas) - 32, 96, 32);
	sp_vidas->setTextureRect(*rectangulo_vidas);
}
