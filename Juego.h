#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Objetivos.h"
#include "Vidas.h"
#include "iostream"
#include "ctime"
#include "stdlib.h"


using namespace sf;
using namespace std;


class Juego {

private:

	RenderWindow* ventana;
	Event* evento;
	Clock* reloj;
	Time* tiempo;
	Font font;
	Text texto_uno;
	Text texto_dos;
	Text texto_tres;
	Text texto_gameOver;



	String string_uno;
	String string_dos;
	String string_tres;
	String string_gameOver;


	Color color_rectangulo;
	Color color_menu;
	RectangleShape* rect_jugar;
	RectangleShape* rect_salir;
	RectangleShape* rect_menu;
	FloatRect floatrect_salir;
	FloatRect floatrect_jugar;



	int opcion;
	int inocentes_eliminados;
	int enemigos_eliminados;

	int inocentes_pausa;
	int enemigos_pausa;
	int vidas_pausa;

	Sprite* sp_fondo;
	Texture* tx_fondo;

	Player* mira;
	Objetivos* blanco;
	Vidas* vida;
	Vector2i pos_mouse;
	Vector2f arreglo_posiciones[8];
	int indice_objetivos;



public:
	Juego();
	Juego(int, int, string);
	~Juego();
	void actualizar();
	void dibujar();
	void procesar_eventos();

};