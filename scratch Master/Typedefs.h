#pragma once
#include <list>
#include <SFML/Graphics.hpp>

/*! \Header description.
*         This Header contains all the typedef in the Program
*		  Each one is used for many classes 
*/

/**
* Classes that are used for Typedef
*/
class recta;
class Boton1;
class figura;

typedef int opcion;	/// Current view Number.
typedef int t;	/// int data type t
typedef int DatosMouse;	  /// int data of the mouse.
typedef int NumBotons;	/// Int number of buttons.
typedef int DatosFuncion;	/// Int data of Function Pointed by a button.
typedef float angle;	/// Angle of an image.
typedef float Linewidth;
typedef float PosBotons;	/// Float for Position of Buttons.
typedef float widthText;	/// width of a string
typedef bool flag;	/// Bool to activate or desactivate functions if the sate is true or false.
typedef bool option;	/// Bool to choose beetween two options.

typedef opcion *ptropcion;	/// Pointer To Number of View.
typedef std::list<recta*> *pointerToList;	/// Pointer to list of pointers to rectangle.
typedef const sf::Texture* TexturePointer;	/// Pointer to Texture.
typedef std::vector<Boton1*> *botones_imagen;	/// Pointer to Buttons of type 1.
typedef std::vector<void(figura::*)(int, int)> VectordeFunciones;	///	Pointer to List of Function of class Figure .
typedef void(figura::*funcion2)(int, int);	/// Pointer to function of class Figure.
typedef sf::Color NormalBotonColor;	/// Colors for Buttons when is not overed.
typedef sf::Color SobreBotonColor;	/// Colors for Buttons when is overed.
typedef std::string TypeOfButton;	/// String of text.
typedef std::string ButtonText;	/// String for Buttons.