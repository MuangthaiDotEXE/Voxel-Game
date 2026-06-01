#include "Core.h"

Core::Core::Core(const CoreData& coreData)
	: coreData(coreData)
{
	std::print(stdout, "{} v{}.{}.{}\n", coreData.name, coreData.version[0], coreData.version[1], coreData.version[2]);
}

void Core::Core::Render()
{
}

void Core::Core::Update()
{
}
