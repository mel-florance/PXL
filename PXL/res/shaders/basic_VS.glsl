#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec2 fUvs;
out vec3 fNormal;
out vec3 fToLight;
out vec3 fToCamera;
out float fVisibility;

uniform mat4 mTransform;
uniform mat4 mView;
uniform mat4 mProj;
uniform float fogDensity;
uniform float fogGradient;

uniform vec3 lightPosition;
uniform int hasNormalTexture;

void main() 
{
    vec4 worldPosition = mTransform * vec4(position, 1.0);
    vec4 posRelToCam = mView * worldPosition;

    gl_Position = mProj * mView * worldPosition;
    fUvs = uvs;

    fNormal = vec3(mTransform * vec4(normal, 0.0)).xyz;

    mat3 TBN = mat3(1.0);
    if(hasNormalTexture == 1)
    {
        vec3 norm = normalize(fNormal);
        vec3 tang = normalize((mTransform * vec4(tangent, 0.0)).xyz);
        vec3 bitang = cross(norm, tang);

        TBN = mat3(
            tang.x, bitang.x, norm.x,
            tang.y, bitang.y, norm.y,
            tang.z, bitang.z, norm.z
        );
    }
    
    fToLight = TBN * (lightPosition - worldPosition.xyz);
    fToCamera = TBN * ((inverse(mView) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz);

    float distance = length(posRelToCam.xyz);
    fVisibility = exp(-pow((distance * fogDensity), fogGradient));
    fVisibility = clamp(fVisibility, 0.0, 1.0);
}
