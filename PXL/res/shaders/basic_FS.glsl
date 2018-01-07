#version 420 core

in vec2 fUvs;
in vec3 fNormal;
in vec3 fToLight;
in vec3 fToCamera;
in float fVisibility;

out vec4 out_Color;

uniform vec3 lightColor;
uniform vec3 lightAttenuation; 

uniform vec3 fogColor;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;
uniform float exponent;

uniform int hasDiffuseTexture;
uniform int hasSpecularTexture;
uniform int hasNormalTexture;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

vec3 specular = vec3(0.0, 0.0, 0.0);
vec4 normalMap = vec4(0.0, 0.0, 0.0, 1.0);

void main() 
{
    if(hasNormalTexture == 1)
    {
        normalMap = 2.0 * texture2D(normalTexture, fUvs) - 1.0;
    }

    vec4 texel = vec4(0.0, 0.0, 0.0, 1.0);

    if(hasDiffuseTexture == 1) 
        texel = texture2D(diffuseTexture, fUvs);
    else
        texel = vec4(Kd, 1.0);

    if(texel.a < 0.5)
        discard;

    vec3 unitNormal;

    if(hasNormalTexture == 1)
        unitNormal = normalize(normalMap.rgb);
    else
        unitNormal = normalize(fNormal);

    float dist = length(fToLight);
    float attenuationFactor = lightAttenuation.x + (lightAttenuation.y * dist) + (lightAttenuation.z * dist * dist);

    vec3 unitLight = normalize(fToLight);
    vec3 unitCamera = normalize(fToCamera);    

    float nDot = dot(unitNormal, unitLight);
    float brightness = max(nDot, Ka.x);
    vec3 diffuse = (brightness * lightColor) / attenuationFactor;

    vec3 lightDirection = -unitLight;
    vec3 reflected = reflect(lightDirection, unitNormal);

    if(shininess > 0.0) 
    {
        float factor = dot(reflected, unitCamera);
        factor = max(factor, 0.0);
        float damping = pow(factor, shininess);
        specular = (damping * exponent * lightColor) / attenuationFactor;
    }

    if(hasSpecularTexture == 1)
    {
        vec4 specularMap = texture2D(specularTexture, fUvs);
        specular *= specularMap.rgb;
    }

    out_Color = texel * vec4(diffuse * Kd, 1.0) + vec4(specular * Ks, 1.0); 
    out_Color = mix(vec4(fogColor, 1.0), out_Color, fVisibility);
}
