#include "Boton2.h"


Boton2::~Boton2()
{
	Cursor->deleteElementatPosition(PositionCursorInButton);
}

void Boton2::handler(sf::Event &eventos)
{
	if (isAlive)
	{
		if (eventos.type == sf::Event::MouseButtonPressed && eventos.mouseButton.button == sf::Mouse::Left)
		{
			mouseClicked = true;
			if (mouseInsideRect)
			{
				dragging = true;
				mouseRectOffset.x = eventos.mouseButton.x - this->getRectangulo()->getGlobalBounds().left - this->getRectangulo()->getOrigin().x;
				mouseRectOffset.y = eventos.mouseButton.y - this->getRectangulo()->getGlobalBounds().top - this->getRectangulo()->getOrigin().y;
			}
		}

		if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
		{
			mouseClicked = false;
			//dragging = false;
		
			if (mouseInsideRect)	// Si el mouse seguia sobre el boton cuando fue liberado y el boton tiene una funcion
			{
				(imagen_ptr->*funcionpointerclass)(datox, datoy);	//llama a la funcion apuntada por pointerclass
				mouseInsideRect = false;

				if (dragging){
					if (area->getGlobalBounds().intersects(this->getRectangulo()->getGlobalBounds()) == false) //is is outside the rectangle area state == false to delete
					{
						dragging = false;
						setEstado(false);
					}
					else
					{
						dragging = false;
						setEstado(true);
						//VerifyPositionThisBoton();
					}
				}
			}
		}

		if (eventos.type == sf::Event::KeyPressed)
		{
			if (CursorInButton && hasValue && mouseInsideRect)
			{
				Cursor->deleteElementatPosition(PositionCursorInButton);
				setNormalSize();
				hasValue = false;
			}

			if (eventos.key.code == sf::Keyboard::Return && CursorInButton && Cursor != nullptr)
			{
				setFuncion_value(Cursor->GetCurrentValue());	// should be const
				PositionCursorInButton = Cursor->GetCursorPosition();
				ValueTextWidth = Cursor->getCurrentTextSize().width;
				hasValue = true;
			}
		}
		if (eventos.type == sf::Event::TextEntered && CursorInButton)
		{
			if (Cursor->GetCursorPosition().x + Cursor->getCurrentTextSize().width > TextRect.getPosition().x + TextRect.getSize().x - 10)	//agrandar
			{
				rectangulo.setSize(sf::Vector2f(rectangulo.getSize().x + 10, rectangulo.getSize().y));	//update sizes
				TextRect.setSize(sf::Vector2f(TextRect.getSize().x + 10, TextRect.getSize().y));
				resized = true;
			}
			if (eventos.text.unicode == 8 && resized)
			{
				if (rectangulo.getSize().x > normalRectSize.x)	//if greater than normal and delete text then resize less
				{
					rectangulo.setSize(sf::Vector2f(rectangulo.getSize().x - 10, rectangulo.getSize().y));	//update resize
					TextRect.setSize(sf::Vector2f(TextRect.getSize().x - 10, TextRect.getSize().y));
				}
				else //else is less or equal than normal so place normal size
				{
					setNormalSize();
				}
			}
		}

		if (eventos.type == sf::Event::MouseMoved)
		{
			mouseX = eventos.mouseMove.x;
			mouseY = eventos.mouseMove.y;
		}

	}
}


void Boton2::drag()
{
	if (isAlive){
		if (dragging == true)
		{
			this->setPositionRect(sf::Vector2f(mouseX - mouseRectOffset.x, mouseY - mouseRectOffset.y));
			Cursor->setPositionOfTextatPosition(PositionCursorInButton, Cursor->GetCursorPosition());
			PositionCursorInButton = Cursor->GetCursorPosition();
		}
	}
}

void Boton2::setEstado(flag place)
{
	estado = place;
}

flag Boton2::getEstado()
{
	return estado;
}

void Boton2::set_Live(flag goLive)
{
	isAlive = goLive;
	activateNewTexture();
}

void Boton2::activateNewTexture()
{
	ButtonActive.loadFromFile("Button4.png");
	rectangulo.setTexture(&ButtonActive);
}

void Boton2::setLinked(flag newLink)
{
	Linked = newLink;
}

flag Boton2::isLinked()
{
	return Linked;
}

void Boton2::setNextBoton(recta &NextButton)
{
	Next = &NextButton;
}

recta* Boton2::getNextBoton()
{
	return Next;
}

void Boton2::setVectordeBoton(std::list<recta*> &rectangulos)
{
	rectangulosList = &rectangulos;
}

void Boton2::VerifyPositionThisBoton()
{
	/*if (rectangulosList->size() > 1)
	{
		for (auto &es : *rectangulosList)
		{
			if (es == rectangulosList->back())
			{
				break;
			}
			if (this->getRectangulo()->getGlobalBounds().intersects(es->getRectangulo()->getGlobalBounds()))
			{
				if (es->isLinked())
				{
					this->setPositionRect(sf::Vector2f(es->getNextBoton()->getPosicionRect().x, es->getNextBoton()->getPosicionRect().y + es->getNextBoton()->getRectangulo()->getSize().y - 7));
				}
				break;
			}
			es++;
		}
	}*/
}