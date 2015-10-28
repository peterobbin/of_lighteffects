#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform float u_aspectRatio;
uniform float u_particle_lifespan;


float origin_aR = u_aspectRatio;

mat3 matrix = mat3(vec3(1.,0.,0.),
                   vec3(0.,1.,0.),
                   vec3(0.,0.,1.));


float F1(float x){
    return pow(min(cos(PI * x /2.0), 1.0 - abs(x)), 3.0);
}

float F2(float x){
    return 1.0 - pow(max(0.0, abs(x) * 2.0 - 0.3), 0.5) * 1.0;
}

mat3 scaleMatrix(vec2 f) {
    return mat3(vec3(f.x,0.0,0.0),
                vec3(0.0,f.y,0.0),
                vec3(0.0,0.0,1.0));
}

void scale(in vec2 f, inout mat3 mtx) {
    mtx = scaleMatrix(f) * mtx;
}

mat3 translationMatrix(vec2 f) {
    return mat3(vec3(1.0,0.0,0.0),
                vec3(0.0,1.0,0.0),
                vec3(f.x,f.y,1.0));
}

void translate(vec2 f, inout mat3 mtx) {
    mtx = translationMatrix(f) * mtx;
}

mat3 rotationMatrix(float a) {
    return mat3(vec3(cos(a),-sin(a),0.0),
                vec3(sin(a),cos(a),0.0),
                vec3(0.0,0.0,1.0));
}

void rotate(float a, inout mat3 mtx) {
    mtx = rotationMatrix(a) * mtx;
}
// Reference to
// http://thndl.com/square-shaped-shaders.html

float triShapeDistance(vec2 st, int sides){
    // Remap the space to -1. to 1.
    st.x = st.x  ;

    st.y -= 0.0 ;
    

    //    st.x = st.x * 2.- u_aspectRatio;
    //    st.y = st.y * 2. - 1.0;
    
    //st.x = st.x * 2. - u_aspectRatio;
    
    // Number of sides of your shape
    int N = sides;
    
    // Angle and radius from the current pixel
    float a = atan(st.x,st.y)+PI;
    float r = TWO_PI/float(N);
    
    // Shaping function that modulate the distance
    float d = cos(floor(.5+a/r)*r-a)*length(st);
    
    return d;
    
}

// @appas  noise function from stackoverflow.xom
float snoise(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

 void aspectRatioFix(vec2 st, vec2 mousePos){
     st.x = st.x * u_aspectRatio;
     st.y = st.y / u_aspectRatio;
     mousePos.x = mousePos.x * u_aspectRatio;
     mousePos.y = mousePos.y / u_aspectRatio;
 }

vec3 rgbNormalizer(vec3 color){
    float r = color.r;
    float g = color.g;
    float b = color.b;
    return vec3((r + 1.0)/256.0 , (g + 1.0)/256.0 , (b + 1.0)/256.0 );
    
}



float bokeh(vec2 st, vec2 mousePos, float size, float edgeThickness, float brightness, int sides, float blurriness){
    
    st.x += mousePos.x;
    st.y += mousePos.y;
    float bokSize = 0.04 * size;
    float bokEdge = 0.003 * edgeThickness;
    blurriness *= size;
    
    //frames
    float bok = 1. - (smoothstep(bokSize, bokSize + 2. * bokEdge + 0.05 * blurriness, triShapeDistance(st, sides)) + smoothstep(bokSize + 0.01 * blurriness, bokSize -  1.0 * bokEdge + 0.01 * blurriness, triShapeDistance(st, sides))) ;
    bok*= 1. - clamp(blurriness * 5., 0.0, 1.0);
    
    //shape
    bok += 1. - smoothstep(bokSize - bokEdge + 0.01 * blurriness, bokSize + 0.05 * blurriness, triShapeDistance(st, sides));
    float bokBrightness = 0.9 * brightness;
    bok*= bokBrightness;
    
    return bok;
}

void main() {
    
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 pos = vec3(st + vec2(0.0, -0.0),1.0);
    vec2 mousePos = u_mouse/u_resolution;
    
    translate(vec2(-mousePos.x,  mousePos.y - 1.0), matrix);
    scale(vec2(u_aspectRatio, 1.0),matrix);
    rotate(-u_time * 0.1, matrix);
    pos = matrix * pos;
    float bok = bokeh(pos.xy, vec2(0.0, 0.0), 1.0 - u_particle_lifespan, 1.0, u_particle_lifespan, 6, u_particle_lifespan);
    
    
    
    vec3 color = vec3(st.x, st.y, st.y);
    
    gl_FragColor = vec4(color, bok);
}