#include "SFML/Graphics.hpp"

using namespace sf;

class Vidas {
private:
	int cantidad_vidas;
	Sprite* sp_vidas;
	Texture* tx_vidas;
	IntRect* rectangulo_vidas;
public:
	Vidas();
	~Vidas();
	int consultar_vidas();
	void restar_vidas();
	Sprite get_sprite();
	void restablecer_vidas(int);

};


