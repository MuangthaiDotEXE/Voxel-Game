include(FetchContent)

find_package(glfw3 QUIET)
if (NOT glfw_FOUND)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

	FetchContent_Declare(
		glfw3
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
	)

	FetchContent_MakeAvailable(glfw3)
endif()

find_package(OpenGL REQUIRED)

include_directories(
	"Library/glad/include"
)

FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
	GIT_TAG master
)

FetchContent_MakeAvailable(stb)
include_directories("${stb_SOURCE_DIR}")

find_package(glm QUIET)
if (NOT glm_FOUND)
	FetchContent_Declare(
		glm
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/g-truc/glm/releases/download/1.0.3/glm-1.0.3.zip
	)

	FetchContent_MakeAvailable(glm)
endif()
