#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normal;

out vec2 fUvs;
out vec3 fNormal;
out vec3 fToLight;

uniform mat4 mTransform;
uniform mat4 mView;
uniform mat4 mProj;

uniform vec3 lightPosition;

void main() {
    vec4 worldPosition = mTransform * vec4(position, 1.0);
    gl_Position = mProj * mView * worldPosition;
    fUvs = uvs;
    fNormal = vec3(mTransform * vec4(normal, 0.0)).xyz;
    fToLight = lightPosition - worldPosition.xyz;
}
