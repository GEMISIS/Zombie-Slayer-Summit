#version 150

in vec3 position;
in vec3 color;
in vec2 uv;

out vec3 Color;
out vec2 UV;

uniform mat4 vp;

void main()
{
    Color = color;
	UV = uv;
    gl_Position = vp * vec4(position, 1.0);
}
