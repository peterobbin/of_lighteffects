#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform float u_particle_lifespan;
uniform float u_range;
uniform float u_thickness;


float Flare1(float x, float range){
    return smoothstep(0.0, 1.0, (1.- pow(x, 2.0) * 5.0 * range + 0.1) * 0.5);
}

float Flare2(float x, float thickness){
    return  (1.0 - smoothstep(0.0, 1.0, pow(max(0.0, abs(x) * 5.0 * thickness - 0.004), 0.5)) * 5.0) * 0.5;
}

void main() {
    float range = u_range;
    float thickness = u_thickness;
    
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec2 mousePos = u_mouse/u_resolution;
    float pct = Flare1(st.x - mousePos.x, range);
    pct += Flare2(1.0 - st.y - mousePos.y, thickness);
    
    vec4 color = vec4(pct* pow(u_particle_lifespan, 5.0));
    
    gl_FragColor = vec4(color);
}