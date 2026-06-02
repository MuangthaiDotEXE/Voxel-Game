#include "App.h"

App::App::App(const Core::CoreData& coreData)
	: core(coreData)
{
}

void App::App::Render()
{
	core.Render();
}

void App::App::Update()
{
	while (!core.window->ShouldClose())
	{
		core.Update();
	}
}
