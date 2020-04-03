#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "Typedefs.h"
#include "Figura.h"
#include "WriteText.h"

class recta : public sf::Drawable, public sf::Transformable
{
public:
	recta();
	recta(const sf::Vector2f, sf::RenderWindow &wnd);
	virtual ~recta();

	void setTamaño(const sf::Vector2f tam);	/// Set the size of the button.
	void setFuente(sf::Font& fuent);	/// Set the font of the button.
	void setCadena_Texto(const ButtonText cadena);	/// Set the String (text) of the button.
	void setColor_Texto(const NormalBotonColor &NB_color);	/// Set the text color.
	void setAncho_Borde(Linewidth espesor);	// Set the outline width.
	void setColor_Borde(const NormalBotonColor &NB_color);	// Set the outline color.
	void setColor_TextoRSB(const SobreBotonColor &RSB_color); /// Set color of text when overed.
	void setColor_BordeRSB(const SobreBotonColor &RSB_color);	/// set Color of outline when overed.
	void setNormalSize();	/// Set initial normal size.
	void setCursor(WriteText &);	/// Set cursor of the program .
	void setFuncion_Area(sf::RectangleShape &rect);	/// Set square area of work.
	void setFuncion_Figura(funcion2, DatosFuncion dato1, DatosFuncion dato2);	/// Set funcion which is pointed by this button.
	void setFuncion_value(DatosFuncion dato);	/// Set main data to call the function.
	void setClassObjectPointedTo(figura* pointer);	/// Set current image to use functions. 
	virtual void setButtonType(TypeOfButton name);	/// Set type of the button in text.
	virtual void setPositionRect(sf::Vector2f &position);	/// Set position of the whole rectangle. 
	virtual void set_Live(flag goLive);	/// Set if the button is ready to work
	virtual void setNextBoton(recta &NextButton);	/// set button which is linked with this button.
	virtual void setTextureRectangle(TexturePointer image);	/// Set texture for the rectangle.
	virtual void setLinked(flag);	/// Function: true if is linked to another boton.
	virtual void setColor_Fondo(const NormalBotonColor &NB_color);	/// Set Color of rectangle to display when is not overed.
	virtual void setColor_FondoOvered(const SobreBotonColor &RSB_color);	/// Set color to display when pointer is over button.

	sf::Vector2f getPosicionRect();	/// Get current position of the rectangle.
	sf::Vector2f getCursorInButtonPosition();	/// Get position of Cursor in button.
	virtual TypeOfButton& getButtonType();	/// Get type of the button (string).
	virtual recta* getNextBoton();	/// Get next rectangle linked to it.
	virtual flag getEstado();	/// Function: if return false the caller will delete the button.
	virtual flag isLinked();	/// Function: if is linked to a rectangle then return true.
	sf::RectangleShape* getRectangulo();	/// Return a pointer to this rectangle.

	virtual void UpdateRectSizeIfText();	/// Update current size if text position plus text size is greater than text rectangle position. 
	virtual void VerifyPositionBoton(recta* &boton);	/// Verify if a button intersec with other of current list.
	virtual void Update_ForButtonPosition();	/// Update position of button of type for.
	virtual void update_strings();	/// Update the size and position of the string within the button.
	virtual void pushBotonToList(recta *boton);	/// Push new Boton to current list of button for.
	virtual void EjecuteFuntion();	/// Execute Function of the button.
	virtual void Overed(sf::RenderWindow &ventana);	/// Verify if the pointer is over the button.
	virtual void handler(sf::Event &eventos) = 0;	/// Virtual pure function: Verify event in the current window which affects the button.
	virtual void drag() = 0;	/// Virtual pure function: actions when button is being dragged.


protected:

	virtual void recta::draw(sf::RenderTarget& seleccionado, sf::RenderStates estados) const;	/// Virtual Function: draw all the drawable objects on the current render window.
	
	sf::RectangleShape rectangulo;	//!< Rectangle which represents the button area.
	sf::RectangleShape TextRect;	//!< Rectangle which represents the area where the cursor can write text.
	sf::RectangleShape *area;	//!< Work area of the button.

	
	figura* imagen_ptr;	 //!< Pointer to class figure which is the object to handler.
	sf::Font* m_fuente;	 //!< Pointer to the current font of all texts. 
	sf::Text m_texto;	//!< Text which contains the string of the function which the button realize.

	NormalBotonColor b_ColorFondo;	//!< Color of the buttons's background.
	NormalBotonColor b_ColorTexto;	//!< Color of button's text.
	NormalBotonColor b_ColorBorde;	//!< Color of button's outline.

	SobreBotonColor sobreB_ColorFondo;	//!< Color of the buttons's background, text and outline when is overed.
	SobreBotonColor sobreB_ColorTexto;
	SobreBotonColor sobreB_ColorBorde;

	flag mouseClicked;	//!< true if click over button.
	flag mouseInsideRect;	//!< true if mouse over button.
	flag dragging;	//!< true if new button is being dragged.
	flag isAlive;	//!< true if button is working.
	flag haveFuntion;	//!< true if have function to trigger.
	flag haveObjectPointingTo;	//!< true if an image has been setted.
	flag CursorInButton;	//!< true if the cursor is inside the button.
	flag hasValue;	//!< true if a value has been entered within the button.
	flag resized;	//!< true if the button is at normal size.

	sf::Vector2f mouseRectOffset;	//!< Number: represents the value of the position of the origin relative to the mouse.
	sf::Vector2f b_tamaño;	//!< Current size of the button.
	sf::Vector2f normalRectSize; // Normal size of the button.
	sf::Vector2f normalTextRectSize; //!< Normal size of text rectangle.
	sf::Vector2f PositionCursorInButton;	//!< Position of the cursor within the button.
	sf::FloatRect CuerpoRect;	//!< rectangle bound of the button.

	DatosMouse mouseX;	//!< Mouse Position.
	DatosMouse mouseY;

	DatosFuncion datox;	//!< data for the function trigger.
	DatosFuncion datoy;
	DatosFuncion value;	//!< value inside the button.

	funcion2 funcionpointerclass;	//!< pointer to function of image.
	sf::RenderWindow *CurrentWindow; //!< pointer to current render window.

	WriteText *Cursor;	//!< Pointer to cursor of the window.
	widthText ValueTextWidth;	//!< width of the current value string.
	TypeOfButton type;	//!< string which contains the name(type) of button.
};


