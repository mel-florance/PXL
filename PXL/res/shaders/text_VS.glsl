#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvs;
out vec2 fUvs;

void main() 
{

	gl_Position = vec4(position, 0.0, 1.0);

vec2 vertexPosition_homoneneousspace = position - vec2(960,540); // [0..800][0..600] -> [-400..400][-300..300]
	vertexPosition_homoneneousspace /= vec2(960,540);
	gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);

	fUvs = uvs;
}
