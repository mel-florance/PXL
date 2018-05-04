#version 330
#extension GL_OES_standard_derivatives : enable

in vec2 fUvs;
in vec3 fNormal;
in vec4 fVertices;
in vec3 fToLight[8];
in vec3 fToCamera;
in float fVisibility;

out vec4 out_Color;

uniform vec3 lightPosition[8];
uniform vec3 lightColor[8];
uniform int  lightType[8];
uniform vec3 lightAttenuation[8]; 

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

vec4 normalMap = vec4(0.0, 0.0, 0.0, 1.0);
vec4 texel = vec4(0.0, 0.0, 0.0, 1.0);


void main() 
{
    vec3 unitCamera = normalize(fToCamera);    

    if(hasNormalTexture == 1)
        normalMap = 2.0 * texture2D(normalTexture, fUvs) - 1.0;

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

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);


    for(int i = 0; i < 8; i++)
    {
        float dist = length(fToLight[i]);
        float attenuationFactor = lightAttenuation[i].x + (lightAttenuation[i].y * dist) + (lightAttenuation[i].z * dist * dist);

        vec3 unitLight = normalize(fToLight[i]);
        float nDot = dot(unitNormal, unitLight);
        float brightness = max(nDot, 0.0);

        totalDiffuse += (brightness * lightColor[i]) / attenuationFactor;

        vec3 reflected = reflect(-unitLight, unitNormal);
        float factor = dot(reflected, unitCamera);
        factor = max(factor, 0.0);
        float damping = pow(factor, shininess);
        totalSpecular += (damping * exponent * lightColor[i]) / attenuationFactor;
    }

    totalDiffuse = max(totalDiffuse, Ka.x);

    if(hasSpecularTexture == 1)
    {
        vec4 specularMap = texture2D(specularTexture, fUvs);
        totalSpecular *= specularMap.rgb;
    }

    out_Color = vec4(totalDiffuse * Kd, 1.0) * texel + vec4(totalSpecular * Ks, 1.0); 
    out_Color = mix(vec4(fogColor, 1.0), out_Color, fVisibility);
}
