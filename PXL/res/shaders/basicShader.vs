#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 fTexCoord;
varying vec3 fNormal;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 1.0);
    fTexCoord = texCoord;
    fNormal = vec3(transform * vec4(normal, 0.0)).xyz;
}