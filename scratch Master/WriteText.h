#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "Typedefs.h"

/*
*	This class creates a Cursor and also a pointer draws the cursor on a given position, when is inside a 
	textRectangle, handle the text entered event but only receive numbers.
	also is in charge of delete all text on the render window.
*/

class WriteText:public sf::Drawable, public sf::Transformable
{
public:
	WriteText(NumBotons);	/// Construct a new instance of cursor object with the current number of object on screen
	~WriteText();

	void setPositionOfTextatPosition(sf::Vector2f&, const sf::Vector2f&);	/// Change the position of a text (string) in a given position
	void setCursorPosition(sf::Vector2f);	/// Set position of cursor
	void SetTextCharacteristics();	/// Initialize cursor and gives the characteristics for write text.
	void SetFont(sf::Font);	/// Set Font of the text.
	void setState(flag state);	/// set state (true if cursor is inside a button).


	DatosFuncion GetCurrentValue();	/// Get Current value in the position of the cursor.
	sf::FloatRect getCurrentTextSize();	/// Get Global bound of the current text.
	sf::Vector2f getPunteroPosition();	/// Get global position of the pointer.
	sf::Vector2f GetCursorPosition();	/// Get global position of the cursor.
	t GetCursorSize();	/// Get size of the cursor.
	flag getState();	/// Get state of the cursor.

	void UpdateAll_Text(sf::Window &wnd, sf::Clock &clock);	/// Update the whole Write Text class.
	void UpdateObjectsInScreen(option);	/// Update the number of object in window +1 . 
	void UpdateClockTime(sf::Clock &clock);	/// Update current clock time.
	void UpdateTexts(sf::Window &wnd);	/// Update Texts on window.
	void UpdateCursor();	/// Update Cursor to display or not depending on the clock time.
	void Handler_Update(sf::Event &, sf::Window &);	/// Function combinated of handler and update all.

	void CheckIfKeyReturnisPressed(sf::Event &);	/// check if the 'return' key has been pressed so push the current text.
	void CheckIfTextisEntered(sf::Event &);	/// Check if text has been entered while the cursor is active.

	void LoadFont();	/// load Font of the text to write on render window.
	void deleteElementatPosition(sf::Vector2f);	/// Delete an element (text) of the given position.

private:
	void draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;	/// draw all the drawable objects from this class.

	std::vector<sf::Text> textos;	//!< Vector which stores all the text to display on window.
	std::vector<flag> inside_Buttons;	//!< Vector which stores at each window iteration if the cursor is inside some button.
	sf::Clock *myClock;	//!< Pointer to window's clock.
	sf::Color fontColor;	//!< color of the Text displayed.
	sf::Font mainFont;	//!< font of the Texts.
	sf::Text Current_Text, Cursor; //!< Texts storing the cursor character and the current text written.
	sf::String userInput;	//!< Store text written when text entered event is triggered and then set it to the current Text.
	sf::Vector2f PointerPosition;	//!< Position of the pointer inside the window

	DatosFuncion CurrentNumber;	//!< Current value of text wrote.
	NumBotons NumberObjectsInScreen;	//!< Current Number of object with text rectangle in the screen.

	flag showCursor;	//!< true when time is greater than delay time to give cursor effect.
	flag primeroLleno;	//!< true when first text has been pushed to the list.
	flag otros;	//!< true if there are more than 1 text on window.
	flag isInButton;	//!< true if cursor is In button.
};


