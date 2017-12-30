#version 120

attribute vec3 position;
attribute vec2 uvs;
attribute vec3 normal;

varying vec2 fUvs;
varying vec3 fNormal;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 1.0);
    fUvs = uvs;
    fNormal = vec3(transform * vec4(normal, 0.0)).xyz;
}
