#pragma once

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <print>
#include <string>
#include <cstdint>
#include <array>

#include "Window/Window.h"

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

		std::unique_ptr<Window> window;

	public:
		Core(const CoreData& coreData = CoreData());
		virtual ~Core() = default;

		void Render();
		void Update();
	};
}

#endif
