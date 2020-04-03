#include "Figura.h"

figura::figura(sf::Texture &imagen, sf::Texture &imagen2, sf::Texture &overed, const sf::Vector2f &viewSize)
{
	figura_Textura = imagen;
	actual_Textura = imagen;
	overed_Textura = overed;
	next_Textura = imagen2;
	sprite_figura.setTexture(imagen);
	anguloIm = sprite_figura.getRotation();
	ActualViewSize = viewSize;
}

figura::~figura()
{
}

void figura::setPosition(sf::Vector2f s)
{
	posicionIm = s;
	sprite_figura.setPosition(s);
}

void figura::setScale(sf::Vector2f es)
{
	sprite_figura.setScale(es);
	sprite_figura.setOrigin(sprite_figura.getGlobalBounds().width / 2, sprite_figura.getGlobalBounds().height / 2);
}

void figura::nextTexture(t x, t y)
{
	sprite_figura.setTexture(next_Textura);
	figura_Textura = next_Textura;
	next_Textura = actual_Textura;
	actual_Textura = figura_Textura;
}

sf::Sprite& figura::getSprite()
{
	return sprite_figura;
}

void figura::mover(t x, t y)
{
	sprite_figura.move(x*cos(sprite_figura.getRotation()*3.14159265 / 180), y*sin(sprite_figura.getRotation()*3.14159265 / 180));	/// Move on the direction pointed.

	/*
	*	Check all the sides of the working area for collisions
	*	if a collision is found then the image stop moving.
	*/
	if (sprite_figura.getPosition().x <= 0)
	{
		sprite_figura.setPosition(1, sprite_figura.getPosition().y);
	}
	else if (sprite_figura.getPosition().x >= ActualViewSize.x - 10)
	{
		sprite_figura.setPosition(ActualViewSize.x - 10, sprite_figura.getPosition().y);
	}
	else if (sprite_figura.getPosition().y <= 0)
	{
		sprite_figura.setPosition(sprite_figura.getPosition().x, 1);
	}
	else if (sprite_figura.getPosition().y >= ActualViewSize.y - 10)
	{
		sprite_figura.setPosition(sprite_figura.getPosition().x, ActualViewSize.y - 10);
	}
}

void figura::rotar(t x, t y)
{
	sprite_figura.rotate(x);
}

void figura::setPosicionImagen(t x, t y)
{
	posicionIm.x = x;
	posicionIm.y = y;
	setPosition(posicionIm);
}

void figura::drag()
{
	if (dragging == true)
	{
		posicionIm.x = mouseX - mouseRectOffset.x;
		posicionIm.y = mouseY - mouseRectOffset.y;
		this->setPosition(posicionIm);
	}
}

void figura::handler(sf::Event &eventos,sf::View cuadro) // Contains rules to handler events inside the image.
{
	workArea = cuadro.getSize();
	if (eventos.type == sf::Event::MouseButtonPressed && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = true;
		
		if (sprite_figura.getGlobalBounds().contains(sf::Vector2f(eventos.mouseButton.x-2*	workArea.x, eventos.mouseButton.y)))
		{
			sprite_figura.setTexture(overed_Textura);
			mouseInsideRect = true;
			dragging = true;
			mouseRectOffset.x = eventos.mouseButton.x - sprite_figura.getGlobalBounds().left - sprite_figura.getOrigin().x;
			mouseRectOffset.y = eventos.mouseButton.y - sprite_figura.getGlobalBounds().top - sprite_figura.getOrigin().y;
		}
	}

	if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = false;
		dragging = false;
		if (mouseInsideRect)
		{
			sprite_figura.setTexture(actual_Textura);
			mouseInsideRect = false;
		}
	}

	if (eventos.type == sf::Event::MouseMoved)
	{
		mouseX = eventos.mouseMove.x;
		mouseY = eventos.mouseMove.y;
	}
}

