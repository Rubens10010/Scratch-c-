#pragma once
#include "Boton.h"
#include "ControlButtons.h"
#include "figura.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <memory>

using namespace std;

/*
*	This is a manager class is used to initialized all the buttons on the window in order to don't have to initialize then 
	inside the main loop or one by one.
*/

class ButtonFor;

class Lista_Botones
{
public:
	Lista_Botones(NumBotons);	/// Receives the current number of buttons in window to initialize.
	~Lista_Botones();

	void setPosicion_ListaBotones(PosBotons, PosBotons);	/// Set Position where a list of given buttons will start drawing.
	void setPosicion_ListaBotonesM(PosBotons x, PosBotons y);	/// Set Position of list of buttons which controlls views.
	void setListBotonsFont(sf::Font &fuente);	/// set Font for the buttons.
	
	void InicializarListaBotonesMTexto(string(&str)[4]);	/// initialize Vector of strings with a given list of strings to initialize controll buttons.
	void InicializarListaBotonesM(std::vector<std::shared_ptr<Boton>> botones_menu);	/// Initialize a given list of Buttons type 'Button'

	void InicializarListaBotonesTexto(string(&str)[10]);	/// Initialize the vector of strings for the list of buttons.
	void InicializarListaBotones(std::vector<std::shared_ptr<Boton1>> botonesfuncion);	/// Initialize a given list of Buttons type 'Button1'
	
	void Initialize_ForButton(shared_ptr<ButtonFor> buttonFor, sf::Vector2f&, sf::Vector2f&);	/// Initialize a give Button of type 'ButtonFor'
	void setClassOjectPointer(figura *Current_figure);	/// set The Class or imagen target pointed by the buttons.

private:

	NumBotons NumeroBotones;	//!< Number of buttons on window
	PosBotons ejeMx;	//!< Menu Buttons axis x.
	PosBotons ejeMy;	//!< Menu buttons axis y.

	PosBotons eje1x; //!< Rectangle Buttons axis x.
	PosBotons eje1y; //!< Rectangle buttons axis y.
	
	figura *Pointer_figure;	//!< Pointer to target Image.

	std::vector<string> letras;	//!< vector of strings containing the name of the buttons.
	std::vector<string> letrasM; //!< vector of strings containing the name of the Menu buttons.
	sf::Font pointer_to_Font;	//!< contain the font of the buttons.

	flag tienenPosicion;	//!< flags to verify if the list of buttons had an initial position.
	flag tienenPosicionM;
};

