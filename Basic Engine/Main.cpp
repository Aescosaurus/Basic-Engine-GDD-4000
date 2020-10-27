#include <iostream>
#include "GameWorld.h"
#include "AescEngine.h"

int main()
{
	AescEngine engine;
	
	engine.CreateObj<GameWorld>();
	
	while( engine.Running() );

	std::cin.get();

	return( 0 );
}