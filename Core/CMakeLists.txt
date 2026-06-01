set(SOURCES
	"Source/Core.h"
	"Source/Core.cpp"
)

add_library(Core STATIC)
target_sources(Core PRIVATE ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

target_compile_definitions(Core PRIVATE
	ProjectDirectory=\"${PROJECT_SOURCE_DIR}\"
	CoreDirectory=\"${PROJECT_SOURCE_DIR}/Core\"
)

target_compile_definitions(Core PUBLIC
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

add_library(glad 
			"${CMAKE_SOURCE_DIR}/Library/glad/src/gl.c"
			"${CMAKE_SOURCE_DIR}/Library/glad/src/gles2.c"
)

target_link_libraries(Core glfw OpenGL::GL glad glm)
target_include_directories(Core PUBLIC "Source")
