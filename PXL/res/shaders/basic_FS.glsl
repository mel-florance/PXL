#version 330

uniform sampler2D diffuse;

in vec2 fUvs;
in vec3 fNormal;

out vec4 out_Color;

void main() {
    out_Color = texture2D(diffuse, vec2(fUvs.x, fUvs.y * -1)) 
    * clamp(dot(-vec3(0, 0, 1), fNormal), 0.0, 1.0);
}
