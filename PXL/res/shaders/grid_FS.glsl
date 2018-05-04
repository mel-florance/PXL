#version 420

in vec2 fUvs;
out vec4 out_Color;

int multiplicationFactor = 200;
float threshold = 0.05;
vec4 color1 = vec4(0.0, 0.0, 1.0, 1.0);
vec4 color2 = vec4(1.0, 1.0, 0.5, 1.0);

// vec2 transform_forward(vec2 P)
// {
//     float x = P.x * cos(P.y);
//     float y = P.x * sin(P.y);
    
//     return vec2(x,y);
// }

// // Inverse transform (polar)
// vec2 transform_inverse(vec2 P)
// {
//     float rho = length(P);
//     float theta = atan(P.y,P.x);

//     if( theta < 0.0 )
//         theta = 2.0*M_PI+theta;

//     return vec2(rho,theta);
// }

// // [-0.5,-0.5]x[0.5,0.5] -> [xmin,xmax]x[ymin,ymax]
// vec2 scale_forward(vec2 P, vec4 limits)
// {
//     // limits = xmin,xmax,ymin,ymax
//     P += vec2(.5,.5);
//     P *= vec2(limits[1] - limits[0], limits[3]-limits[2]);
//     P += vec2(limits[0], limits[2]);

//     return P;
// }

// // [xmin,xmax]x[ymin,ymax] -> [-0.5,-0.5]x[0.5,0.5]
// vec2 scale_inverse(vec2 P, vec4 limits)
// {
//     // limits = xmin,xmax,ymin,ymax
//     P -= vec2(limits[0], limits[2]);
//     P /= vec2(limits[1]-limits[0], limits[3]-limits[2]);

//     return P - vec2(.5,.5);
// }

// float stroke_alpha(float distance, float linewidth, float antialias)
// {
//     float t = linewidth/2.0 - antialias;
//     float signed_distance = distance;
//     float border_distance = abs(signed_distance) - t;
//     float alpha = border_distance/antialias;
//     alpha = exp(-alpha*alpha);

//     if( border_distance > (linewidth/2.0 + antialias) )
//         return 0.0;
//     else if( border_distance < 0.0 )
//         return 1.0;
//     else
//         return alpha;
// }

// // Compute the nearest tick from a (normalized) t value
// float get_tick(float t, float vmin, float vmax, float step)
// {
//     float first_tick = floor((vmin + step/2.0)/step) * step;
//     float last_tick = floor((vmax + step/2.0)/step) * step;
//     float tick = vmin + t*(vmax-vmin);

//     if (tick < (vmin + (first_tick-vmin)/2.0))
//         return vmin;

//     if (tick > (last_tick + (vmax-last_tick)/2.0))
//         return vmax;

//     tick += step/2.0;
//     tick = floor(tick/step)*step;

//     return min(max(vmin,tick),vmax);
// }

// // Compute the distance (in screen coordinates) between A and B
// float screen_distance(vec4 A, vec4 B)
// {
//     vec4 pA = projection*view*model*A;
//     pA /= pA.w;
//     pA.xy = pA.xy * iResolution/2.0;
//     vec4 pB = projection*view*model*B;
//     pB /= pB.w;
//     pB.xy = pB.xy * iResolution/2.0;

//     return length(pA.xy - pB.xy);
// }

// void main() 
// {
//     float x = fract(fUvs.s * multiplicationFactor);
//     float f = smoothstep(0.40, 0.5, x) - smoothstep(0.90, 1.0, x);
//     out_Color = mix(color2, color1, f);
// }
