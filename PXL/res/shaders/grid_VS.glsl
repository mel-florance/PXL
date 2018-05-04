#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
out vec2 fUvs;

uniform mat4 mTransform;
uniform mat4 mView;
uniform mat4 mProj;

void main() 
{
    fUvs = uvs;
    gl_Position = mProj * mView * mTransform * vec4(position, 1.0);
}
