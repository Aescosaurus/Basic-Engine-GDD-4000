#include "AescEngine.h"

AescEngine::AescEngine()
{
	gameThread = std::thread( this->GameUpdate );
	gfxThread = std::thread( this->GfxDraw );
}

AescEngine::~AescEngine()
{
	running = false;

	gameThread.join();
	gfxThread.join();
}

void AescEngine::GameUpdate()
{
	for( auto& obj : objs )
	{
		obj->Update();
	}
}

void AescEngine::GfxDraw()
{
	for( const auto& obj : objs )
	{
		obj->Draw();
	}
}
