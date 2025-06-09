#version 330 core

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
    uv = vec2(gl_FragCoord.x/uResolution.x, gl_FragCoord.y/uResolution.y) * 2.f - vec2(1.f,1.f);
    uv.x *= AR;
    //uv *= 3.0;
    //zoom out

    mPos = vec2(uMousePos.x/uResolution.x, uMousePos.y/uResolution.y) * 2.f - vec2(1.f,1.f);
    mPos.x *= AR;
    mPos.y *= -1;
    
    vec3 col = vec3(0.f);

    
    //FragColor = vec4(col, 1.f);

    //FragColor.rg = sin(uv * 100);
    if(abs(uv.x - uv.y) <= 0.03f){
        FragColor.rg = sin(uv * 100);
    }
    //else discard;
   
}
