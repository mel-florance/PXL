#version 420 core

in vec2 fUvs;
out vec4 out_Color;

uniform sampler2D diffuseTexture;
uniform int hasDiffuseTexture;
uniform vec3 diffuseColor;
uniform float alpha;

vec4 linearGradient(vec3 a, vec3 b, vec2 uvs, int res, float f)
{
    vec4 top = vec4(a, f);
    vec4 bottom = vec4(b, 0);

    return vec4(mix(top, bottom, uvs.y / 0.8)); 
}

void main() 
{
    vec4 texel;

    if(hasDiffuseTexture == 1)
        texel = texture(diffuseTexture, fUvs);
    else
        texel = linearGradient(diffuseColor, vec3(0.0, 0.0, 0.0), fUvs, 10, alpha);
        
    out_Color = texel;
}
