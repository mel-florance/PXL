#version 420 core

layout (location = 0) in vec2 position;
out vec2 fUvs;

uniform mat4 mTransform;

void main() 
{
    gl_Position = mTransform * vec4(position, 0.0, 1.0);
    fUvs = vec2((position.x + 1.0) / 2.0, 1 - (position.y + 1.0) / 2.0);
}