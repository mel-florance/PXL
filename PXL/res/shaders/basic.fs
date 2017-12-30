#version 120

uniform sampler2D diffuse;

varying vec2 fUvs;
varying vec3 fNormal;

void main() {
    gl_FragColor = texture2D(diffuse, vec2(fUvs.x, fUvs.y * -1)) 
    * clamp(dot(-vec3(0, 0, 1), fNormal), 0.0, 1.0);
}
