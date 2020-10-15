#include "AescEngine.h"

std::vector<std::unique_ptr<GameObject>> AescEngine::objs;

AescEngine::AescEngine()
{
	// Call Functions once.
	auto gameCallFunc = [&]() { GameUpdate(); };
	auto gfxCallFunc = [&]() { GfxDraw(); };

	// Wrap function call lamb in game loop thread func lamb.
	auto gameThreadFunc = [&]() { ThreadFunc( gameCallFunc ); };
	auto gfxThreadFunc = [&]() { ThreadFunc( gfxCallFunc ); };

	// Use lamb for thread.
	gameThread = std::thread( gameThreadFunc );
	gfxThread = std::thread( gfxThreadFunc );
}

AescEngine::~AescEngine()
{
	running = false;

	gameThread.join();
	gfxThread.join();
}

void AescEngine::Quit()
{
	running = false;
}

bool AescEngine::Running() const
{
	return( running );
}

void AescEngine::GameUpdate()
{
	static FrameTimer ft;

	const auto dt = ft.Mark();
	for( auto& obj : objs )
	{
		obj->Update( kbd,dt );
	}
}

void AescEngine::GfxDraw()
{
	gfx.ClearScreen();

	for( const auto& obj : objs )
	{
		obj->Draw( gfx );
	}

	gfx.Present();
	gfx.ClearPixels();
	gfx.FlipBuffer();
}
