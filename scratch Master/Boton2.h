#pragma once
#include "recta.h"

/**
* derived class of rectangle class which inherits its constructor in order to could be placed in a container
Buttons of type 2 can be dragged inside the working and trigger function pointed to.
Buttons of this type are stored following a secuence if they are intersected with others.
*/

class Boton2 : public recta
{
public:

	Boton2(const sf::Vector2f size, sf::RenderWindow &wnd) : recta(size, wnd)	/// Contruct new button of type 2 inheriting from rectangle
	{
		isAlive = false; //!< hasn't lived yet
		Linked = false;	//!< Is not linked to another button
		estado = true;	//!< Is working correctly
	}
	virtual ~Boton2();

	void setVectordeBoton(std::list<recta*> &rectangulos);	/// Set vector of buttons to verify if intersec some.
	void setNextBoton(recta &NextButton);	/// set if is linked, the next Boton.
	void setLinked(flag);	/// Function: true if is linked to another boton.
	virtual void setEstado(flag);	/// Set state, true if is working correctly inside the working area.
	virtual void set_Live(bool goLive);	/// Set if should start living

	virtual flag getEstado();	/// get Current State
	recta* getNextBoton();	/// get Button linked to.
	flag isLinked();	/// return true if is linked to another button.

	void VerifyPositionThisBoton();	/// Verify position of this button if intersect another set new Position.

	virtual void activateNewTexture();	/// Activate texture when is set to live
	virtual void handler(sf::Event &eventos);	/// handle all event which affects this button.
	virtual void drag();	/// drag this button.


protected:

	flag estado;	//!< True or false depending on whether it is working correctly or not
	flag Linked;	//!< True or false depending on whether is linked or not
	sf::Texture ButtonActive;	//!< Texture when button is alive
	std::list<recta*> *rectangulosList;	//!< pointer to current list of rectangles.
	recta *Next;	//!< Pointer to button button linked.
};

