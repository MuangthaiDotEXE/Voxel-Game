#version 460 core

layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 colors;
layout (location = 2) in vec2 textures;

out vec3 color;
out vec2 textureUV;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
	gl_Position = cameraMatrix * model * vec4(positions, 1.0f);

	color = colors;
	textureUV = textures;
}
