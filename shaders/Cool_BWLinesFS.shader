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

// float WIN_WIDTH = 800.f;
// float WIN_HEIGHT = 600.f;
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

    // float angle = 0.f;//PI/2.f;
    // float angle = PI/6.f;
    float angle = uTime*0.3;// * 0.1;
    // float angle = 2./3.*PI;
    
    vec2 n = vec2(sin(angle), cos(angle));
    
    //uv.x +=.5;
    int iterations = 3;
    float scale = 1.;
    for(int i = 0; i < iterations; i++){
        scale *= 3.;
        uv *= 3.;
        uv.y = abs(uv.y);
        uv.x = abs(uv.x);
        uv.x -= .5;
        uv.y -= .5;

        float x = dot(uv, n);// + dot(uv, -n);
        uv -= n* min(0., x) * 2;
        //uv -= n* x * 2;
    }

    float clp = scale/3.;
    //clp = 27.;
    vec2 nn = vec2(clamp(uv.x, -clp, clp), 0.);
    float d = length(uv - nn);
    col += smoothstep(0.2f, 0.0f, (d));
    //col = vec3(sin(uTime), cos(uTime), 0.f) * d;
    // FragColor = vec4(0.f, 0.f, 0.f, 1.f);
    FragColor = vec4(col, 1.f);
    //  vec3 newC = vec3(0.796, 0.11, 0.859);
    //  FragColor = vec4(newC * sin(d*.3), 1.f);
    //  FragColor = vec4(vec3((d)), 1.f);
    //  FragColor.rg += uv;
     //FragColor.rg *= sin(uv)*sin(d);
    //  FragColor.b *= sin(uv.x*(uTime));
   
}
