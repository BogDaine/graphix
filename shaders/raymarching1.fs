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

float sphereSDF(vec3 p, vec3 spherePos, float sphereRadius){
    return length(p - spherePos) - sphereRadius;
}

float sceneDist(vec3 p){
    float obj1 =
    min(sphereSDF(p, vec3(-0., -0.1, 0.3), 0.05),
    sphereSDF(p, vec3(0.13, -0.1, 0.33), .05));
    obj1 = sphereSDF(p, vec3(0.5 + sin(uTime) * .1, 0.5 + cos(uTime) * .1, 0.5), 0.1);
    // float obj2_prime = 0
    // max(sphereSDF(p, vec3(0.2, -0.05, .3), 0.1),
    // -sphereSDF(p, vec3(0.7, -0.1, 0.28), 0.1));

    // float obj2 = 
    // max(obj2_prime,
    //     -sphereSDF(p, vec3(2., (sin(uTime)) * 0.2, 2.3 + .5 * cos(uTime)), .3 + .5 * abs(cos(uTime * 0.1))));

    //if(value > 200.)
        //value = ;
    //float    value = min(obj1, obj2);
    float value = obj1;
    return value;
    
}

vec3 getNormal(vec3 p){
    float d = sceneDist(p);
    if(d > 80.)
        return vec3(0.);
    return normalize(
        vec3(
        d - sceneDist(p - vec3(0.01, 0., 0.)),
        d - sceneDist(p - vec3(0., 0.01, 0.)),
        d - sceneDist(p - vec3(0.0, 0., 0.01))
        ));
}

void main()
{
    float AR = uResolution.x/uResolution.y;
    uv = vec2(gl_FragCoord.x/uResolution.x, gl_FragCoord.y/uResolution.y) * 2.f - vec2(1.f,1.f);
    uv.x *= AR;
    mPos = uMousePos;
    mPos.x /= uResolution.x * AR;
    mPos.y /= uResolution.y;

    vec3 lightPos = vec3(130. * sin(uTime), 129., -70. + 62. * cos(uTime));
    vec3 lightCol = vec3(0.941, 0.843, 0.639);
    vec3 ambientLight = vec3(0.316, 0.48, 0.465);
    vec3 objCol = vec3((0.639, 0.478, 0.239));
    vec3 clearCol = vec3(0.741, 0.553, 0.655);
    //uv *= 3.0;
    //zoom out

    vec3 camPos = vec3(0., 0., 0.);
    vec3 rayDir = normalize(vec3(uv, 1.));



    
    //spherePos = vec3(0., 0., 3.);
    float sphereRadius = 1.;
    float d = 0.;
    vec3 p = camPos;
    int i;

    

    const int dLimit = 20; 
    vec3 col = vec3(0.);
    int iterations = 128;
    float mf = .8;
    float iterationsf = iterations;
    for(i = 0; i < iterations; ++i){
        p = camPos + rayDir * d;
        //p.x *= sin(d);
        //p.y *= cos(d);
        p = vec3(mod(p.x, mf), mod(p.y, mf), mod(p.z, mf));
        //p+=sin(d);
        //float dScene = length(p - spherePos) - sphereRadius;
        float dScene = sceneDist(p);
        d +=  dScene;

        col = vec3(1-i/iterationsf);
        if(dScene < 0.00001 || d > dLimit)
            break;
    }
    
    //FragColor = vec4(mPos.x, mPos.y, 0.f, 1.0f);
    //FragColor = vec4(d,d,d,1.);
    //FragColor = vec4(vec3(d/dLimit),1.);
    vec3 normal = getNormal(p);
    if(length(normal) <.99){
        col = clearCol;
    }
    else
    {
        float lightAngle = clamp((dot(normalize(lightPos - p), normal)), 0., 1.);
        //col = getNormal(p);
        col = (lightCol) * lightAngle + (ambientLight) * (objCol * 2);
    }
    FragColor = vec4(col,1.);
    
   
}