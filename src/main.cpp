#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include "Game.h"

int main()
{
    try{
        Game game( 1920, 1080, "Lord Runner Game" );
        game.Run();

    }catch( std::exception & err )
    {
        std::cout << "Exception: " << err.what() << std::endl;
    }

	std::cout << "Daniel Mehatzven" << std::endl;

    return( EXIT_SUCCESS );
}