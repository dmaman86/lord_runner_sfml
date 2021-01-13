#include "Application.h"

#include <stdexcept>
#include <iostream>
#include <cstdlib>


int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return(EXIT_SUCCESS);
}
