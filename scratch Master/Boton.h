#pragma once
#include "recta.h"

/*
*	This Class stores buttons of type Menu Buttons, which are used for manage the differents views of the game.
*/

class Boton : public recta
{
public:

	Boton::Boton(const sf::Vector2f size, sf::RenderWindow &wnd) :recta(size, wnd)	/// Inherit the button constructor.
	{
		isAlive = true;
	}

	~Boton();

	void setPositionRect(sf::Vector2f &position);	/// set Position of the button.
	void setOpcBoton(opcion opcion);	/// set option to change of button.
	void setOpcion(opcion &opc);	/// set option to change of view.

	void handler(sf::Event &eventos);	/// Check events that affect this button.
	void drag();	/// override pure virtual function.
	void Overed(sf::RenderWindow &);	/// check if button is overed.

private:

	void draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;	/// draw all drawable objects.

	std::list<recta*> *rectangulosList;	/// Pointer to the current list of buttons.
	ptropcion opc_Real;	///	pointer to current view option.
	opcion opc_button;	/// store the button option.
};