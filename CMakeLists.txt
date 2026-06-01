cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS ON)

project(
	VoxelGame
	VERSION 1.0.0
	LANGUAGES C CXX
	DESCRIPTION "Voxel engine with world generation, like that one game"
)

include("Library.cmake")

add_subdirectory(Core)
add_subdirectory(App)
