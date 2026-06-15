#pragma once

#ifndef CHUNK_H
#define CHUNK_H

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "../Block/Block.h"

#define CHUNK_SIZE 16

namespace App
{
	class Chunk
	{
	public:
		Block block;

	public:
		Chunk();
		virtual ~Chunk();

		void Render();
		void Update();
	};
}

#endif
