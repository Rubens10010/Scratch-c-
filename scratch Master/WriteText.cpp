#include "WriteText.h"


WriteText::WriteText(NumBotons Num)
{
	NumberObjectsInScreen = Num;
	showCursor = false;
	primeroLleno = false;
	otros = false;
	isInButton = false;
	CurrentNumber = -1;
	SetTextCharacteristics();
}

WriteText::~WriteText()
{
}

void WriteText::LoadFont()
{
	mainFont.loadFromFile("comicbd.ttf");
	fontColor.r = 0;
	fontColor.g = 203;
	fontColor.b = 0;
}

void WriteText::SetTextCharacteristics()
{
	Cursor.setColor(fontColor);
	Cursor.setString("");
	Cursor.setFont(mainFont);
	Cursor.setCharacterSize(14);	//automatizar
	Cursor.setPosition(60, 20);

	Current_Text.setColor(fontColor);
	Current_Text.setFont(mainFont);
	Current_Text.setCharacterSize(14);
	Current_Text.setStyle(sf::Text::Regular);
	Current_Text.setPosition(Cursor.getPosition().x + 5, Cursor.getPosition().y);
}

void WriteText::Handler_Update(sf::Event &myEvent,sf::Window &wnd)
{
	if (myEvent.type == sf::Event::MouseButtonReleased)
	{
		if (isInButton){ //sis se puede :)
			Cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(wnd).x , sf::Mouse::getPosition(wnd).y - 20));	// -20 por cursor
			userInput.clear();	
			Current_Text.setString(userInput);
		}
	}

	CheckIfKeyReturnisPressed(myEvent);
	CheckIfTextisEntered(myEvent);
}

void WriteText::CheckIfKeyReturnisPressed(sf::Event &myEvent)
{
	if (myEvent.type == sf::Event::KeyPressed)
	{
		if (myEvent.key.code == sf::Keyboard::Return && Current_Text.getString() != "")
		{
			if (textos.size() >= 1 && Current_Text.getPosition() == textos.back().getPosition())
			{
				std::cout << "double enter pressed" << std::endl;
			}

			else
			{
				try{
					std::string cString = Current_Text.getString();
					CurrentNumber = std::stoi(cString);	//get the current value
					sf::Text *nuevoTexto = new sf::Text;	//new Text containing the current value
					nuevoTexto->setColor(fontColor);
					nuevoTexto->setFont(mainFont);
					nuevoTexto->setCharacterSize(14);
					nuevoTexto->setStyle(sf::Text::Regular);
					nuevoTexto->setString(Current_Text.getString());
					nuevoTexto->setPosition(Current_Text.getPosition());
					textos.push_back(*nuevoTexto);

					primeroLleno = true;
					delete nuevoTexto;
				}
				catch (std::out_of_range& e)
				{
					std::cout << "Out Of range" << std::endl;
					userInput.clear();
				}

				std::cout << textos.size() << std::endl;
			}
		}
		
		if (primeroLleno && otros == false)
		{
			userInput.clear(); //limpia la current string para poner otro
			otros = true;
		}
	}
}

void WriteText::CheckIfTextisEntered(sf::Event &myEvent)
{
	if (myEvent.type == sf::Event::TextEntered)
	{

		if (myEvent.text.unicode >= 48 && myEvent.text.unicode <= 57|| myEvent.text.unicode ==45)
		{
			if (textos.size() <= 1 && primeroLleno == false){
				userInput.insert(userInput.getSize(), myEvent.text.unicode);
				primeroLleno = false;
			}
			else if (otros == true)
			{
				userInput.insert(userInput.getSize(), myEvent.text.unicode);
			}
		}

		else if (myEvent.text.unicode == 8 && userInput.getSize() > 0)
		{
			userInput.erase(userInput.getSize() - 1, userInput.getSize());
		}

		if (textos.size() >= 1 && Current_Text.getPosition() == textos.back().getPosition())
		{
			userInput.clear();
		}
		else
		{
			Current_Text.setString(userInput);
		}
	}
}

void WriteText::UpdateTexts(sf::Window &wnd)
{
	Current_Text.setPosition(Cursor.getPosition().x, Cursor.getPosition().y);
	PointerPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(wnd));
}

void WriteText::UpdateClockTime(sf::Clock &clock)
{
	myClock = &clock;
	UpdateCursor();
}

void WriteText::UpdateCursor()
{
	if (myClock->getElapsedTime() >= sf::milliseconds(500)) {
		myClock->restart();
		showCursor = !showCursor;

		if (showCursor == true) {
			Cursor.setString("|");
		}
		else {
			Cursor.setString(" ");
		}
	}
}

void WriteText::UpdateAll_Text(sf::Window &wnd, sf::Clock &clock)
{
	UpdateTexts(wnd);
	UpdateClockTime(clock);
	UpdateCursor();
}

void WriteText::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const
{
	estados.transform *= getTransform();	//Obtiene las transformaciones que se hizo al objeto
	if (isInButton){
		seleccionado.draw(Cursor, estados);	// Dibuja el cursor "_"
	}
	seleccionado.draw(Current_Text, estados); // Dibuja el texto actual
	for (int i = 0; i < textos.size(); i++)
	{
		seleccionado.draw(textos[i], estados);
	}
}

DatosFuncion WriteText::GetCurrentValue()
{
	return CurrentNumber;
}

sf::Vector2f WriteText::GetCursorPosition()
{
	return Cursor.getPosition();
}

void WriteText::setCursorPosition(sf::Vector2f newPosition)
{
	Cursor.setPosition(newPosition);
}

t WriteText::GetCursorSize()
{
	return Cursor.getCharacterSize();
}

sf::FloatRect WriteText::getCurrentTextSize()
{
	return Current_Text.getGlobalBounds();
}

sf::Vector2f WriteText::getPunteroPosition()
{
	return PointerPosition;
}

void WriteText::deleteElementatPosition(sf::Vector2f numPos)
{
	if (textos.size() >= 1)
	{
		for (std::vector<sf::Text>::iterator es = textos.begin(); es != textos.end(); es++)
		{
			if (es->getPosition() == numPos)
			{
				textos.erase(es);
				userInput.clear();
				break;
			}
		}
	}
}

void WriteText::setPositionOfTextatPosition(sf::Vector2f &pos, const sf::Vector2f &newPos)
{
	if (textos.size() >= 1)
	{
		for (std::vector<sf::Text>::iterator es = textos.begin(); es != textos.end(); es++)
		{
			if (es->getPosition() == pos)
			{
				es->setPosition(newPos);
				break;
			}
		}
	}
}

void WriteText::setState(flag state)
{
	if (inside_Buttons.size() >= NumberObjectsInScreen)
	{
		isInButton = false;
		for (std::vector<bool>::iterator et = inside_Buttons.begin(); et != inside_Buttons.end(); et++)
		{
			if (*et == true)
			{
				isInButton = true;
			}
		}
		inside_Buttons.clear();
	}

	inside_Buttons.push_back(state);
}

void WriteText::UpdateObjectsInScreen(option isNew)
{
	if (isNew)
		NumberObjectsInScreen++;
	else
		NumberObjectsInScreen--;
}

flag WriteText::getState()
{
	return isInButton;
}

