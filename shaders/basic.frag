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

    //uv = (gl_FragCoord.x - 0.5f * uResolution)/uResolution.y;

    mPos = vec2(uMousePos.x/uResolution.x, uMousePos.y/uResolution.y) * 2.f - vec2(1.f,1.f);
    //mPos = vec2(uMousePos.x, uMousePos.y);
    //mPos.x *= AR;
    //mPos.y *= -1;

    //mPos = vec2(0., 0.);

    //FragColor = vec4(gl_FragCoord.x/800.f, 1.f-(gl_FragCoord.x/800.f), TexCoords.x, 1.f);
    FragColor = vec4(0.3, TexCoords.x, 0.f, 1.f);

    vec3 color = vec3(1.0, abs(cos(uTime)), 1.0);
    float d = length(mPos - uv);
    float x = (uv.x * (cos(uTime*.3f)) * cos(uTime*.3f) * 50);
    float y = (uv.y * (cos(uTime*.3f)) * cos(uTime*.3f) * 50);
    FragColor.rg = vec2(sin(x), cos(y));
    
    vec4 scrColor = FragColor;

    float m = smoothstep(0.f,1.6f , d);

    if(d < 0.04f){
        FragColor = vec4(color * (d * 10.f), 1.0f);
    }
    // vec4 mouseColor = vec4(color * (m * 10.f), 1.0f);
    // FragColor = m * mouseColor + (1.f - m) * scrColor;
    // FragColor.rgb = vec3(1.f) - FragColor.rgb;
   
}