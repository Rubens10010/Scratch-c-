#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boton1.h"
#include "ForFunction.h"
#include "For_Button2.h"

/**
* This Class create a For Button which main function is to repeat a list of executions from buttons of all types
*/

class ButtonFor : public Boton1
{
public:

	ButtonFor(const sf::Vector2f size, sf::RenderWindow &wnd) : Boton1(size, wnd)	/// inherit the Button contructor
	{
		rectangulo.setSize(size);
		CurrentWindow = &wnd;
		triggered = false;
		haveButtonList = false;
		value = 5;	//!< set Initial value of times to iterate.
		contador = 0;	//!< set counter to 0.
	}

	virtual ~ButtonFor();

	void InitializeForButton(const sf::Vector2f &size, sf::Vector2f position);	/// Initialize the three parts of the FOR Button.

	void setTextureForButton(option);	/// Set Texture to the whole button
	void setListObjectToIterate(std::list<recta*> &botones);	/// Set list of object to iterate and execute repeticions.
	void setColor_Fondo(const NormalBotonColor &NB_color);	/// Set Color of button's background (the whole button)
	void setCompiler(Compiler &currentCompiler);	/// Set current compiler to execute functions.
	void setVectordeBoton(std::list<recta*> &rectangulos);	/// Set current vector of buttons (complete list).

	t getContador();	/// Get current counter of repetitions set. default = 0.
	Compiler& getCompiler();	/// Get Current Compiler.

	//void VerifyIfButtonisInside(std::list<recta*> &listButtons);
	//void VerifyPositionBoton(recta* &boton);
	void Update_ForButtonPosition();	/// Update the whole for button position.
	void EjecuteFuntion();	/// Execute Function setted. (repeat a list)
	void InicializarBForSecundario(For_Button2* &boton);	/// Initialize for button type 2.
	void verifyList();	/// Verify if some derived button is not working correctly.
	void restContador();	/// rest -1 to the current counter (means that a repeat cicle has been completed).
	void TriggerFunction();	/// Trigger current Function. (if the button has been clicked then it is repeating the execution of the list iterated)
	void Overed(sf::RenderWindow &ventana);	/// Verify if the button is overed.
	void handler(sf::Event &eventos);	/// Verify all the event which affects this button.
	void drag();	/// Drag some derived for button.

protected:

	virtual void draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;	//!< Override draw function to draw all the drawable objects of this class on screen.
	Linewidth height;	//!< store the height of the third part of the button for to resize when is linked to other buttons.
	sf::RectangleShape for_middle, for_bottom;	//!< rectangle shapes which complete the body of the 'for' button.
	sf::Texture topTexture, middleTexture, bottomTexture;	//!< Textures which stored the images of the button.
	std::list<recta*> *puntero;	//!< pointer to the list to iterate.
	Compiler* compilador;	//!< Pointer to the current Compiler.
	flag triggered;	//!< flag is activated when execute function has been called with a value.
	t contador;	//!< is the current count of function iterate.
};
