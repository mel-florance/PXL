#version 420 core

in vec2 fUvs;
in vec3 fNormal;
in vec3 fToLight;
in vec3 fToCamera;

out vec4 out_Color;

uniform vec3 lightColor;

uniform float Ka;
uniform float Kd;
uniform float Ks;
uniform vec3 diffuseColor;
uniform vec3 ambientColor;
uniform vec3 specularColor;
uniform float shininess;

uniform sampler2D diffuseTexture;

vec3 specular = vec3(0.0, 0.0, 0.0);

void main() {
    vec4 texel = texture2D(diffuseTexture, fUvs);

    if(texel.a < 0.5)
        discard;

    vec3 N = normalize(fNormal);
    vec3 L = normalize(fToLight);

    float lambertian = max(dot(N, L), 0.0);
    float specular = 0.0;

    if(lambertian > 0.0) {
        vec3 R = reflect(-L, N);
        vec3 V = normalize(fToCamera);

        float specAngle = max(dot(R, V), 0.0);
        specular = pow(specAngle, shininess);
    }

    out_Color = texel * vec4(Ka * ambientColor + Kd * lambertian * diffuseColor + Ks * specular * specularColor, 1.0);


    // vec3 unitNormal = normalize(fNormal);
    // vec3 unitLight = normalize();
    // vec3 unitCamera = normalize(fToCamera);    

    // float nDot = dot(unitNormal, unitLight);
    // float brightness = max(nDot, 0.1);
    // vec3 diffuse = brightness * lightColor;

    // vec3 lightDirection = -unitLight;
    // vec3 reflected = reflect(lightDirection, unitNormal);

    // if(shininess > 0.0) {
    //     float factor = dot(reflected, unitCamera);
    //     factor = max(factor, 0.0);
    //     float damping = pow(factor, shininess);
    //     specular = damping * reflectivity * lightColor;
    // }

    // out_Color = vec4(diffuse, 1.0) * texel + vec4(specular, 1.0);
}
