#include "Player.h"


Player::Player(int x_inicial, int y_inicial) {
	sp_mira = new Sprite;
	tx_mira = new Texture;
	tx_mira->loadFromFile("mira.png");
	sp_mira->setTexture(*tx_mira);
	sp_mira->setOrigin(32.f, 32.f);
	sp_mira->setPosition(x_inicial, y_inicial);


}
Player::Player() {}

Player::~Player() {
	delete sp_mira;
	delete tx_mira;
}

void Player::apuntar(int x, int y) {
	sp_mira->setPosition(Vector2f(x, y));
}
Sprite Player::get_sprite() {
	return *sp_mira;
}

