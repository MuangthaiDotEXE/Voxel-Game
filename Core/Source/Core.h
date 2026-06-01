#pragma once

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <print>
#include <string>
#include <cstdint>
#include <array>

namespace Core
{
	struct CoreData
	{
		std::string name = "App";
		std::array<uint32_t, 3> version = { 0, 0, 0 };
	};

	class Core
	{
	private:
		CoreData coreData;

	public:
		Core(const CoreData& coreData = CoreData());
		virtual ~Core() = default;

		void Render();
		void Update();
	};
}

#endif
