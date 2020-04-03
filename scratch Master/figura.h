#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Typedefs.h"

using namespace std;

/**
*	This Class render the target image that is currently being handler by all the buttons
	also this class provides basics function to handle the sprite.
*/

class figura
{
public:
	figura(sf::Texture &imagen, sf::Texture &imagen2, sf::Texture &overed, const sf::Vector2f &size);	/// receive the textures and size to draw the current image 
	~figura();

	void setPosicionImagen(t x, t y);	/// setPosition Of target Image.
	void setPosition(sf::Vector2f);	/// setPosition of image at beginning.
	void setScale(sf::Vector2f);	/// setScale of image;

	sf::Sprite& getSprite();	/// return the current image.

	void mover(t x, t y);	/// move x and y steps on the current direction.
	void nextTexture(t x,t y);	/// set Next texture to the image.
	void rotar(t x, t y);	/// rotate x grades.

	void handler(sf::Event &,sf::View);	/// handler events which affects this image.
	void drag();	/// drag this image.

private:
	sf::Texture figura_Textura;	//!< store default start texture.
	sf::Texture next_Textura;	//!< store next texture.
	sf::Texture overed_Textura;	//!< store texture when is overed
	sf::Texture actual_Textura; //!< Store current Texture (should be a smart pointer)
	sf::Sprite sprite_figura; //!< Sprite which stores the current texture.

	sf::Vector2f posicionIm;	//!< position of the image.
	sf::Vector2f ActualViewSize;	//!< size of the view where the image is drawn.
	sf::Vector2f mouseRectOffset;	//!< value to rest the difference with the origin.
	sf::Vector2f workArea; //!< working area to draw the image.

	flag mouseClicked;	//!< true if is clicked.
	flag mouseInsideRect;	//!< true if mouse is inside the image.
	flag dragging;	//!< true if image is being dragged.

	DatosMouse mouseX;	//!< positon of mouse.
	DatosMouse mouseY;

	angle anguloIm; //!< store the current image's angle.
};


