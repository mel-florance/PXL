#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normal;

out vec2 fUvs;
out vec3 fNormal;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 1.0);
    fUvs = uvs;
    fNormal = vec3(transform * vec4(normal, 0.0)).xyz;
}
