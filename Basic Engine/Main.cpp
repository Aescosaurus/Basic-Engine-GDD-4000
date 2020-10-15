#include <iostream>
#include "AescEngine.h"
#include "GameWorld.h"

int main()
{
	AescEngine engine;

	engine.CreateObj<GameWorld>();

	while( engine.Running() );

	std::cin.get();

	return( 0 );
}