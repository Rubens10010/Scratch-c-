#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "WriteText.h"

class Rectangle :public sf::Drawable, public sf::Transformable
{
public:

	Rectangle(sf::Window &);
	~Rectangle();
	sf::Vector2f getPosition();
	void setValue(int x);
	void setPosition(sf::Vector2f);
	void setNormalSize();
	sf::RectangleShape& getBoton();
	void setCursor(WriteText &);
	void Update();
	void Handler(sf::Event &myEvent);
	void draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;

private:
	
	sf::RectangleShape Boton;
	sf::RectangleShape TextRect;
	int value;
	bool CursorInButton;
	bool hasValue;
	bool resized;
	WriteText *Cursor;
	sf::Vector2f PositionValue;
	float ValueTextWidth;
	sf::Vector2f normalRectSize; //constante
};

Rectangle::Rectangle(sf::Window &wnd)
{
	Boton.setPosition(wnd.getSize().x / 10, wnd.getSize().y / 10);
	Boton.setSize(sf::Vector2f(wnd.getSize().x / 8, wnd.getSize().y/15));
	Boton.setFillColor(sf::Color::Blue);
	TextRect.setSize(sf::Vector2f(Boton.getGlobalBounds().width / 3, Boton.getGlobalBounds().height - 10));
	TextRect.setPosition(Boton.getPosition().x-5 + (Boton.getGlobalBounds().width / 3) * 2, Boton.getPosition().y + 5);
	TextRect.setFillColor(sf::Color::White);
	
	normalRectSize = Boton.getSize();

	CursorInButton = false;
	hasValue = false;
	Cursor = nullptr;
	resized = false;
}

Rectangle::~Rectangle()
{
}

void Rectangle::setNormalSize()
{
	Boton.setSize(normalRectSize);
	TextRect.setSize(sf::Vector2f(Boton.getGlobalBounds().width / 3, Boton.getGlobalBounds().height - 10));
	resized = false;
}

void Rectangle::setPosition(sf::Vector2f pos)
{
	Boton.setPosition(pos);
	TextRect.setPosition(Boton.getPosition().x - 5 + (Boton.getGlobalBounds().width / 3) * 2, Boton.getPosition().y + 5);
}

void Rectangle::Handler(sf::Event &myEvent)
{
	if (myEvent.type == sf::Event::KeyPressed)
	{
		if (CursorInButton && hasValue)
		{
			Cursor->deleteElementatPosition(PositionValue);
			setNormalSize();
			hasValue = false;
		}

		if (myEvent.key.code == sf::Keyboard::Return && CursorInButton && Cursor != nullptr )
		{
			setValue(Cursor->GetCurrentValue());	// should be const
			PositionValue = Cursor->GetCursorPosition();
			ValueTextWidth = Cursor->getCurrentTextSize().width;
			hasValue = true;
			std::cout << value << std::endl;
		}
	}
	if (myEvent.type == sf::Event::TextEntered && CursorInButton)
	{
		if (Cursor->GetCursorPosition().x + Cursor->getCurrentTextSize().width > TextRect.getPosition().x + TextRect.getSize().x - 10)	//agrandar
		{
			Boton.setSize(sf::Vector2f(Boton.getSize().x + 10, Boton.getSize().y));	//update sizes
			TextRect.setSize(sf::Vector2f(TextRect.getSize().x +10 , TextRect.getSize().y));
			resized = true;
		}
		if (myEvent.text.unicode == 8 && resized)
		{
			if (Boton.getSize().x > normalRectSize.x)	//if greater than normal and delete text then resize less
			{
				Boton.setSize(sf::Vector2f(Boton.getSize().x - 10, Boton.getSize().y));	//update resize
				TextRect.setSize(sf::Vector2f(TextRect.getSize().x - 10, TextRect.getSize().y));
			}
			else //else is less or equal than normal so place normal size
			{
				setNormalSize();
			}
		}
	}
}

void Rectangle::Update(/*WriteText &CursorText*/)
{
	if (Boton.getGlobalBounds().contains(Cursor->GetCursorPosition().x,Cursor->GetCursorPosition().y+20))
	{
		CursorInButton = true;
		Cursor->setCursorPosition(sf::Vector2f(TextRect.getPosition().x + 1, TextRect.getGlobalBounds().top + TextRect.getGlobalBounds().height - Cursor->GetCursorSize()*2));
	}
	else
	{
		CursorInButton = false;
		if (!hasValue || Cursor->GetCursorPosition().x + ValueTextWidth < TextRect.getPosition().x + normalRectSize.x / 3 - 5)
		{
			setNormalSize();
		}
	}
}

void Rectangle::setCursor(WriteText &CursorText)
{
	Cursor = &CursorText;
}

void Rectangle::setValue(int x)
{
	value = x;
}

sf::RectangleShape& Rectangle::getBoton()
{
	return Boton;
}

void Rectangle::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const
{
	estados.transform *= getTransform();	//Obtiene las transformaciones que se hizo al objeto
	seleccionado.draw(Boton, estados);	// Dibuja el boton con su estado actual
	seleccionado.draw(TextRect, estados);
}

sf::Clock myClock;

int main() {
	sf::RenderWindow wnd(sf::VideoMode(800, 600), "SFML Console");

	float y = 20;
	
	std::vector<Rectangle*> rectangulos;

	WriteText ScratchTexts;
	ScratchTexts.LoadFont();
	ScratchTexts.LoadCursor();
	//ScratchTexts.SetTextCharacteristics();

	for (int i = 0; i < 5; i++)
	{
		rectangulos.push_back(new Rectangle(wnd));
		rectangulos[i]->setCursor(ScratchTexts);
		rectangulos[i]->setPosition(sf::Vector2f(20, y));
		y += 60;
	}

	sf::View fixed = wnd.getView();
	wnd.setMouseCursorVisible(false);
	
	const std::vector<sf::Text> CurrentTexts;
	while (wnd.isOpen()) {
		sf::Event myEvent;

		while (wnd.pollEvent(myEvent)) {
			if (myEvent.type == sf::Event::Closed) {
				wnd.close();
			}

			if (myEvent.type == sf::Event::KeyPressed) {
				if (myEvent.key.code == sf::Keyboard::Escape)
				{
					wnd.close();
				}
			}

			ScratchTexts.Handler_Update(myEvent, wnd);

			for (std::vector<Rectangle*>::iterator at = rectangulos.begin(); at != rectangulos.end(); at++)
			{
				(*at)->Handler(myEvent);
				(*at)->Update();
			}
		}

		ScratchTexts.UpdateAll_Text(wnd,myClock);
		wnd.clear();
		for (std::vector<Rectangle*>::iterator at = rectangulos.begin(); at != rectangulos.end(); at++)
		{
			wnd.draw(*(*at));
		}
		wnd.draw(ScratchTexts);
		wnd.display();
	}
}