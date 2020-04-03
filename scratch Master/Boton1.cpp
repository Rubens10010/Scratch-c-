#include "Boton1.h"

Boton1::~Boton1()
{
}

void Boton1::handler(sf::Event &eventos)
{
	if (eventos.type == sf::Event::MouseButtonPressed && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = true;
		if(mouseInsideRect)
		{
			dragging = true;
			mouseRectOffset.x = eventos.mouseButton.x - this->getRectangulo()->getGlobalBounds().left - this->getRectangulo()->getOrigin().x;
			mouseRectOffset.y = eventos.mouseButton.y - this->getRectangulo()->getGlobalBounds().top - this->getRectangulo()->getOrigin().y;
			
			//if (clickHoldTime == sf::seconds(2.f)){
			//Boton2* nuevoBoton = new Boton2(this->getRectangulo()->getSize(), *CurrentWindow);
			Boton2* nuevoBoton = new Boton2(this->rectangulo.getSize(), *CurrentWindow);
			InicializarBotonSecundario(nuevoBoton);
			rectangulosList->push_back(std::move(nuevoBoton));
			haveButtonList = true;			
		}
	}

	if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = false;
		dragging = false;
		if (haveButtonList && mouseInsideRect){
			
			if (rectangulosList->back()->getRectangulo()->getGlobalBounds().intersects(this->getRectangulo()->getGlobalBounds()))//si el nuevo boton interseca con alguno de los anteriores botones
			{
				rectangulosList->pop_back();
				haveButtonList = false;
			}
			else if (area->getGlobalBounds().intersects(rectangulosList->back()->getRectangulo()->getGlobalBounds()) == false)// si el boton no interseca con el rectangulo blanco
			{
				rectangulosList->pop_back();
				haveButtonList = false;
			}
			else if (rectangulosList->back()->getRectangulo()->getGlobalBounds().contains(eventos.mouseButton.x, eventos.mouseButton.y))
			{
				Cursor->UpdateObjectsInScreen(true);
				VerifyPositionBoton(rectangulosList->back());
				rectangulosList->back()->set_Live(true);
				dragging = false;
			}
		}

		if (mouseInsideRect)	// Si el mouse seguia sobre el boton cuando fue liberado y el boton tiene una funcion
		{
			/*if (TieneFuncionNormal && m_FuncionDesencadenante != nullptr)
			{
				m_FuncionDesencadenante();
			}*/
			//(imagen_ptr->*funcionpointerclass)(datox, datoy);	//llama a la funcion apuntada por pointerclass
			EjecuteFuntion();
		}
		
	}

	if (eventos.type == sf::Event::MouseMoved)
	{
		mouseX = eventos.mouseMove.x;
		mouseY = eventos.mouseMove.y;
	}

	if (eventos.type == sf::Event::KeyPressed)
	{
		if (CursorInButton && hasValue && mouseInsideRect)
		{
			Cursor->deleteElementatPosition(PositionCursorInButton);	// delete current Text value in orden to put other
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

	verifyList();
}

void Boton1::drag()
{
	if (dragging == true)
	{
		rectangulosList->back()->setPositionRect(sf::Vector2f(mouseX - mouseRectOffset.x, mouseY - mouseRectOffset.y));
	}
}

void Boton1::setVectordeBoton(std::list<recta*> &rectangulos)
{
	rectangulosList = &rectangulos;
}

/*void Boton1::setPositionRect(float x, float y)
{
	rectangulo.setPosition(x, y);
	update_strings();
}
*/
void Boton1::InicializarBotonSecundario(Boton2* &boton)
{
	boton->setFuente(*m_fuente);
	boton->setCadena_Texto(this->m_texto.getString());
	boton->setPositionRect(getPosicionRect());
	boton->setColor_Fondo(sf::Color(28, 134, 238, 255));
	boton->setColor_Texto(sf::Color(255, 255, 255));
	boton->setButtonType(this->getButtonType());

	boton->setColor_FondoOvered(sf::Color(0, 180, 10, 200));
	boton->setColor_TextoRSB(sf::Color(255, 255, 0, 255));
	boton->UpdateRectSizeIfText();
	boton->setTextureRectangle(this->rectangulo.getTexture());
	boton->setClassObjectPointedTo(this->imagen_ptr);
	boton->setFuncion_Figura(this->funcionpointerclass, value, datoy);
	boton->setFuncion_Area(*area);
	boton->setCursor(*Cursor);
}

void Boton1::verifyList()
{
	if (haveButtonList)
	{
		for (std::list<recta*>::iterator es = rectangulosList->begin(); es != rectangulosList->end();)
		{
			if ((*es)->getEstado() == false) // if buttons is outside the rectangle area then delete it
			{
				if (rectangulosList->size() == 1)//si hay un solo elemento en la lista
				{
					Cursor->deleteElementatPosition((*es)->getCursorInButtonPosition());
					es = rectangulosList->erase(es);
					Cursor->UpdateObjectsInScreen(false);
					haveButtonList = false;
					break;
				}
				else //si hay mas
				{
					Cursor->deleteElementatPosition((*es)->getCursorInButtonPosition());
					es = rectangulosList->erase(es);
					Cursor->UpdateObjectsInScreen(false);
					break;
				}
			}
			else
				++es;
		}
	}
}

/*flag Boton1::getEstado()
{
	return mouseClicked;
}*/

void Boton1::VerifyPositionBoton(recta* &boton)
{
	for (std::list<recta*>::iterator es = rectangulosList->begin(); es != rectangulosList->end();)
	{
		if ((*es) == rectangulosList->back())
		{
			break;
		}

		if (boton->getRectangulo()->getGlobalBounds().intersects((*es)->getRectangulo()->getGlobalBounds()))
		{
			(*es)->setLinked(true);
	
			if ((*es)->getButtonType() == "forButton")
			{
				if ((*es)->getNextBoton() != NULL)
				{
					recta* next = (*es);
					while (next->getNextBoton() != NULL)
					{
						next = next->getNextBoton();
						cout << "mas abajo" << endl;
					}
					boton->setPositionRect(sf::Vector2f(next->getPosicionRect().x, next->getPosicionRect().y + next->getRectangulo()->getSize().y-7));
					next->setNextBoton(*boton);
					(*es)->pushBotonToList(boton);
					//delete[]next;
				}
				else
				{
					boton->setPositionRect(sf::Vector2f((*es)->getPosicionRect().x + 15, (*es)->getPosicionRect().y + (*es)->getRectangulo()->getSize().y - 6));
					(*es)->pushBotonToList(boton);
					(*es)->setNextBoton(*boton);
				}
			}
			else
			{
				boton->setPositionRect(sf::Vector2f((*es)->getPosicionRect().x, (*es)->getPosicionRect().y + (*es)->getRectangulo()->getSize().y - 7));
				(*es)->setNextBoton(*boton);
			}
			break;
		}
		es++;
	}
}
