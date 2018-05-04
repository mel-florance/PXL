#version 330

in vec3 fUvs;
out vec4 out_Color;

uniform samplerCube cubemap;
uniform samplerCube cubemap2;

uniform vec4 clearColor;
uniform float blendFactor;
uniform vec2 limits;

void main()
{
    vec4 texture1 = texture(cubemap, fUvs);
	vec4 texture2 = texture(cubemap2, fUvs);
	vec4 finalColor = mix(texture1, texture2, blendFactor);

	float factor = (fUvs.y - limits.x) / (limits.y - limits.x);
	factor = clamp(factor, 0.0, 1.0);

	out_Color = mix(clearColor, finalColor, factor);
}