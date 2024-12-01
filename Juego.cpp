#include "Juego.h"

Juego::Juego(int alto_ventana, int ancho_ventana, string nombre_ventana) {
	srand(time(NULL));
	ventana = new RenderWindow(VideoMode(alto_ventana, ancho_ventana), nombre_ventana);
	evento = new Event;
	reloj = new Clock();
	tiempo = new Time();

	color_rectangulo = Color(250, 120, 20, 150);
	color_menu = Color(250, 150, 30, 200);


	font.loadFromFile("medieval.ttf");
	texto_uno.setFont(font);
	texto_dos.setFont(font);
	texto_tres.setFont(font);
	texto_gameOver.setFont(font);


	rect_jugar = new RectangleShape(Vector2f(100, 40));
	rect_salir = new RectangleShape(Vector2f(100, 40));
	rect_menu = new RectangleShape(Vector2f(580, 300));

	arreglo_posiciones[0] = Vector2f(124, 187);
	arreglo_posiciones[1] = Vector2f(267, 182);
	arreglo_posiciones[2] = Vector2f(411, 187);
	arreglo_posiciones[3] = Vector2f(193, 311);
	arreglo_posiciones[4] = Vector2f(271, 311);
	arreglo_posiciones[5] = Vector2f(339, 311);
	arreglo_posiciones[6] = Vector2f(109, 407);
	arreglo_posiciones[7] = Vector2f(427, 413);

	sp_fondo = new Sprite;
	tx_fondo = new Texture;
	tx_fondo->loadFromFile("castillo.png");
	sp_fondo->setTexture(*tx_fondo);

	mira = new Player(300, 450);
	indice_objetivos = rand() % 8;
	blanco = new Objetivos(arreglo_posiciones[indice_objetivos]);
	vida = new Vidas();

	opcion = 2;
	inocentes_eliminados = 0;
	enemigos_eliminados = 0;
	inocentes_pausa = inocentes_eliminados;
	enemigos_pausa = enemigos_eliminados;
	vidas_pausa = vida->consultar_vidas();

	ventana->setMouseCursorVisible(false);
	ventana->setFramerateLimit(60);

	actualizar();
}
Juego::Juego() {

}

Juego::~Juego() {
	delete ventana;
	delete evento;
	delete reloj;
	delete tiempo;
	delete sp_fondo;
	delete tx_fondo;
	delete mira;
	delete blanco;
	delete vida;
	delete rect_jugar;
	delete rect_salir;
	delete rect_menu;
}


void Juego::procesar_eventos() {
	while (ventana->pollEvent(*evento)) {

		pos_mouse.x = Mouse::getPosition(*ventana).x;
		pos_mouse.y = Mouse::getPosition(*ventana).y;
		mira->apuntar(pos_mouse.x, pos_mouse.y);
		if (evento->type == Event::Closed) {
			ventana->close();
		}
		if (evento->type == Event::KeyPressed) {
			if (evento->key.code == Keyboard::Escape) {
				opcion = 2;
				inocentes_pausa = inocentes_eliminados;
				enemigos_pausa = enemigos_eliminados;
				vidas_pausa = vida->consultar_vidas();

			}
		}
		if (evento->type == Event::MouseButtonPressed) {
			if (evento->key.code == Mouse::Left) {//cuando presiona la tecla izquierdaes para elegir una opcion de juego/salida o para disparar
				cout << "Mouse X " << pos_mouse.x << endl;
				cout << "Mouse Y " << pos_mouse.y << endl;
				floatrect_jugar = rect_jugar->getGlobalBounds();
				floatrect_salir = rect_salir->getGlobalBounds();
				if (floatrect_jugar.contains(pos_mouse.x, pos_mouse.y)) {//opcion de jugar
					cout << "eligio jugar" << endl;

					vida->restablecer_vidas(vidas_pausa);
					enemigos_eliminados = enemigos_pausa;
					inocentes_eliminados = inocentes_pausa;

					texto_dos.setCharacterSize(25);
					texto_dos.setFillColor(Color::Black);
					texto_dos.setPosition(175, 10);
					rect_jugar->setPosition(10, 10);
					string_dos = "Puntaje " + to_string(static_cast<int>(enemigos_eliminados - (inocentes_eliminados * 2)));
					texto_dos.setString(string_dos);
					texto_dos.setCharacterSize(20);
					string_tres = "Vidas ";
					texto_tres.setString(string_tres);
					texto_tres.setCharacterSize(20);
					texto_tres.setScale(1.f, 1.f);
					texto_tres.setFillColor(Color::Black);
					texto_tres.setPosition(10, 10);

					rect_salir->setPosition(405, 10);
					texto_uno.setPosition(400, 10);
					texto_uno.setCharacterSize(20);
					texto_uno.setFillColor(Color::Black);

					opcion = 1;
				}
				if (floatrect_salir.contains(pos_mouse.x, pos_mouse.y)) {//opcion de salida
					cout << "eligio salir" << endl;
					opcion = 0;
				}
				for (int i = 0; i < 8; i++) {//chequea si disparo a alguna ventana
					if (pos_mouse.x >= arreglo_posiciones[i].x && pos_mouse.y >= arreglo_posiciones[i].y) {
						if (pos_mouse.x <= arreglo_posiciones[i].x + 64 && pos_mouse.y <= arreglo_posiciones[i].y + 64) {
							cout << "colision en la ventana " << i << endl;
							if (blanco->get_peligrosidad() == false) {//si disparamos a un objetivo no peligroso nos resta una vida
								inocentes_eliminados++;//contador de inocentes eliminados
								cout << "disparo a un inocente" << endl;
								vida->restar_vidas();
							}
							else {
								enemigos_eliminados++;//contador de enemigos eliminados
								cout << "enemigos_eliminados " << enemigos_eliminados << endl;
							}
							indice_objetivos = rand() % 8;
							blanco->cambiar_objetivo(arreglo_posiciones[indice_objetivos]);
							reloj->restart();
						}
					}
				}
			}
		}
	}

}
void Juego::actualizar() {
	while (ventana->isOpen()) {
		*tiempo = reloj->getElapsedTime();

		switch (opcion) {
		case 0://SALIR
			ventana->close();
			break;
		case 1://JUGAR

			string_dos = "Puntaje " + to_string(static_cast<int>(enemigos_eliminados - (inocentes_eliminados * 2)));
			texto_dos.setString(string_dos);

			string_uno = "Reaccion " + to_string(static_cast<float>(2 - (0.005 * enemigos_eliminados)));
			texto_uno.setString(string_uno);
			texto_uno.setScale(1.f, 1.f);
			if (vida->consultar_vidas() == 0) {//consulta si tiene vidas para saber si perdio
				opcion = 2;
				string_gameOver = "GAME OVER";
				texto_gameOver.setString(string_gameOver);
				texto_gameOver.setPosition(50, 310);
				texto_gameOver.setScale(2.2f, 2.2f);
				texto_gameOver.setFillColor(Color::Blue);
				vidas_pausa = 3;
				enemigos_pausa = 0;
				inocentes_pausa = 0;

			}

			if ((tiempo->asSeconds() >= 2 - (0.005 * enemigos_eliminados) && (opcion == 1))) {//el tiempo de reaccion de los enemigos se va reduciendo a medida que los va eliminando, por lo tanto el juego aumenta su dificultad
				if (blanco->get_peligrosidad() == true) {//solo pasa si el objetivo es peligroso
					vida->restar_vidas();//si pasa el tiempo el enemigo dispara y perdemos una vida
				}
				indice_objetivos = rand() % 8;//cada x tiempo cambia el objetivo, eligiendo una posicion aleatoria
				blanco->cambiar_objetivo(arreglo_posiciones[indice_objetivos]);//la funcion cambiar_objetivo se encarga de asignarle el Sprite correspondiente y la posicion nueva
				reloj->restart();
			}
			procesar_eventos();
			dibujar();
			break;
		case 2://PAUSA
			string_uno = "Elimina los arqueros antes de que te disparen,o perderas una vida.\nNo dañes a los inocentes o también perderas una vida.\nEl tiempo de reacción de los arqueros dismunuye con cada\nenemigo que eliminas.\nPresiona escape para pausar.";
			texto_uno.setString(string_uno);
			texto_uno.setFillColor(Color::Black);
			texto_uno.setPosition(10, 10);
			texto_uno.setCharacterSize(20);

			rect_jugar->setPosition(70, 500);
			rect_jugar->setFillColor(color_rectangulo);
			rect_jugar->setOutlineColor(Color::Black);
			rect_jugar->setOutlineThickness(3);

			rect_salir->setPosition(400, 500);
			rect_salir->setFillColor(color_rectangulo);
			rect_salir->setOutlineColor(Color::Black);
			rect_salir->setOutlineThickness(3);

			rect_menu->setPosition(10, 10);
			rect_menu->setFillColor(color_menu);
			rect_menu->setOutlineColor(Color::Black);
			rect_menu->setOutlineThickness(3.0);

			string_tres = "Jugar";
			texto_tres.setString(string_tres);
			texto_tres.setPosition(70, 500);
			string_dos = "Salir";
			texto_dos.setString(string_dos);
			texto_dos.setPosition(400, 500);

			reloj->restart();
			procesar_eventos();
			dibujar();
			break;
		}

	}
}
void Juego::dibujar() {
	ventana->clear(Color::Yellow);
	ventana->draw(*sp_fondo);
	if (opcion == 1) {//solo se dibuja si esta jugando
		ventana->draw(blanco->get_sprite());
		ventana->draw(vida->get_sprite());
	}
	if (opcion == 2) {//solo se dibuja si esta eligiendo una opcion
		ventana->draw(*rect_jugar);
		ventana->draw(*rect_salir);
		ventana->draw(*rect_menu);
		ventana->draw(texto_gameOver);

	}
	ventana->draw(texto_uno);
	ventana->draw(texto_dos);
	ventana->draw(texto_tres);
	ventana->draw(mira->get_sprite());
	ventana->display();

}
