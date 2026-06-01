set(SOURCES
	"Source/Game.cpp"
	"Source/App.h"
	"Source/App.cpp"
)

add_executable(App)
target_sources(App PRIVATE ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

target_compile_definitions(App PRIVATE
	ProjectDirectory=\"${PROJECT_SOURCE_DIR}\"
	AppDirectory=\"${PROJECT_SOURCE_DIR}/App\"
)

target_compile_definitions(App PRIVATE
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(App Core)
target_include_directories(App PRIVATE "Source")

if (MSVC)
	set_target_properties(App PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/App")
endif()
