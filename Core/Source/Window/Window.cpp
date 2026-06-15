#include "Window.h"

#ifdef _WIN32
static void ApplyTitleBarTheme(HWND hwnd)
{
	bool systemDarkMode = false;
	HKEY hKey;
	if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		DWORD value = 0;
		DWORD size = sizeof(value);

		if (RegQueryValueExW(hKey, L"AppsUseLightTheme", nullptr, nullptr, reinterpret_cast<LPBYTE>(&value), &size) == ERROR_SUCCESS)
		{
			systemDarkMode = (value == 0);
		}

		RegCloseKey(hKey);
	}

	BOOL useDarkMode = systemDarkMode ? TRUE : FALSE;
	DwmSetWindowAttribute(hwnd, 20, &useDarkMode, sizeof(useDarkMode));

#if 0	// for Windows 11 only (For custom titlebar color), currently disabled
	COLORREF titleBarColor = systemDarkMode ? RGB(16, 16, 16) : RGB(240, 240, 240);
	DwmSetWindowAttribute(hwnd, 35, &titleBarColor, sizeof(titleBarColor));
#endif

	SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE);
}

static LRESULT CALLBACK ThemeSubclassProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	if (msg == WM_SETTINGCHANGE && lParam != 0)
	{
		if (wcscmp(reinterpret_cast<LPCWSTR>(lParam), L"ImmersiveColorSet") == 0)
		{
			ApplyTitleBarTheme(hwnd);
		}
	}

	return DefSubclassProc(hwnd, msg, wParam, lParam);
}
#endif

static void ErrorCallback(int error, const char* description)
{
	std::print(stderr, "\033[31m[Error] GLFW error {}: {} (GLFW windowing API)\033[0m\n", error, description);
}

Core::Window::Window(const WindowData& windowData)
	: windowData(windowData), width(windowData.width), height(windowData.height), fullscreenMode(windowData.fullscreen)
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize window (GLFW windowing API)\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, windowData.resizable);
	glfwWindowHint(GLFW_DECORATED, windowData.decorated);

	window = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), nullptr, nullptr);
	if (window == nullptr || !window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window (GLFW windowing API)\n");
	}

#ifdef _WIN32
	hwnd = glfwGetWin32Window(window);

	ApplyTitleBarTheme(hwnd);
	SetWindowSubclass(hwnd, ThemeSubclassProcess, 1, 0);
#endif

		glfwMakeContextCurrent(window);

		glfwSwapInterval(windowData.vSync);

	if (windowData.icon.has_value() && std::filesystem::exists(*windowData.icon))
	{
		GLFWimage icon[1];
		int width, height, channels;

		unsigned char* image = stbi_load((*windowData.icon).c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (image)
		{
			icon[0].width = width;
			icon[0].height = height;
			icon[0].pixels = image;

			glfwSetWindowIcon(window, 1, icon);

			stbi_image_free(image);
		}
	}
	else if (windowData.icon.has_value() && !std::filesystem::exists(*windowData.icon))
	{
		std::print(stdout, "\033[33mFailed to load icon with path: '{}'. Application will use operating system's default icon instead (GLFW windowing API, Input/Output)\033[0m\n", *windowData.icon);
	}

	restoredWidth = windowData.width;
	restoredHeight = windowData.height;
	restoredX = 0;
	restoredY = 0;

	WindowState savedState;
	if (LoadState(savedState))
	{
		glfwSetWindowSize(window, savedState.width, savedState.height);
		glfwSetWindowPos(window, savedState.x, savedState.y);

		if (savedState.fullscreen)
		{
			fullscreenMode = true;
			Fullscreen();
		}
		else if (savedState.maximized)
		{
			glfwMaximizeWindow(window);
		}

		restoredWidth = savedState.width;
		restoredHeight = savedState.height;
		restoredX = savedState.x;
		restoredY = savedState.y;
	}
	else
	{
		SetCenter();
	}

	if (windowData.fullscreen)
	{
		Fullscreen();
	}

	glfwSetWindowUserPointer(window, this);

	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
}

Core::Window::~Window()
{
	SaveState();

#ifdef _WIN32
	if (hwnd != nullptr)
	{
		RemoveWindowSubclass(hwnd, ThemeSubclassProcess, 1);
	}
#endif

	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}

	glfwTerminate();
}

void Core::Window::Input()
{
	// Mouse
	{
		// Empty for now
	}

	// Keyboard
	{
		double currentTime = glfwGetTime();

		if (currentTime - toggleTime > debounceTime)
		{
			if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
			{
				fullscreenMode = !fullscreenMode;

				Fullscreen();
				toggleTime = currentTime;
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, true);
				toggleTime = currentTime;
			}
		}
	}
}

void Core::Window::Render()
{
	glfwShowWindow(window);
}

void Core::Window::Update()
{
	if (!fullscreenMode && !glfwGetWindowAttrib(window, GLFW_MAXIMIZED))
	{
		glfwGetWindowSize(window, &restoredWidth, &restoredHeight);
		glfwGetWindowPos(window, &restoredX, &restoredY);
	}
	
	glfwSwapBuffers(window);

	glfwPollEvents();
}

bool Core::Window::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Core::Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}

GLFWwindow* Core::Window::GetWindow() const
{
	if (window == nullptr || !window)
	{
		throw std::runtime_error("Failed to return window because window does not exist (GLFW windowing API)");
	}

	return window;
}

std::string Core::Window::GetTitle() const
{
	return windowData.title;
}

glm::vec2 Core::Window::GetWindowSize() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return glm::vec2(width, height);
}

glm::vec2 Core::Window::GetFramebufferSize() const
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	return glm::vec2(width, height);
}

glm::vec2 Core::Window::GetPosition() const
{
	int x, y;
	glfwGetWindowPos(window, &x, &y);

	return glm::vec2(x, y);
}

bool Core::Window::GetMonitorSync() const
{
	return windowData.vSync;
}

bool Core::Window::GetFullscreenMode() const
{
	return fullscreenMode;
}

void Core::Window::SetTitle(const std::string& title)
{
	glfwSetWindowTitle(window, title.c_str());
}

void Core::Window::SetIcon(const std::string& path)
{
	if (!path.empty() && std::filesystem::exists(path))
	{
		GLFWimage icon[1];
		int width, height, channels;

		unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (image)
		{
			icon[0].width = width;
			icon[0].height = height;
			icon[0].pixels = image;

			glfwSetWindowIcon(window, 1, icon);

			stbi_image_free(image);
		}
	}
	else if (!path.empty() && !std::filesystem::exists(path))
	{
		std::print(stdout, "\033[33mFailed to load icon with path: '{}' (GLFW windowing API, Input/Output)\033[0m\n", *windowData.icon);
	}
}

void Core::Window::SetPosition(glm::vec2 position)
{
	glfwSetWindowPos(window, position.x, position.y);
}

void Core::Window::SetCenter()
{
	int windowX, windowY;
	glfwGetWindowPos(window, &windowX, &windowY);

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	windowWidth *= 0.5;
	windowHeight *= 0.5;

	windowX += windowWidth;
	windowY += windowHeight;

	int monitorsLength;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorsLength);
	if (monitors == nullptr)
		return;

	GLFWmonitor* monitor = nullptr;
	int monitorX, monitorY, monitorWidth, monitorHeight;

	for (int i = 0; i < monitorsLength; i++)
	{
		int monitorsX, monitorsY;
		glfwGetMonitorPos(monitors[i], &monitorsX, &monitorsY);

		int monitorsWidth, monitorsHeight;
		GLFWvidmode* monitorVideoMode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);
		if (monitorVideoMode == nullptr)
			continue;
		else
		{
			monitorsWidth = monitorVideoMode->width;
			monitorsHeight = monitorVideoMode->height;
		}

		if ((windowX > monitorsX && windowX < (monitorsX + monitorsWidth)) && (windowY > monitorsY && windowY < (monitorsY + monitorsHeight)))
		{
			monitor = monitors[i];

			monitorX = monitorsX;
			monitorY = monitorsY;

			monitorWidth = monitorsWidth;
			monitorHeight = monitorsHeight;
		}
	}

	if (monitor != nullptr)
		glfwSetWindowPos(window, monitorX + (monitorWidth * 0.5) - windowWidth, monitorY + (monitorHeight * 0.5) - windowHeight);
}

void Core::Window::Fullscreen()
{
	if (fullscreenMode)
	{
		glfwGetWindowPos(window, &x, &y);
		glfwGetWindowSize(window, &width, &height);
	}

	if (glfwGetWindowMonitor(window) == nullptr && fullscreenMode)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = (GLFWvidmode*)glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);

		glfwSwapBuffers(window);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
		glfwSetWindowSize(window, width, height);
		glfwSetWindowPos(window, x, y);

		glfwSwapBuffers(window);
	}
}

void Core::Window::SaveState()
{
	WindowState windowState{};
	windowState.fullscreen = fullscreenMode;
	windowState.maximized = static_cast<bool>(glfwGetWindowAttrib(window, GLFW_MAXIMIZED));

	windowState.width = restoredWidth;
	windowState.height = restoredHeight;
	windowState.x = restoredX;
	windowState.y = restoredY;

	std::ofstream file("Window.state", std::ios::binary);
	if (file)
	{
		file.write(reinterpret_cast<char*>(&windowState), sizeof(windowState));
	}

#ifndef NDEBUG
	std::print(stdout, "\033[33m[Debug] Save window state setting file in path: {}\033[0m\n", std::filesystem::absolute("Window.state").generic_string());
#endif
}

bool Core::Window::LoadState(WindowState& windowState)
{
	std::ifstream file("Window.state", std::ios::binary);
	if (!file)
	{
		return false;
	}

	file.read(reinterpret_cast<char*>(&windowState), sizeof(windowState));

	return file.good();
}

void Core::Window::ResetState()
{
	std::filesystem::remove("Window.state");

	if (fullscreenMode)
	{
		fullscreenMode = false;
		Fullscreen();
	}

	glfwRestoreWindow(window);

	glfwSetWindowSize(window, windowData.width, windowData.height);
	SetCenter();

	restoredWidth = windowData.width;
	restoredHeight = windowData.height;
	glfwGetWindowPos(window, &restoredX, &restoredY);

#ifndef NDEBUG
	std::print(stdout, "\033[33m[Debug] Window state reset to defaults\033[0m\n");
#endif
}