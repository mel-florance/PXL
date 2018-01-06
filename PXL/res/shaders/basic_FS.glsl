#version 420 core

in vec2 fUvs;
in vec3 fNormal;
in vec3 fToLight;
in vec3 fToCamera;
in float fVisibility;

out vec4 out_Color;

uniform vec3 lightColor;
uniform vec3 fogColor;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;

uniform sampler2D diffuseTexture;

vec3 specular = vec3(0.0, 0.0, 0.0);

void main() 
{
    vec4 texel = texture2D(diffuseTexture, fUvs);

    if(texel.a < 0.5)
        discard;

    vec3 unitNormal = normalize(fNormal);
    vec3 unitLight = normalize(fToLight);
    vec3 unitCamera = normalize(fToCamera);    

    float nDot = dot(unitNormal, unitLight);
    float brightness = max(nDot, 0.1);
    vec3 diffuse = brightness * lightColor;

    vec3 lightDirection = -unitLight;
    vec3 reflected = reflect(lightDirection, unitNormal);

    if(shininess > 0.0) 
    {
        float factor = dot(reflected, unitCamera);
        factor = max(factor, 0.0);
        float damping = pow(factor, shininess);
        specular = damping * Ks * lightColor;
    }

    out_Color = texel * vec4(diffuse, 1.0) + vec4(specular, 1.0); 
    out_Color = mix(vec4(fogColor, 1.0), out_Color, fVisibility);
}
