#version 330 core
#define PI 3.14159

out vec4 FragColor;
in vec2 TexCoords;



layout(shared) uniform user_input{
    vec2 uMousePos;
    vec2 uMouseBtnPressed;
    vec2 uMouseDelta;
    //uint uKeyPressed;
};

layout(shared) uniform app_info{
    vec2 uResolution;
    vec2 uWindowPos;
    float uTime;
    float uDeltaTime;
};

vec2 uv;
vec2 mPos;
void main()
{
    float AR = uResolution.x/uResolution.y;
    uv = vec2(gl_FragCoord.x/uResolution.x - 0.5f, gl_FragCoord.y/uResolution.y - 0.5f);// * 2.f - vec2(1.f,1.f);
    uv.x *= AR;
    //uv *= 3.0;
    //zoom out

    vec3 col = vec3(0.f);

    float angle = 0.;//PI/1.f;
    // float angle = PI/6.f;
    // float angle = uTime*0.3;// * 0.1;
    // float angle = 2./3.*PI;
    angle = 1./3.*PI;
    
    vec2 n = vec2(sin(angle), cos(angle));
    
    //uv.y -= .1;
    //uv.x +=.5;
    int iterations = 2;
    float scale = 1.;
    for(int i = 0; i < iterations; i++){
        scale *= 3.;
        uv *= 3.;
         uv.y = abs(uv.y);
        uv.x = abs(uv.x);
        uv.x -= 1.5;
         uv.y -= .5;

        float x = dot(uv, n);// + dot(uv, -n);
        uv -= n* min(0., x) * 2;
        //uv -= n* x * 2;
    }

    // scale *= 3.;
    // uv *= 3.;
    // uv.x -= .5;
    // float x = dot(uv, n);
    
    float clp = scale/3.;
    // clp = 27.;
    vec2 nn = vec2(clamp(uv.x, -clp, clp), 0.);
    float d = length(uv - nn);
    col += smoothstep(0.1f, 0.0f, (d));
    FragColor = vec4(col, 1.f);
      FragColor.rg += uv;
   
}
