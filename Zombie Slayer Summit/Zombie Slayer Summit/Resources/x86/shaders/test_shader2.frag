#version 150

in vec3 Color;
in vec2 UV;

out vec4 outColor;

uniform bool hasTexture;
uniform sampler2D in_texture;

void main()
{
	vec3 tempColor = Color;
	if(hasTexture == true)
	{
		tempColor *= texture(in_texture, UV).rgb;
	}
    outColor = vec4(tempColor, 1.0);
}
