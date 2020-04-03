#include "EventButtons.h"

EventButtons::~EventButtons()
{
}

void EventButtons::openTextures()
{
	if (!startTexture.loadFromFile("flag.png") || !overedStartTexture.loadFromFile("flagOvered.png") || !stopTexture.loadFromFile("stop_X.png") || !overedStopTexture.loadFromFile("stop_Y.png"))
	{
		cout << "No se encontro un archivo" << endl;
	}
	else
	{
		Current_flagTexture = &startTexture;
		Current_stopTexture = &stopTexture;
		startSprite.setTexture(*Current_flagTexture);
		stopSprite.setTexture(*Current_stopTexture);
		SetImageValues(sf::Vector2f(340, 20));
	}
}
void EventButtons::SetImageValues(const sf::Vector2f pos)
{
	startSprite.setPosition(pos);
	startSprite.setScale(0.5, 0.5);

	stopSprite.setPosition(pos.x, pos.y+startSprite.getGlobalBounds().height + 10);
	stopSprite.setScale(0.2, 0.2);
}

void EventButtons::handler(sf::Event &eventos)
{
	if (eventos.type == sf::Event::MouseButtonPressed && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = true;
		if (mouseInsideRect || mouseInsideStopSprite)
		{
			mouseClicked = true;
		}
	}

	if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
	{
		mouseClicked = false;

		if (mouseInsideRect || mouseInsideStopSprite /*&& !isExecuting*/)	/// Si el mouse seguia sobre el boton cuando fue liberado y el boton tiene una funcion
		{
			if (mouseInsideRect){
				//compilador->Execute();	///Call the pointed function
				compilador->stopExecution(false);
				mouseInsideRect = false;
			}
			else if (mouseInsideStopSprite)
			{
				//isExecuting = false;
				compilador->stopExecution(true);
				mouseInsideStopSprite = false;
			}
		}
	}
}
void EventButtons::drag()
{
	cout << "nada por ahora" << endl;
}

/*void EventButtons::Update(std::list<recta*> &botones)
{
	compilador.setListToCompile(botones);
}*/

void EventButtons::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const
{
	estados.transform *= getTransform();	
	seleccionado.draw(startSprite, estados);	
	seleccionado.draw(stopSprite, estados);
}

void EventButtons::Overed(sf::Window &ventana)
{

	if (startSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(ventana))))	/// check if button contains the current mouse position
	{

			mouseInsideRect = true;
			Current_flagTexture = &overedStartTexture;
			startSprite.setTexture(*Current_flagTexture);
	}
	else 	/// check if the mouse is not overing the button anymore
	{
		if (!mouseClicked)
			mouseInsideRect = false;
		Current_flagTexture = &startTexture;
		startSprite.setTexture(*Current_flagTexture);
	}

	stopButtonOvered(ventana);
}

void EventButtons::stopButtonOvered(sf::Window &ventana)
{
	if (stopSprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(ventana))))	/// same of overed
	{
		mouseInsideStopSprite = true;
		Current_stopTexture = &overedStopTexture;
		stopSprite.setTexture(*Current_stopTexture);
	}
	else 	/// same of overed
	{
		if (!mouseClicked)
			mouseInsideStopSprite = false;
		Current_stopTexture = &stopTexture;
		stopSprite.setTexture(*Current_stopTexture);
	}
}

Compiler& EventButtons::getCompiler()
{
	return *compilador;
}

void EventButtons::setCompiler(Compiler &currentCompiler)
{
	compilador = &currentCompiler;
}