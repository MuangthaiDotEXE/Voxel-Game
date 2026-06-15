#include "App.h"

App::App::App(const Core::CoreData& coreData)
	: core(coreData), world(core)
{
}

void App::App::Render()
{
	core.Render();
	world.Render();
}

void App::App::Update()
{
	while (!core.window->ShouldClose())
	{
		core.Update();
		world.Update();
	}
}
