#pragma once
#include "ForFunction.h"
#include "Boton2.h"

/**
*	This class creates a derived 'for' button type 2 from the class Buttonfor which is kind of a button2
	but has other function and handler for events.
*/

class For_Button2:public Boton2
{
	public:
		For_Button2(const sf::Vector2f size, sf::RenderWindow &wnd) : Boton2(size, wnd)	/// Inherits the buttons2' constructor.
		{
			rectangulo.setSize(size);
			CurrentWindow = &wnd;
			triggered = false;
			value = 0;

			isAlive = false;
			Linked = false;
			estado = true;
			hasListToIterate = false;	
		}

		~For_Button2();

	void setTextureForButton(flag);	///	if true load textures for the whole 'for' button.
	void setListObjectToIterate(std::list<recta*> &botones);	/// set list to iterate when function is triggered.
	void setColor_Fondo(const NormalBotonColor &NB_color);	/// set button's background color.
	void setCompiler(Compiler &currentCompiler);	/// set Current Compiler.
	void setPositionRect(sf::Vector2f &position);	/// set Positon of the main rectangle.
	void set_Live(flag goLive);	/// set if should be alive.

	t getContador();	/// Get counter of iterator of the button; default = 0.

	void InitializeForButton(const sf::Vector2f &size, sf::Vector2f position);	/// Initialize position and size of the button.
	void pushBotonToList(recta *boton);	/// push a rectangle button to the list to compile by this button.
	void Update_ForBotPosition(sf::RectangleShape &CurrentMiddle, sf::RectangleShape &bot);	/// Update Positiion of the body of the button.
	void Update_ForButtonPosition();	/// Update Position of the main rectangle of 'For' Button
	//void VerifyPositionBoton(recta* &boton);
	void restContador();	/// rest 1 from the current iteration count.
	void EjecuteFuntion();	/// Execute Function of 'for' the button.

	void drag();	/// verify if should be dragged.
	void TriggerFunction();	/// trigger function when mouse is release over the button with the current value.
	void Overed(sf::RenderWindow &ventana);	/// verify if is being overed.
	void handler(sf::Event &eventos);	/// verify event which affect this button.

protected:

	virtual void draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;	/// draw all the drawable objects from this class.
	
	t height;	//!< height of the main rectangle of the 'for' button (top).
	sf::RectangleShape for_middle, for_bottom;		//!< Body of the button.
	sf::Texture topTexture, middleTexture, bottomTexture;	//!< textures storing the images for the button.
	std::list<recta*> ListToIterate;	//!< list to iterate when function is triggered.
	Compiler* compilador;	//!< compiler to call for the function.
	flag triggered;	//!< true if function is triggered.
	flag hasListToIterate;	//!< true if a button has been pushed to the iterate list.
	t contador;	//!< counter of the current number of iterations to do.
};

