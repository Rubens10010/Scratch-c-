#include "Compiler.h"


Compiler::Compiler()
{
	tieneLista = false;
	isExecuting = false;
	stop = false;
}


Compiler::~Compiler()
{
}

void Compiler::setListToCompile(std::list<recta*> &botones)
{
	if (&botones != nullptr)
	{
		botonesP = std::make_unique<std::list<recta*> >(botones);
		//botonesP = &botones;
		tieneLista = true;
	}
}

void Compiler::Execute()
{
	isExecuting = true;
	if (tieneLista)
	{
		for (auto &es : *botonesP)
		{
			if (!stop)
			{
				es->EjecuteFuntion();
				//isExecuting = true;
			}
			else
			{
				throw invalid_argument("false");
			}
		}
	}
}

void Compiler::stopExecution(flag stop_execution)
{
	stop = stop_execution;
}

flag Compiler::getStateOfExecution()
{
	return isExecuting;
}