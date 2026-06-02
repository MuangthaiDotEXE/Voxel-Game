#include "Core.h"

Core::Core::Core(const CoreData& coreData)
	: coreData(coreData)
{
	std::print(stdout, "{} v{}.{}.{}\n", coreData.name, coreData.version[0], coreData.version[1], coreData.version[2]);

	window = std::make_unique<Window>(coreData.windowData);
	graphics = std::make_unique<OpenGL>(window->GetWindow());
}

void Core::Core::Render()
{
	window->Render();
	graphics->Render();
}

void Core::Core::Update()
{
	window->Update();
	graphics->Update();

	OpenGL* gl = dynamic_cast<OpenGL*>(graphics.get());
	if (gl)
	{
		gl->ViewportResize();
	}

	window->Input();
}
