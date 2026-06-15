#include "Chunk.h"

App::Chunk::Chunk()
	: block()
{
}

App::Chunk::~Chunk()
{
}

void App::Chunk::Render()
{
	block.Render();
}

void App::Chunk::Update()
{
	block.Update();
}
