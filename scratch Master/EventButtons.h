#pragma once
#include "recta.h"
#include "Compiler.h"
#include <memory>

/**
* This Class Creates buttons which controlls the current execution of the program and list of buttons.
	is mainly formed for two button one for execute and another one to stop execution.
*/

class EventButtons:public recta
{
public:

	EventButtons::EventButtons(const sf::Vector2f size, sf::RenderWindow &wnd) :recta(size, wnd)	/// Inherits the rectangle button constructor.
	{
		isExecuting = false;
		openTextures();
	}

	~EventButtons();

	void setCompiler(Compiler &currentCompiler);	/// Set the current program's compiler.
	void SetImageValues(const sf::Vector2f pos);	/// Set Position to draw the buttons.

	Compiler& getCompiler();	/// Return current Compiler.

	void openTextures();	/// Load Textures in orden to draw them
	void handler(sf::Event &eventos);	/// manage events on the current render window which affects this buttons.
	void drag();	/// drag (is being override because of virtual pure function)
	void Overed(sf::Window &ventana);	/// verify if it is overed.
	void stopButtonOvered(sf::Window &ventana);	/// Verify if stop button is overed.

private:

	void draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;	/// Draw drawable object.

	flag isExecuting;	//!< true if a execution is in proccess.
	flag mouseInsideStopSprite;	//!< true if mouse is inside stop button.

	sf::Sprite startSprite;	//!< sprite and textures for the 'flag' Button.
	sf::Texture	startTexture;
	sf::Texture overedStartTexture;
	TexturePointer Current_flagTexture;

	sf::Sprite stopSprite;	//!< sprite and textures for the 'stop' button.
	sf::Texture	stopTexture;
	sf::Texture overedStopTexture;
	TexturePointer Current_stopTexture;

	Compiler* compilador;	//!< Pointer to the current Compiler.
};

