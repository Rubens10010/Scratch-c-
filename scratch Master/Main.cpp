#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <exception>
#include <functional>
#include <memory>
#include "recta.h"
#include "Boton.h"
#include "Boton1.h"
#include "Lista_Botones.h"
#include "Figura.h"
#include "EventButtons.h"
#include "WriteText.h"
#include "ControlButtons.h"

sf::Clock myClock; // Text Clock

//C++ program entry point
int main()
{	
	//Creating the window
	sf::RenderWindow window(sf::VideoMode(1024, 600), "Scratch V3.0Beta");

	//Settign the framerate limit to 60 FPS
	window.setFramerateLimit(100);
	window.setKeyRepeatEnabled(false);

	//Variable that keeps the game loop running
	NumBotons nb = 10;
	opcion opc=0;

	//Views of the current Window
	sf::View viewLefttop(sf::FloatRect(0, 0, window.getSize().x / 3, window.getSize().y/4));
	viewLefttop.setViewport(sf::FloatRect(0, 0, 0.3333333333333333333333333333333333333333333333333333333, 0.25));

	sf::View viewLeft(sf::FloatRect(0, 0, window.getSize().x*2/ 3, window.getSize().y));
	viewLeft.setViewport(sf::FloatRect(0, 0, 0.666666666666666666666666666666666666666666, 1));

	sf::View viewRight(sf::FloatRect(0, 0, window.getSize().x/3, window.getSize().y));
	viewRight.setViewport(sf::FloatRect(0.66666666666, 0, 0.34, 1));

	//Event object holding all events
	sf::Event event;

	std::string lista[] = { "ROTATE RIGHT", "ROTATE LEFT", "POSITION", "NEXT COSTUME", "MOVE", "MOVE", "MOVE", "MOVE", "MOVE", "MOVE" }; //Lista de textos de los botones
	std::string listaM[] = { "MOTION", "LOOKS", "SOUNDS", "CONTROL" };
	//loading textures
	sf::Texture mytext, nextTEXT, overed, ButtonT;
	if (!mytext.loadFromFile("zeus1.gif") || !nextTEXT.loadFromFile("zeus2.gif") || !overed.loadFromFile("zeusovered.gif") || !ButtonT.loadFromFile("Button2.png"))
	{
		cout << "no se encontro el archivo" << endl;
	}

	sf::Sprite Background1, Background2, Background3;	//Load and set Background of the window
	sf::Texture Back1, Back2 ,Back3;
	if (!Back1.loadFromFile("Fondo.png") || !Back2.loadFromFile("Fondo2.png") || !Back3.loadFromFile("Fondo3.png"))
	{
		cout << "no se encontro el archivo" << endl;
	}

	Background1.setTexture(Back1);
	Background1.setScale(sf::Vector2f(1.7, 1.5));

	Background2.setTexture(Back2);
	Background2.setScale(sf::Vector2f(1.7, 1.5));

	Background3.setTexture(Back3);
	Background3.setScale(sf::Vector2f(0.43, 0.34));

	//Font
	sf::Font Fuent;
	if (!Fuent.loadFromFile("contb.ttf"))
	{
		cout << "Couldn't open the font" << endl;
	}

	//Rectangle that handle the Buttons created when a button is dragged
	sf::RectangleShape square;
	square.setPosition(window.getSize().x /2.5, 20);
	square.setSize(sf::Vector2f(viewLeft.getSize().x/3, viewLeft.getSize().y-40));
	square.setFillColor(sf::Color(255, 255, 255, 150));
	square.setOutlineColor(sf::Color(0, 0, 0, 255));
	square.setOutlineThickness(1.f);

	//Objects running
	Compiler compiler;	//compiler for all the events

	std::shared_ptr<ButtonFor> for_button(new ButtonFor(sf::Vector2f(150, 40), window));

	WriteText ScratchTexts(nb);
	ScratchTexts.LoadFont();

	std::vector<std::shared_ptr<Boton1>> botones;
	std::list<recta*> rectangulos;
	std::vector<std::shared_ptr<Boton>> botonesM;//botones menu

	Lista_Botones Botones_init(nb);
	figura *imagen = new figura(mytext, nextTEXT, overed, viewRight.getSize());
	EventButtons FlagButton(sf::Vector2f(100, 40),window);

	imagen->setScale(sf::Vector2f(1,1));

	auto call_foo = std::mem_fn(&figura::setPosition);
	call_foo(imagen, sf::Vector2f(100, 200));

	//pointers to Funtions
	void(figura::*funcion1)(int, int) = &figura::mover; //Puntero a funcion miembro de figura que recibe dos int
	void(figura::*funcion2)(int, int) = &figura::rotar;
	void(figura::*funcion3)(int, int) = &figura::setPosicionImagen;
	void(figura::*funcion4)(int, int) = &figura::nextTexture;

	//Initializing le list
	Botones_init.setPosicion_ListaBotones(50,175);

	for (auto i = 0; i < nb; i++)
	{
		std::shared_ptr<Boton1> newBoton1(new Boton1(sf::Vector2f(100, 30), window));
		botones.push_back(std::move(newBoton1));
		botones[i]->setVectordeBoton(rectangulos);
		botones[i]->setFuncion_Figura(funcion1, 10, 10);
		botones[i]->setFuncion_Area(square);
		botones[i]->setCursor(ScratchTexts);
		botones[i]->setTextureRectangle(&ButtonT);
		botones[i]->setButtonType("Button1");
	}

	botones[0]->setFuncion_Figura(funcion2, 10, 0);
	botones[1]->setFuncion_Figura(funcion2, -30, 0);
	botones[2]->setFuncion_Figura(funcion3, 50, 50);
	botones[3]->setFuncion_Figura(funcion4, 10, 10);

	Botones_init.setClassOjectPointer(imagen);
	Botones_init.setListBotonsFont(Fuent);
	
	Botones_init.setPosicion_ListaBotonesM(55, 30);

	for (auto i = 0; i < 4; i++)
	{
		std::shared_ptr<Boton> newBoton(new Boton(sf::Vector2f(100, 40), window));
		botonesM.push_back(std::move(newBoton));
		botonesM[i]->setOpcBoton(i);
		botonesM[i]->setOpcion(opc);
		botonesM[i]->setButtonType("Button");
	}

	try //Si La lista no tiene Una posicion establecida no ejecuta el programa y manda un error
	{
		Botones_init.InicializarListaBotonesTexto(lista);
		Botones_init.InicializarListaBotones(botones);

		Botones_init.InicializarListaBotonesMTexto(listaM);
		Botones_init.InicializarListaBotonesM(botonesM);

		Botones_init.Initialize_ForButton(for_button,sf::Vector2f(140, 35), sf::Vector2f(150, 200));
	}
	catch (exception &e)
	{
		cout << "Exception throw during Botons Initialization" << endl;
		return 0;
	}

	for_button->setCursor(ScratchTexts);
	for_button->setCompiler(compiler);
	for_button->setVectordeBoton(rectangulos);
	for_button->setFuncion_Area(square);

	FlagButton.setCompiler(compiler);
	FlagButton.setButtonType("flagButton");
	ScratchTexts.UpdateObjectsInScreen(true);
	//Game loop
	while (window.isOpen())
	{
		//EVENTS
		while (window.pollEvent(event))
		{
			//LMB Pressed
			ScratchTexts.Handler_Update(event, window);
			imagen->handler(event,viewRight);
			for (auto es : botonesM)
			{
				es->handler(event);
			}
			switch (opc)
			{
				case 0:	
						{
							for (auto es : botones)
								es->handler(event);
							break;
						}
				case 1:	{
							break;
						}
				case 2:	{
							break;
						}
				case 3:	{
							//for_button->setListObjectToIterate(rectangulos);
							for_button->handler(event);
							break;
						}
				default:
					break;
			}

			for (auto es : rectangulos)
					es->handler(event);

			FlagButton.handler(event);
			//Event type is window closed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		ScratchTexts.UpdateAll_Text(window, myClock);
		//FlagButton.Update(rectangulos);
		FlagButton.Overed(window);
		imagen->drag();
		//LOGIC
		for (auto es : botonesM)
		{
			es->Overed(window);
		}
		switch (opc)
		{
			case 0:
					for (auto es : botones)
					{
						es->Overed(window);
						es->drag();
					}

			case 3:{
					   for_button->drag();
					   for_button->Overed(window);
					   for_button->TriggerFunction();
					}
			default:
				break;
		}

		for (auto bot : rectangulos)
		{	
			bot->Overed(window);
			bot->drag();			
		}

		//RENDERING
		window.clear();
		window.setView(viewLeft);
		window.draw(Background1);
		window.draw(square);

		switch (opc)
		{
			case 0:
				for (auto es : botones)
				{
					window.draw(*es);
				}
				break;
			case 1:
				window.draw(imagen->getSprite());
				break;
			case 3:
				window.draw(*for_button);
			default:
				break;
		}

		for (auto it : rectangulos)
		{
			window.draw(*it);
		}

		window.draw(ScratchTexts);
		window.draw(FlagButton);
		window.setView(viewLefttop);
		window.draw(Background3);

		for (auto x : botonesM)
		{
			window.draw(*x);
		}

		window.setView(viewRight);
		window.draw(ScratchTexts);
		window.draw(Background2);
		window.draw(imagen->getSprite());
		window.display();
	}
	///////////

	for (auto es : rectangulos)
	{
		delete es;
	}

	//Close the program
	return 0;
}