#pragma once

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <print>
#include <string>
#include <cstdint>
#include <array>

#include "Window/Window.h"
#include "Graphics/Graphics.h"
#include "Graphics/OpenGL.h"

namespace Core
{
	struct CoreData
	{
		WindowData windowData;

		std::string name = "App";
		std::array<uint32_t, 3> version = { 0, 0, 0 };
	};

	class Core
	{
	private:
		CoreData coreData;

	public:
		std::unique_ptr<Window> window;
		std::unique_ptr<Graphics> graphics;

	public:
		Core(const CoreData& coreData = CoreData());
		virtual ~Core() = default;

		void Render();
		void Update();
	};
}

#endif
