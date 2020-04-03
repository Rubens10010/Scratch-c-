#include "WriteText.h"


WriteText::WriteText()
{
	showCursor = false;
	primeroLleno = false;
	otros = false;
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

void WriteText::LoadCursor()
{
	if (!texture.loadFromFile("cursor.png"))
		std::cout << "Cursor texture not founded" << std::endl;
	sprite.setTexture(texture);
	sprite.setScale(0.05, 0.05);
}

void WriteText::SetTextCharacteristics()
{
	Cursor.setColor(fontColor);
	Cursor.setString("");
	Cursor.setFont(mainFont);
	Cursor.setCharacterSize(14);	//automatizar
	Cursor.setPosition(10, 10);

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
		//if (sf::Mouse::getPosition(wnd).x < 200 && sf::Mouse::getPosition(wnd).y < 20){ //sis se puede :)
			Cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(wnd).x , sf::Mouse::getPosition(wnd).y - 20));	// -20 por cursor
			userInput.clear();	
			Current_Text.setString(userInput);
		//}
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
		if (myEvent.text.unicode >= 48 && myEvent.text.unicode <= 57)
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

		Current_Text.setString(userInput);
	}
}

void WriteText::UpdateTexts(sf::Window &wnd)
{
	Current_Text.setPosition(Cursor.getPosition().x, Cursor.getPosition().y);
	sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(wnd))); //update Cursor
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
			Cursor.setString("_");
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
	seleccionado.draw(sprite, estados);	// Dibuja el ountero
	seleccionado.draw(Cursor, estados);	// Dibuja el cursor "_"
	seleccionado.draw(Current_Text, estados); // Dibuja el texto actual
	for (int i = 0; i < textos.size(); i++)
	{
		seleccionado.draw(textos[i], estados);
	}
}

int WriteText::GetCurrentValue()
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

int WriteText::GetCursorSize()
{
	return Cursor.getCharacterSize();
}

sf::FloatRect WriteText::getCurrentTextSize()
{
	return Current_Text.getGlobalBounds();
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