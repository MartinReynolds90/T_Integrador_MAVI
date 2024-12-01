#include "SFML/Graphics.hpp"
#include "iostream"

using namespace std;
using namespace sf;

class Player {
private:
	Sprite* sp_mira;
	Texture* tx_mira;
	int vidas;
	Vector2f posicion_mira;
public:

	Player(int, int);
	Player();
	~Player();
	void apuntar(int, int);
	Sprite get_sprite();
};

