#include "ControlButtons.h"

ButtonFor::~ButtonFor()
{
}

void ButtonFor::InitializeForButton(const sf::Vector2f &size,sf::Vector2f position)
{

	setTamaño(size);
	setPositionRect(position);

	for_middle.setSize(sf::Vector2f(22, size.y-20));
	for_middle.setPosition(rectangulo.getPosition().x, rectangulo.getPosition().y + rectangulo.getSize().y);


	for_bottom.setSize(rectangulo.getSize());
	for_bottom.setPosition(for_middle.getPosition().x, for_middle.getPosition().y + for_middle.getSize().y);

	setTextureForButton(true);

	height = rectangulo.getGlobalBounds().height;
	isAlive = true;
}

void ButtonFor::setColor_Fondo(const NormalBotonColor &NB_color)
{
	b_ColorFondo = NB_color;	// Guarda el color en el una variable
	rectangulo.setFillColor(NB_color);	// Establece el color del fondo
	for_middle.setFillColor(NB_color);
	for_bottom.setFillColor(NB_color);
}

void ButtonFor::setTextureForButton(option texture)
{
	if (texture)
	{
		topTexture.loadFromFile("for_Top.png");
		rectangulo.setTexture(&topTexture);

		middleTexture.loadFromFile("for_Middle.png");
		for_middle.setTexture(&middleTexture);

		bottomTexture.loadFromFile("for_Bottom.png");
		for_bottom.setTexture(&bottomTexture);
		cout << "puse texture" << endl;
	}
}

void ButtonFor::Overed(sf::RenderWindow &ventana)	//Este manejador solo detecta cuando el puntero esta sobre un boton y da el efecto correspondiente
{
	if (rectangulo.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(ventana))) || for_middle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(ventana))) || for_bottom.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(ventana))))// Verifica si el boton contiene la posicion del mouse
	{
		Cursor->setState(true); 
		mouseInsideRect = true;

		m_texto.setColor(sobreB_ColorTexto);	//cambia los parametros a sus valores cuando el boton esta siendo pasado por el mouse
		rectangulo.setFillColor(sobreB_ColorFondo);
		for_middle.setFillColor(sobreB_ColorFondo);
		for_bottom.setFillColor(sobreB_ColorFondo);
	}
	else
	{
		Cursor->setState(false);

		if (!mouseClicked)
			mouseInsideRect = false;

		if (m_texto.getColor() != b_ColorTexto)	// si el puntero ya no esta en el boton, entonces debemos cambiar los valores a los normales
		{
			m_texto.setColor(b_ColorTexto);
			rectangulo.setFillColor(b_ColorFondo);
			for_middle.setFillColor(b_ColorFondo);
			for_bottom.setFillColor(b_ColorFondo);
		}
	}

	if (rectangulo.getGlobalBounds().contains(Cursor->GetCursorPosition().x, Cursor->GetCursorPosition().y + 20) ||
		for_middle.getGlobalBounds().contains(Cursor->GetCursorPosition().x, Cursor->GetCursorPosition().y + 20) ||
		for_bottom.getGlobalBounds().contains(Cursor->GetCursorPosition().x, Cursor->GetCursorPosition().y + 20))// Verifica si el boton contiene la posicion del mouse
	{
		CursorInButton = true;
		Cursor->setCursorPosition(sf::Vector2f(TextRect.getPosition().x + 1, TextRect.getGlobalBounds().top + TextRect.getGlobalBounds().height - Cursor->GetCursorSize() - 3));
	}
	else
	{
		if ((!hasValue || Cursor->GetCursorPosition().x + ValueTextWidth < TextRect.getPosition().x + normalTextRectSize.x - 5) && Cursor->getState() == true)
		{
			//setNormalSize();
		}
		CursorInButton = false;
	}
}

void ButtonFor::handler(sf::Event &eventos)
{

	if (eventos.type == sf::Event::MouseButtonPressed && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = true;
		if (mouseInsideRect)
		{
			dragging = true;
			//triggered = true;
			mouseRectOffset.x = eventos.mouseButton.x - this->getRectangulo()->getGlobalBounds().left - this->getRectangulo()->getOrigin().x;
			mouseRectOffset.y = eventos.mouseButton.y - this->getRectangulo()->getGlobalBounds().top - this->getRectangulo()->getOrigin().y;

			//create new For
			For_Button2* nuevoBoton = new For_Button2(this->rectangulo.getSize(), *CurrentWindow);
			InicializarBForSecundario(nuevoBoton);
			rectangulosList->push_back(std::move(nuevoBoton));
			haveButtonList = true;
		}
	}

	if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = false;
		dragging = false;
		
		if (haveButtonList && mouseInsideRect && rectangulosList->size() > 0 ){

			if (rectangulosList->back()->getRectangulo()->getGlobalBounds().intersects(this->getRectangulo()->getGlobalBounds()))//si el nuevo boton interseca con alguno de los anteriores botones
			{
				cout << "Pop Back" << endl;
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

		if (mouseInsideRect)	
		{
			//EjecuteFuntion();
			if (contador == 0)
			{
				contador = value;
			}
			triggered = true;
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

	verifyList();
}

void ButtonFor::TriggerFunction()
{
	if(triggered && contador !=0 )	//!< if mouse was inside the button when was released and triggered a for function
	{
		try
		{
			EjecuteFuntion();
			restContador();
		}
		catch (invalid_argument& e)
		{
			contador = 0;
		}
	}
}


void ButtonFor::drag()
{
	if (dragging == true)
	{
		rectangulosList->back()->setPositionRect(sf::Vector2f(mouseX - mouseRectOffset.x, mouseY - mouseRectOffset.y));
		rectangulosList->back()->Update_ForButtonPosition();
	}
}

void ButtonFor::Update_ForButtonPosition()
{
	for_middle.setPosition(rectangulo.getPosition().x, rectangulo.getPosition().y + rectangulo.getSize().y);
	for_bottom.setPosition(for_middle.getPosition().x, for_middle.getPosition().y + for_middle.getSize().y);
}

void ButtonFor::EjecuteFuntion()
{
	forFunction newIteration(*puntero, *CurrentWindow, *compilador);
	newIteration(1);	//iterate all the list once
}

void ButtonFor::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const
{
	estados.transform *= getTransform();	//Obtiene las transformaciones que se hizo al objeto
	seleccionado.draw(rectangulo, estados);	// Dibuja el boton con su estado actual
	seleccionado.draw(for_middle, estados);	// Dibuja el texto del boton
	seleccionado.draw(for_bottom, estados);
	seleccionado.draw(TextRect, estados);
	seleccionado.draw(m_texto, estados);
}

/*template <typename functor, typename dato> 
void ButtonFor::setFunction(functor function, dato number)
{
	function(number);
}*/

void ButtonFor::setListObjectToIterate(std::list<recta*> &botones)
{
	puntero = &botones;
}

t ButtonFor::getContador(){
	return contador;
}
void ButtonFor::restContador()
{
	contador--;
	if (contador == 0)
	{
		triggered = false;
	}
}

Compiler& ButtonFor::getCompiler()
{
	return *compilador;
}

void ButtonFor::setCompiler(Compiler &currentCompiler)
{
	compilador = &currentCompiler;
}

void ButtonFor::setVectordeBoton(std::list<recta*> &rectangulos)
{
	rectangulosList = &rectangulos;
}

void ButtonFor::InicializarBForSecundario(For_Button2* &buttonFor)
{
	/// Initialize new Boton with all the same values

	buttonFor->InitializeForButton(rectangulo.getSize(), rectangulo.getPosition());
	buttonFor->setFuente(*m_fuente);
	buttonFor->setCadena_Texto(m_texto.getString());
	buttonFor->setButtonType(getButtonType());

	buttonFor->setPositionRect(getPosicionRect());
	buttonFor->UpdateRectSizeIfText();
	buttonFor->setColor_Fondo(sf::Color(236, 183, 37));
	buttonFor->setColor_Texto(sf::Color(255, 255, 255));

	buttonFor->setColor_FondoOvered(sf::Color(0, 180, 10, 200));
	buttonFor->setColor_TextoRSB(sf::Color(255, 255, 0, 255));

	buttonFor->setCursor(*Cursor);
	buttonFor->setCompiler(*compilador);
	buttonFor->setFuncion_Area(*area);
	buttonFor->setVectordeBoton(*rectangulosList);
}

void ButtonFor::verifyList()
{
	if (haveButtonList){
		for (std::list<recta*>::iterator es = rectangulosList->begin(); es != rectangulosList->end();)
		{
			if ((*es)->getEstado() == false) //!< if buttons is outside the rectangle area then delete it
			{
				if (rectangulosList->size() == 1)//!< if there is only 1 element 
				{
					Cursor->deleteElementatPosition((*es)->getCursorInButtonPosition());
					es = rectangulosList->erase(es);
					Cursor->UpdateObjectsInScreen(false);
					haveButtonList = false;
					break;
				}
				else 
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