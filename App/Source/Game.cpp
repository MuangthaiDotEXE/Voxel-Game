#include <iostream>
#include <print>
#include <exception>

#ifdef _WIN32
#include <windows.h>
#endif

#include "App.h"

int main(int argc, char** argv)
{
#ifdef _WIN32
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwordMode = 0;

	GetConsoleMode(handleOut, &dwordMode);
	dwordMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	SetConsoleMode(handleOut, dwordMode);
#endif

	Core::CoreData gameData{};
	gameData.name = "Voxel Game";
	gameData.version = { 1, 0, 0 };
	gameData.windowData.width = 854u;
	gameData.windowData.height = 480u;
	gameData.windowData.title = "Voxel Game";

	try
	{
		for (size_t i = 0; i < argc; ++i)
		{
			if (std::string(argv[i]) == "--reset-window" && std::filesystem::exists("Window.state"))
			{
				std::filesystem::remove("Window.state");
				break;
			}
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
