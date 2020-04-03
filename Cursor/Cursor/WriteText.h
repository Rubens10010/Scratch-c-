#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <SFML/Graphics.hpp>

class WriteText:public sf::Drawable, public sf::Transformable
{
public:
	WriteText();
	~WriteText();

	void LoadFont();
	void SetFont(sf::Font);
	void LoadCursor();
	void SetTextCharacteristics();
	void Handler_Update(sf::Event &, sf::Window &);
	void CheckIfKeyReturnisPressed(sf::Event &);
	void CheckIfTextisEntered(sf::Event &);
	void UpdateTexts(sf::Window &wnd);
	void UpdateCursor();
	void UpdateClockTime(sf::Clock &clock);
	void UpdateAll_Text(sf::Window &wnd, sf::Clock &clock);
	void draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;
	int GetCurrentValue();
	sf::Vector2f GetCursorPosition();
	int GetCursorSize();
	void setCursorPosition(sf::Vector2f);
	void deleteElementatPosition(sf::Vector2f);
	sf::FloatRect getCurrentTextSize();

private:
	sf::Color fontColor;
	sf::Font mainFont;
	sf::Clock *myClock;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Text Current_Text, Cursor;
	sf::String userInput;
	std::vector<sf::Text> textos;
	int CurrentNumber;
	bool showCursor;
	bool primeroLleno;
	bool otros;
};

