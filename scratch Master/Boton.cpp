#include "Boton.h"

Boton::~Boton()
{
}

void Boton::handler(sf::Event &eventos)
{
	if (eventos.type == sf::Event::MouseButtonPressed && eventos.mouseButton.button == sf::Mouse::Left)
	{
		if (mouseInsideRect)
		{	
			mouseClicked = true;
		}
	}

	if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = false;
		
		if (mouseInsideRect)	// Si el mouse seguia sobre el boton cuando fue liberado y el boton tiene una funcion
		{
			//"aqui va la funcion para cambio del puntero opc"
			*opc_Real = opc_button;
			mouseInsideRect = false;
		}
		mouseInsideRect = false;
	}

	if (eventos.type == sf::Event::MouseMoved)
	{
		mouseX = eventos.mouseMove.x;
		mouseY = eventos.mouseMove.y;
	}

}
void Boton::setOpcBoton(opcion opcion)
{
	opc_button = opcion;
}
void Boton::setOpcion(opcion &opc)
{
	opc_Real = &opc;
}
void Boton::setPositionRect(sf::Vector2f &position)
{
	rectangulo.setPosition(position);
	update_strings();
}

void Boton::drag()
{

}

void Boton::Overed(sf::RenderWindow &ventana)	//Este manejador solo detecta cuando el puntero esta sobre un boton y da el efecto correspondiente
{
	CuerpoRect = { getPosicionRect().x, getPosicionRect().y, rectangulo.getSize().x, rectangulo.getSize().y };

	if (CuerpoRect.contains(sf::Vector2f(sf::Mouse::getPosition(ventana))))	// Verifica si el boton contiene la posicion del mouse
	{

		mouseInsideRect = true;
		m_texto.setColor(sobreB_ColorTexto);	//cambia los parametros a sus valores cuando el boton esta siendo pasado por el mouse
		rectangulo.setFillColor(sobreB_ColorFondo);
		rectangulo.setOutlineColor(sobreB_ColorBorde);
	}
	else
	{
		if (!mouseClicked)
			mouseInsideRect = false;
		if (m_texto.getColor() != b_ColorTexto)	// si el puntero ya no esta en el boton, entonces debemos cambiar los valores a los normales
		{
			m_texto.setColor(b_ColorTexto);
			rectangulo.setFillColor(b_ColorFondo);
			rectangulo.setOutlineColor(b_ColorBorde);
		}
	}
}

void Boton::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const
{
	estados.transform *= getTransform();	//Obtiene las transformaciones que se hizo al objeto
	seleccionado.draw(rectangulo, estados);	// Dibuja el boton con su estado actual
	seleccionado.draw(m_texto, estados);
}