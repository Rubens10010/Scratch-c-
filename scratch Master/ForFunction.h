#pragma once
#include <SFML/Graphics.hpp>
#include "recta.h"
#include <iostream>
#include <chrono>
#include "Compiler.h"

/*
*	This class is used like a functor to perform the function of iterate a given list of buttons and execute its function
	this function is used for buttons of the class control Buttons.
*/

class forFunction
{

	public:
		forFunction(std::list<recta*> &rectangulos, sf::RenderWindow &wnd, Compiler &CurrentCompiler) :pointer(&rectangulos), window(&wnd), tempCompiler(&CurrentCompiler){}

		void operator() (DatosFuncion x)
		{
			sf::Clock reloj;		//!< start a clock to meause time between function executed.
			while (window->isOpen())
			{
				tempCompiler->setListToCompile(*pointer);	//!< give the given list to the current compiler.

				if (reloj.getElapsedTime() >= sf::milliseconds(100))	//!< makes a delay of 100 miliseconds between executions.
				{
					reloj.restart();
					try
					{
						tempCompiler->Execute();
					}
					catch (invalid_argument& e)	//!< if an exception is throw (like stop execution) it breaks the loop.
					{
						throw e;
						break;
					}
					break;
				}
			}
		}
		
	private:

		std::list<recta*> *pointer;	//!< pointer to list to iterate.
		Compiler* tempCompiler;	//!< Pointer to current Compiler.
		sf::RenderWindow *window;	//!< Pointer to current render Window.
};