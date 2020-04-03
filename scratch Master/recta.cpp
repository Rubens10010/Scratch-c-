#include "recta.h"


recta::recta(sf::Vector2f size, sf::RenderWindow &wnd) : CurrentWindow(&wnd)
{
	setTamaño(sf::Vector2f(wnd.getSize().x / 10, wnd.getSize().y / 15));

	m_texto.setCharacterSize(15);

	CursorInButton = false;
	hasValue = false;
	Cursor = nullptr;
	resized = false;

	mouseClicked = false;
	mouseInsideRect = false;
	dragging = false;
	haveFuntion = false;
	haveObjectPointingTo = false;
	isAlive = false;
}


recta::~recta()
{
	/*delete area;
	delete imagen_ptr;
	delete m_fuente;*/
}

void recta::setTamaño(const sf::Vector2f tam)
{
	b_tamaño = tam;	//el tamaño del boton esta guardado en una variable del mismo tippo
	rectangulo.setSize(b_tamaño);	// Establece el tamñano del boton con estos parametros

	TextRect.setSize(sf::Vector2f(rectangulo.getGlobalBounds().width / 3, rectangulo.getGlobalBounds().height - 20));
	TextRect.setFillColor(sf::Color::White);

	normalRectSize = rectangulo.getSize();
	normalTextRectSize = TextRect.getSize();

	update_strings();	// Actualiza los nuevos datos en la pantalla
}

void recta::UpdateRectSizeIfText()
{
	if (b_tamaño.x > 0 && b_tamaño.y > 0 && m_texto.getString() != "")
	{
		while (m_texto.getGlobalBounds().left + m_texto.getGlobalBounds().width >= TextRect.getPosition().x)
		{
			TextRect.setPosition(TextRect.getPosition().x + 12, TextRect.getPosition().y);
			if (TextRect.getPosition().x + TextRect.getGlobalBounds().width >= rectangulo.getPosition().x)
			{
				rectangulo.setSize(sf::Vector2f(rectangulo.getSize().x + 12, rectangulo.getSize().y));
			}

			normalRectSize = rectangulo.getSize();
			normalTextRectSize = TextRect.getSize();
		}
	}
}

void recta::setNormalSize()
{
	rectangulo.setSize(normalRectSize);
	TextRect.setSize(sf::Vector2f(/*rectangulo.getGlobalBounds().width / 3, rectangulo.getGlobalBounds().height - 15*/ normalTextRectSize));
	resized = false;
}

void recta::setTextureRectangle(const sf::Texture* image)
{
	rectangulo.setTexture(image);
}

void recta::setCadena_Texto(const ButtonText cadena)
{
	m_texto.setString(cadena);	// Establece la cadena de texto a usar
	update_strings();	// Actualiza los datos
}

void recta::setFuente(sf::Font &fuent)
{
	m_fuente = &fuent;	// la fuente es guardada localmente
	m_texto.setFont(*m_fuente); // Establece la fuente del texto
	update_strings();	// Actualiza los datos
}

void recta::setColor_Fondo(const NormalBotonColor &NB_color)
{
	b_ColorFondo = NB_color;	// Guarda el color en el una variable
	rectangulo.setFillColor(NB_color);	// Establece el color del fondo
}

void recta::setColor_Texto(const NormalBotonColor &NB_color)
{
	b_ColorTexto = NB_color;	// Guarda el color del texto
	m_texto.setColor(NB_color);		//	Establece el color del Texto
}

void recta::setColor_Borde(const NormalBotonColor &NB_color)
{
	b_ColorBorde = NB_color;	// Guarda el color del borde
	rectangulo.setOutlineColor(NB_color);
}

void recta::setAncho_Borde(Linewidth espesor)
{
	rectangulo.setOutlineThickness(espesor);	// Establece el ancho de borde
}

void recta::setColor_FondoOvered(const SobreBotonColor &RSB_color)
{
	sobreB_ColorFondo = RSB_color;
}

void recta::setColor_TextoRSB(const SobreBotonColor &RSB_color)
{
	sobreB_ColorTexto = RSB_color;
}

void recta::setColor_BordeRSB(const SobreBotonColor &RSB_color)
{
	sobreB_ColorBorde = RSB_color;
}

void recta::setPositionRect(sf::Vector2f &position)
{
	rectangulo.setPosition(position);
	TextRect.setPosition(rectangulo.getPosition().x - 5 + (rectangulo.getGlobalBounds().width / 3) * 2, rectangulo.getPosition().y + 5);
	update_strings();
}

sf::Vector2f recta::getPosicionRect()
{
	return rectangulo.getPosition();
}

sf::RectangleShape* recta::getRectangulo()
{
	return &rectangulo;
}

void recta::set_Live(flag goLive)
{
	isAlive = goLive;
}

void recta::Overed(sf::RenderWindow &ventana)	//Este manejador solo detecta cuando el puntero esta sobre un boton y da el efecto correspondiente
{
	CuerpoRect = { getPosicionRect().x, getPosicionRect().y, rectangulo.getSize().x, rectangulo.getSize().y };

	if (CuerpoRect.contains(sf::Vector2f(sf::Mouse::getPosition(ventana))))	// Verifica si el boton contiene la posicion del mouse
	{
		Cursor->setState(true); //*

		mouseInsideRect = true;

		m_texto.setColor(sobreB_ColorTexto);	//cambia los parametros a sus valores cuando el boton esta siendo pasado por el mouse
		rectangulo.setFillColor(sobreB_ColorFondo);
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
		}
	}

	if (rectangulo.getGlobalBounds().contains(Cursor->GetCursorPosition().x, Cursor->GetCursorPosition().y + 20))
	{
		CursorInButton = true;
		Cursor->setCursorPosition(sf::Vector2f(TextRect.getPosition().x + 1, TextRect.getGlobalBounds().top + TextRect.getGlobalBounds().height - Cursor->GetCursorSize() - 5));
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

void recta::update_strings()	// actualiza el tamaño y letras del boton
{
	if (b_tamaño.x > 0 && b_tamaño.y > 0 && m_texto.getString() != "")	//Si el ancho y alto del boton es mayor que 0 y no tiene ningun texto dentro
	{
		if (m_texto.getGlobalBounds().width < b_tamaño.x / 4 * 3 && m_texto.getGlobalBounds().height < b_tamaño.y - 25.f) //Si el ancho del texto es menor que 3/4 del ancho del boton y el alto del texto es < q el alto del boton -20
		{
			while (m_texto.getGlobalBounds().width < b_tamaño.x / 4 * 3 && m_texto.getGlobalBounds().height < b_tamaño.y - 25.f)	//mientras que el ancho del texto no sea al menos 3/4 del boton y el alto al menos -10 del alto del boton 
			{
				m_texto.setCharacterSize(m_texto.getCharacterSize() + 1);// Aumenta el tamaño de los caracteres en 1
			}
			if (m_texto.getGlobalBounds().width < b_tamaño.x / 4 * 3 || m_texto.getGlobalBounds().height < b_tamaño.y - 25.f)	// Si uno de los dos se pasa disminuye el tamaño en 1
			{
				m_texto.setCharacterSize(m_texto.getCharacterSize() - 1);
			}
		}
		else
		{
			while (m_texto.getGlobalBounds().width >b_tamaño.x / 4 * 3 || m_texto.getGlobalBounds().height > b_tamaño.y -25.f)	// Lo contrario al otro si es muy grande disminuye hasta que sea < 3/4
			{
				m_texto.setCharacterSize(m_texto.getCharacterSize() - 1);
			}
			if (m_texto.getGlobalBounds().width > b_tamaño.x / 4 * 3 || m_texto.getGlobalBounds().height > b_tamaño.y - 25.f) // si disminuye mucho aumenta en 1
			{
				m_texto.setCharacterSize(m_texto.getCharacterSize() + 1);
			}
		}

		//m_texto.setOrigin(rectangulo.getLocalBounds().left+(rectangulo.getLocalBounds().width / 2), rectangulo.getLocalBounds().top + m_texto.getLocalBounds().height / 4); //Establece el origen del texto en el centro del rectangulo del texto
		m_texto.setPosition(rectangulo.getPosition().x +5 , rectangulo.getPosition().y+6); //establece la posicion del boton en el centro del 

	}
}

void recta::setFuncion_Area(sf::RectangleShape &rect)
{
	area = &rect;
}

void recta::setFuncion_Figura(funcion2 funcion, DatosFuncion dato1, DatosFuncion dato2)
{
	funcionpointerclass = funcion;            
	value = dato1;
	datoy = dato2;
	haveFuntion = true;
}

void recta::setFuncion_value(DatosFuncion dato)
{
	value = dato;
}

void recta::setClassObjectPointedTo(figura* pointer)
{
	imagen_ptr = pointer;
	haveObjectPointingTo = true;
}

void recta::setCursor(WriteText &CursorText)
{
	Cursor = &CursorText;
}

sf::Vector2f recta::getCursorInButtonPosition()
{
	return PositionCursorInButton;
}

void recta::EjecuteFuntion()
{
	if (haveFuntion && funcionpointerclass != nullptr)
	{
		if (haveObjectPointingTo)
		{
			(imagen_ptr->*funcionpointerclass)(value, datoy);
		}
		else
		{
			cout << "Doesn't have a object" << endl;
		}
	}
	else
	{
		cout << "Function to execute is not found" << endl;
	}
}

void recta::setLinked(flag newLink)
{
}

flag recta::isLinked()
{	
	return false;
}

void recta::setNextBoton(recta &NextButton)
{
}

recta* recta::getNextBoton()
{
	return this;
}

void recta::VerifyPositionBoton(recta* &boton)
{
}

flag recta::getEstado()
{
	return false;
}

void recta::Update_ForButtonPosition()
{
}

void recta::setButtonType(std::string name)
{
	type = name;
}

TypeOfButton& recta::getButtonType()
{
	return type;
}

void recta::pushBotonToList(recta *boton)
{
}

void recta::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const
{
	estados.transform *= getTransform();	//Obtiene las transformaciones que se hizo al objeto
	seleccionado.draw(rectangulo, estados);	// Dibuja el boton con su estado actual
	seleccionado.draw(m_texto, estados);	// Dibuja el texto del boton
	seleccionado.draw(TextRect, estados);
}