#include <iostream>
#include <print>
#include <exception>

#include "App.h"

int main(int argc, char** argv)
{
	Core::CoreData gameData{};
	gameData.name = "Voxel Game";
	gameData.version = { 1, 0, 0 };

	try
	{
		for (size_t i = 0; i < argc; ++i)
		{

		}

		App::App game(gameData);

		game.Render();
		game.Update();
	}
	catch (const std::exception& exception)
	{
		std::print(stderr, "\033[31m[Error] An exception was thrown: {}\033[0m\n", exception.what());

		return 1;
	}

	return 0;
}
