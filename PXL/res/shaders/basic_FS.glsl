#version 330

uniform sampler2D diffuseTexture;

in vec2 fUvs;
in vec3 fNormal;
in vec3 fToLight;

out vec4 out_Color;

uniform vec3 lightColor;

void main() {
    vec3 unitNormal = normalize(fNormal);
    vec3 unitLight = normalize(fToLight);

    float nDot = dot(unitNormal, unitLight);
    float brightness = max(nDot, 0.1);
    vec3 diffuse = brightness * lightColor;


    out_Color = vec4(diffuse, 1.0) * texture2D(diffuseTexture, vec2(fUvs.x, fUvs.y * -1));
}
