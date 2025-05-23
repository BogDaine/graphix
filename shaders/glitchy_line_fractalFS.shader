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
    uv *= 3.0;
    //zoom out

    vec3 col = vec3(0.f);

    // float angle = 0.f;//PI/2.f;
    // float angle = PI/6.f;
    float angle = uTime*0.3;// * 0.1;
    // float angle = 0.f;
    uv.x = abs(uv.x);
    uv.x += 0.5;
    vec2 n = vec2(sin(angle), cos(angle));
    //n = vec2(-1.f);


    float d = dot(uv, n);// + dot(uv, -n);
    //float dist = length(n-uv);
    col += smoothstep(0.01f, 0.0f, abs(d));

    uv -= n*d * uTime;
    //col = vec3(sin(uTime), cos(uTime), 0.f) * d;
    //FragColor = vec4(0.f, 0.f, 0.f, 1.f);
    FragColor = vec4(col, 1.f);
    vec3 newC = vec3(0.796, 0.11, 0.859);
    FragColor = vec4(newC, 1.f);
    //FragColor = vec4(vec3((d)), 1.f);
    FragColor.rg *= sin(uv*10);
    FragColor.b *= sin(uv.x*(uTime*uTime));
   
}
