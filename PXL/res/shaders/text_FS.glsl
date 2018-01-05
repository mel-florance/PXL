#version 330 core

in vec2 fUvs;
out vec4 out_Color;
uniform sampler2D diffuseTexture;

void main() 
{
	out_Color = texture(diffuseTexture, fUvs);
    // out_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
