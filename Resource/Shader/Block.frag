#version 460 core

out vec4 fragColor;

in vec3 color;
in vec2 textureUV;

uniform sampler2D textureSampler;

void main()
{
	//fragColor = vec4(color, 1.0f);
	fragColor = texture(textureSampler, textureUV);
}
