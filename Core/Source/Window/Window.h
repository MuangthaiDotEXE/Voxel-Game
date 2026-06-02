#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <print>
#include <cstdio>
#include <cstdint>
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>
#include <stdexcept>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <dwmapi.h>
#include <winreg.h>
#include <commctrl.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "comctl32.lib")
#endif

namespace Core
{
	struct WindowData
	{
		std::string title = "App";
		std::optional<std::string> icon = std::nullopt; // pass std::nullopt instead of nullptr
		uint32_t width = 640u, height = 480u;
		bool vSync = true;
		bool resizable = true;
		bool decorated = true;
		bool fullscreen = false;
	};

	struct WindowState
	{
		int width, height;
		int x, y;
		bool maximized = false;
		bool fullscreen = false;
	};

	class Window
	{
	private:
		WindowData windowData;

		GLFWwindow* window;
		int width, height, x, y;

		double toggleTime = 0.0;
		const double debounceTime = 0.15;

		bool fullscreenMode;

		int restoredWidth, restoredHeight;
		int restoredX, restoredY;

#ifdef _WIN32
		HWND hwnd;
#endif

	public:
		Window(const WindowData& windowData = WindowData());
		virtual ~Window();

		void Input();
		void Render();
		void Update();

		[[nodiscard]] bool ShouldClose() const;
		void Close();

		GLFWwindow* GetWindow() const;
		std::string GetTitle() const;
		glm::vec2 GetWindowSize() const;
		glm::vec2 GetFramebufferSize() const;
		glm::vec2 GetPosition() const;
		bool GetMonitorSync() const;
		bool GetFullscreenMode() const;

		void SetTitle(const std::string& title);
		void SetIcon(const std::string& path);
		void SetPosition(glm::vec2 position);

	private:
		void SetCenter();
		void Fullscreen();

		void SaveState();
		bool LoadState(WindowState& windowState);
		void ResetState();
	};
}

#endif