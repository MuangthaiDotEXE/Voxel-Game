#include "World.h"

App::World::World(Core::Core& core)
	: chunk(), camera(core.window->GetWindow(), glm::vec3(0.0f, 0.0f, 5.0f))
{
}

App::World::~World()
{
}

void App::World::Render()
{
	chunk.Render();
}

void App::World::Update()
{
	glClearColor(0.529f, 0.808f, 0.922f, 1.000f);

	camera.UpdateMatrix(70.0f, nearPlane, farPlane);
	camera.Input();

	chunk.block.shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(chunk.block.shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(chunk.block.transform.GetMatrix()));
	camera.Matrix(chunk.block.shader, "cameraMatrix");
	chunk.block.Update();
}
