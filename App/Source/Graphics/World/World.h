#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Core.h"

#include "Mesh/Chunk/Chunk.h"
#include "Camera/Camera.h"

namespace App
{
	class World
	{
	private:
		Chunk chunk;
		Camera camera;

		float nearPlane = 0.001f, farPlane = 1000.0f;

	public:
		World(Core::Core& core);
		virtual ~World();

		void Render();
		void Update();
	};
}

#endif
