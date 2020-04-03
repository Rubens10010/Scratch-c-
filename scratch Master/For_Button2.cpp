#include "For_Button2.h"
For_Button2::~For_Button2()
{

}


void For_Button2::InitializeForButton(const sf::Vector2f &size, sf::Vector2f position)
{

	setTamaño(size);
	setPositionRect(position);

	for_middle.setSize(sf::Vector2f(22, size.y - 20));
	for_middle.setPosition(rectangulo.getPosition().x, rectangulo.getPosition().y + rectangulo.getSize().y);


	for_bottom.setSize(rectangulo.getSize());
	for_bottom.setPosition(for_middle.getPosition().x, for_middle.getPosition().y + for_middle.getSize().y);

	setTextureForButton(true);

	height = rectangulo.getGlobalBounds().height;
	isAlive = true;
}

void For_Button2::setColor_Fondo(const NormalBotonColor &NB_color)
{
	b_ColorFondo = NB_color;	// Guarda el color en el una variable
	rectangulo.setFillColor(NB_color);	// Establece el color del fondo
	for_middle.setFillColor(NB_color);
	for_bottom.setFillColor(NB_color);
}

void For_Button2::setTextureForButton(option texture)
{
	if (texture)
	{
		topTexture.loadFromFile("for_Top.png");
		rectangulo.setTexture(&topTexture);

		middleTexture.loadFromFile("for_Middle.png");
		for_middle.setTexture(&middleTexture);

		bottomTexture.loadFromFile("for_Bottom.png");
		for_bottom.setTexture(&bottomTexture);
	}
}

void For_Button2::Overed(sf::RenderWindow &ventana)	//Este manejador solo detecta cuando el puntero esta sobre un boton y da el efecto correspondiente
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
		for_bottom.getGlobalBounds().contains(Cursor->GetCursorPosition().x, Cursor->GetCursorPosition().y + 20)) /// check if for contains cursor
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

void For_Button2::handler(sf::Event &eventos)
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
			//VerifyIfButtonisInside(*rectangulosList);
			mouseClicked = false;

			if (mouseInsideRect)	// Si el mouse seguia sobre el boton cuando fue liberado y el boton tiene una funcion
			{
				if (contador == 0)
				{
					contador = value;
				}
				triggered = true;
			}

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
				cout << "has deleted\n" << endl;
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
	}
}

void For_Button2::TriggerFunction()
{
	if (isAlive)
	{
		if (triggered && contador != 0)	// If function was triggered and counter is not 0 then itera the current list once more.
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
}


void For_Button2::drag()
{
	if (isAlive){
		if (dragging == true)
		{
			setPositionRect(sf::Vector2f(mouseX - mouseRectOffset.x, mouseY - mouseRectOffset.y));
			Update_ForButtonPosition();
			Cursor->setPositionOfTextatPosition(PositionCursorInButton, Cursor->GetCursorPosition());
			PositionCursorInButton = Cursor->GetCursorPosition();
		}
	}

	TriggerFunction();
}

void For_Button2::Update_ForButtonPosition()
{
	for_middle.setPosition(rectangulo.getPosition().x, rectangulo.getPosition().y + rectangulo.getSize().y);
	for_bottom.setPosition(for_middle.getPosition().x, for_middle.getPosition().y + for_middle.getSize().y);
}

void For_Button2::Update_ForBotPosition(sf::RectangleShape &CurrentMiddle, sf::RectangleShape &bot)
{
	bot.setPosition(CurrentMiddle.getPosition().x, CurrentMiddle.getPosition().y + CurrentMiddle.getSize().y);
}

void For_Button2::setPositionRect(sf::Vector2f &position)
{
	rectangulo.setPosition(position);
	TextRect.setPosition(rectangulo.getPosition().x - 5 + (rectangulo.getGlobalBounds().width / 3) * 2, rectangulo.getPosition().y + 5);
	Update_ForButtonPosition();
	update_strings();
}

void For_Button2::EjecuteFuntion()
{
	if (isAlive)	/// if is alive Execute Iteration of list.
	{
		if (hasListToIterate)
		{
			forFunction newIteration(ListToIterate, *CurrentWindow, *compilador);
			newIteration(1);	
		}
	}
}

/*template <typename functor, typename dato>
	void ButtonFor::setFunction(functor function, dato number)
	{
	function(number);
}*/

void For_Button2::setListObjectToIterate(std::list<recta*> &botones)
{
	ListToIterate = botones;
	hasListToIterate = true;
}

t For_Button2::getContador(){
	return contador;
}

void For_Button2::restContador()
{
	contador--;
	if (contador == 0)
	{
		triggered = false;
	}
}

void For_Button2::setCompiler(Compiler &currentCompiler)
{
	compilador = &currentCompiler;
}

void For_Button2::set_Live(flag goLive)
{
	isAlive = goLive;
}

void For_Button2::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const
{
	estados.transform *= getTransform();	/// Get all the transformations of the drawable objects.
	seleccionado.draw(rectangulo, estados);	
	seleccionado.draw(for_middle, estados);	
	seleccionado.draw(for_bottom, estados);
	seleccionado.draw(TextRect, estados);
	seleccionado.draw(m_texto, estados);
}

void For_Button2::pushBotonToList(recta *boton)
{
	if (boton != this)
	{
		ListToIterate.push_back(boton);
		hasListToIterate = true;
		if (ListToIterate.size() > 1)
		{
			for_middle.setSize(sf::Vector2f(for_middle.getSize().x, for_middle.getSize().y + height));
			Update_ForBotPosition(for_middle, for_bottom);
		}
	}
}