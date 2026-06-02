#include "Core.h"

Core::Core::Core(const CoreData& coreData)
	: coreData(coreData)
{
	std::print(stdout, "{} v{}.{}.{}\n", coreData.name, coreData.version[0], coreData.version[1], coreData.version[2]);

	window = std::make_unique<Window>(coreData.windowData);
}

void Core::Core::Render()
{
	window->Render();
}

void Core::Core::Update()
{
	while (!window->ShouldClose())
	{
		window->Update();
	}
}
