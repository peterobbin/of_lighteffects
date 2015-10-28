//  by @peterobbin


#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform float u_timer;
uniform float u_size;
uniform float u_brightness;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution;
    float pct = 0.0;
    vec2 mousePos = u_mouse/u_resolution;
    float brightness = pow(u_timer, 3.0) * u_brightness;
    float size = u_size;
    
    
    pct = 1.0 - distance(st - vec2(mousePos.x, 1.0 - mousePos.y),vec2(0.0)) * 4.0 * size ;
    
    
    
    vec4 color = vec4(pct * brightness);
    
    gl_FragColor = vec4( color );
}