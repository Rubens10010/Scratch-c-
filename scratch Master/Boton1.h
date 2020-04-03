#pragma once
#include "recta.h"
#include "Boton2.h"
#include <memory>

/**
* derived class of rectangle class which inherits its constructor in order to could be placed in a container
  Buttons of type 1 only can be overed, handler and can verify the current list to delete buttons 2. 
*/

class Boton1: public recta
{
public:

	Boton1::Boton1(const sf::Vector2f size, sf::RenderWindow &wnd) :recta(size, wnd)	/// inherits constructor and set live = true
	{
		isAlive = true;	
		haveButtonList = false;
	}

	virtual ~Boton1();

	void setVectordeBoton(std::list<recta*> &rectangulos);	/// set current vector of buttons type 2 holded in a list
	void InicializarBotonSecundario(Boton2* &boton);	/// Initialize new Button 2.
	void verifyList();	/// Verify if some button derived from this class is not working correctly.

	virtual void VerifyPositionBoton(recta* &boton);	/// Verify if a new Button intersect one existent.
	virtual void handler(sf::Event &eventos);	/// Handler event in the wich affects buttons of this type.
	virtual void drag();	/// Drag when Button2 has been created

protected:

	std::list<recta*> *rectangulosList;	//!< List of rectangles(buttons) in the working area.
	flag haveButtonList;	//!< True if has buttons derived from this.
};

