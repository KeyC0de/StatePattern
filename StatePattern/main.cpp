#include <iostream>
#include <string>
#include "state.h"
#if defined _DEBUG && !defined NDEBUG
#	include <vld.h>
#endif


int help()
{
	std::cout << "usage: state {width} {height} [title]"
		<< '\n';
	return EXIT_FAILURE;
}


int main( int argc,
	char* argv[] )
{
	if ( argc < 3 )
	{
		return help();
	}

	unsigned width = atoi( argv[1] );
	unsigned height = atoi( argv[2] );

	std::string title;
	if ( argc < 4 )
	{
		title = "Time to play the Game";
	}
	else
	{
		title = argv[3];
	}

	Game theGame{width, height, title};
	bool ret = theGame.start();
	if ( ret )
	{
		return EXIT_FAILURE;
	}

	std::system( "pause" );
	return 0;
}
