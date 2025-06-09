#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

layout(shared) uniform test{
    float uIntensity;
    vec4 uColor;
};



// layout(shared) uniform textures{
//     sampler2D tex0;
//     sampler2D tex1;
//     sampler2D tex2;
//     sampler2D tex3;
// };

float WIN_WIDTH = 800.f;
float WIN_HEIGHT = 600.f;
vec2 uv;
void main()
{
    float AR = WIN_WIDTH/WIN_HEIGHT;
    uv = vec2(gl_FragCoord.x/WIN_WIDTH, gl_FragCoord.y/WIN_HEIGHT) * 2.f - vec2(1.f,1.f);
    uv.x *= AR;

    //FragColor = vec4(gl_FragCoord.x/800.f, 1.f-(gl_FragCoord.x/800.f), TexCoords.x, 1.f);
    FragColor = vec4(0.3, TexCoords.x, 0.f, 1.f);

    if(length(uv) < 0.5f){
        FragColor = vec4(uColor.x, uColor.y, uColor.z, 1.0f);
    }

   
}