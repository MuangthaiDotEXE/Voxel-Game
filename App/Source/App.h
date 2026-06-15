#pragma once

#ifndef APP_H
#define APP_H

#include "Core.h"

#include "Graphics/World/World.h"

namespace App
{
	class App
	{
	private:
		Core::Core core;

		World world;

	public:
		App(const Core::CoreData& coreData);
		virtual ~App() = default;

		void Render();
		void Update();
	};
}

#endif
