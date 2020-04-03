#pragma once
#include "recta.h"
#include <memory>

/**
* This class compile all the functions of a list of buttons given as well as stop execution of a current compilation
*/

class Compiler
{
public:
	Compiler();
	~Compiler();

	void setListToCompile(std::list<recta*> &botones);	/// Set list of buttons to trigger its function.
	void stopExecution(flag stop_execution);	/// Stop current execution.
	void Execute();	///	Function for set to a flag button.
	
	flag getStateOfExecution(); /// Return if a compilation is being executed.

private:

	std::unique_ptr<std::list<recta*> > botonesP;	//!< Smart pointer to list to execute.
	flag tieneLista;	//!< true if a list has been setted.
	flag isExecuting;	//!< true if a execution has started.
	flag stop;	//!< True if a call to stop has been triggered.
};

