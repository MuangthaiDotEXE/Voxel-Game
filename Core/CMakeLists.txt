set(SOURCES
	"Source/Core.h"
	"Source/Core.cpp"
	"Source/Window/Window.h"
	"Source/Window/Window.cpp"
	"Source/Graphics/Graphics.h"
	"Source/Graphics/Graphics.cpp"
	"Source/Graphics/OpenGL.h"
	"Source/Graphics/OpenGL.cpp"
	"Source/Graphics/Shader/Shader.h"
	"Source/Graphics/Shader/Shader.cpp"
	"Source/Graphics/Shader/VertexArray.h"
	"Source/Graphics/Shader/VertexArray.cpp"
	"Source/Graphics/Shader/VertexBuffer.h"
	"Source/Graphics/Shader/VertexBuffer.cpp"
	"Source/Graphics/Shader/ElementBuffer.h"
	"Source/Graphics/Shader/ElementBuffer.cpp"
	"Source/Graphics/Texture/Texture.h"
	"Source/Graphics/Texture/Texture.cpp"
	"Source/Graphics/Texture/stb.cpp"
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
