#version 420 core

uniform sampler2D diffuseTexture;

in vec2 fUvs;
in vec3 fNormal;
in vec3 fToLight;
in vec3 fToCamera;

out vec4 out_Color;

uniform vec3 lightColor;

void main() {
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
    
    float shininess = 50.0;
    float reflectivity = 1.0;

    float factor = dot(reflected, unitCamera);
    factor = max(factor, 0.0);
    float damping = pow(factor, shininess);
    vec3 specular = damping * reflectivity * lightColor;

    out_Color = vec4(diffuse, 1.0) * texel + vec4(specular, 1.0);
}
