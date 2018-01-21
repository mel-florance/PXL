#version 330

in vec3 position;
out vec3 fUvs;

uniform mat4 mProj;
uniform mat4 mView;
uniform mat4 mTransform;

void main()
{
    fUvs = normalize(position);
    gl_Position = mProj * mView * mTransform * vec4(position, 1.0);
}