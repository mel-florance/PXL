#version 420 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvs;
out vec2 fUvs;

void main() 
{
	vec2 pos = position - vec2(400, 300);
	pos /= vec2(400, 300);
	gl_Position = vec4(pos, 0, 1);

	fUvs = uvs;
}
