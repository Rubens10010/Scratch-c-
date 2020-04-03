#include "Lista_Botones.h"


Lista_Botones::Lista_Botones(NumBotons n)
:NumeroBotones(n)
{
	//Empty momently
}


Lista_Botones::~Lista_Botones()
{
}

void Lista_Botones::setPosicion_ListaBotones(PosBotons x, PosBotons y)
{
	eje1x = x;
	eje1y = y;
	tienenPosicion = true;
}

void Lista_Botones::InicializarListaBotonesTexto(string(&str)[10])
{
	for (t i = 0; i < NumeroBotones; i++)
	{
		letras.push_back(str[i]);
	}
}

void Lista_Botones::InicializarListaBotones(std::vector<std::shared_ptr<Boton1>> botones_imagen)
{
	if (tienenPosicion)
	{
		for (t i = 0; i < NumeroBotones; i++){

			botones_imagen[i]->setFuente(pointer_to_Font);
			botones_imagen[i]->setCadena_Texto(letras[i]);

			botones_imagen[i]->setPositionRect(sf::Vector2f(eje1x, eje1y));
			botones_imagen[i]->UpdateRectSizeIfText();
			botones_imagen[i]->setColor_Fondo(sf::Color(28,134,238,255));
			botones_imagen[i]->setColor_Texto(sf::Color(255, 255, 255));

			botones_imagen[i]->setColor_FondoOvered(sf::Color(0,180,10,200));
			botones_imagen[i]->setColor_TextoRSB(sf::Color(255, 255, 0,255));
			botones_imagen[i]->setClassObjectPointedTo(Pointer_figure);
			if (i % 2 == 0)
			{
				eje1x += 185;
			}
			else
			{
				eje1x -= 185;
				eje1y += 75;
			}
			//eje1y += 50;
		}
	}

	else
	{
		throw EXIT_FAILURE;
	}
}
void Lista_Botones::setClassOjectPointer(figura *Current_figure)
{
	Pointer_figure = Current_figure;
}

void Lista_Botones::setListBotonsFont(sf::Font &fuente)
{
	pointer_to_Font = fuente;
}
//◘◘◘◘◘◘◘◘◘◘◘◘◘◘---◘◘◘◘◘◘◘◘◘◘◘◘ ◘◘◘◘◘◘◘◘◘◘◘◘◘◘---◘◘◘◘◘◘◘◘◘◘◘◘ ◘◘◘◘◘◘◘◘◘◘◘◘◘◘---◘◘◘◘◘◘◘◘◘◘◘◘

void Lista_Botones::setPosicion_ListaBotonesM(PosBotons x, PosBotons y)
{
	ejeMx = x;
	ejeMy = y;
	tienenPosicionM = true;
}

void Lista_Botones::InicializarListaBotonesMTexto(string(&str)[4])
{
	for (t i = 0; i < 4; i++)
	{
		letrasM.push_back(str[i]);
	}
}

void Lista_Botones::InicializarListaBotonesM(std::vector<std::shared_ptr<Boton>> botones_menu)
{
	if (tienenPosicionM)
	{
		for (t i = 0; i < 4; i++){

			botones_menu[i]->setFuente(pointer_to_Font);
			botones_menu[i]->setCadena_Texto(letrasM[i]);

			botones_menu[i]->setPositionRect(sf::Vector2f(ejeMx, ejeMy));

			botones_menu[i]->setColor_Fondo(sf::Color(72, 166, 50, 200));
			botones_menu[i]->setColor_Texto(sf::Color(255, 255, 255));
			botones_menu[i]->setAncho_Borde(2.f);
			botones_menu[i]->setColor_Borde(sf::Color(255, 255, 255)); //168, 219, 168

			botones_menu[i]->setColor_FondoOvered(sf::Color(217, 227, 78, 150));
			botones_menu[i]->setColor_TextoRSB(sf::Color(255, 255, 0, 255));
			botones_menu[i]->setColor_BordeRSB(sf::Color(255, 255, 255));
			
			if (i%2==0)
			{
				ejeMx += 150;
			}
			else
			{
				ejeMx -= 150;
				ejeMy += 50;
			}
		}
	}

	else
	{
		throw EXIT_FAILURE;
	}
}

void Lista_Botones::Initialize_ForButton(shared_ptr<ButtonFor> buttonFor, sf::Vector2f& size, sf::Vector2f& position)
{
	buttonFor->InitializeForButton(size, position);
	buttonFor->setFuente(pointer_to_Font);
	buttonFor->setCadena_Texto("REPEAT");
	buttonFor->setButtonType("forButton");

	buttonFor->setPositionRect(position);
	buttonFor->UpdateRectSizeIfText();
	buttonFor->setColor_Fondo(sf::Color(236, 183, 37));
	buttonFor->setColor_Texto(sf::Color(255, 255, 255));

	buttonFor->setColor_FondoOvered(sf::Color(0, 180, 10, 200));
	buttonFor->setColor_TextoRSB(sf::Color(255, 255, 0, 255));
}