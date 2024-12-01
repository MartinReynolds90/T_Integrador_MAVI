#include "SFML/Graphics.hpp"
#include "ctime"
#include "stdlib.h"
#include "iostream"
using namespace std;
using namespace sf;

class Objetivos {
private:

	Sprite* sp_objetivo;
	Texture* tx_objetivo;
	IntRect* rectangulo_obj;
	Vector2f pos_objetivo;
	int num_peligrosidad;
	bool peligroso;
public:

	Objetivos(Vector2f);
	Objetivos();
	~Objetivos();
	bool get_peligrosidad();
	Vector2f get_position();
	Sprite get_sprite();
	void cambiar_objetivo(Vector2f);
};

