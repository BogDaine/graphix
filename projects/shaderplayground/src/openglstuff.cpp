#include "shaderplayground.h"
#include "openglstuff.h"

#include <vector>

ShaderGL        *ogl::appShader;
UniformBlockGL  *ogl::appInfoUB;
UniformBlockGL  *ogl::userInputUB;

void initOpenGL(){

    GLenum error = glewInit();
    if(error != GLEW_OK){
        std::cout << "GLEW ERROR::" << error << std::endl;
        exit(-1);
    }


    using namespace ogl;
    // appShader = new ShaderGL("..\\..\\shaders\\default_vert.shader", "..\\..\\shaders\\basic_frag.shader");
    appShader = new ShaderGL("..\\..\\shaders\\default_vert.shader", "..\\..\\shaders\\linesfs.shader");
    // appShader = new ShaderGL("..\\..\\shaders\\default_vert.shader", "..\\..\\shaders\\kaleidoscope1_FS.shader");
    
    appInfoUB = new UniformBlockGL("app_info", 0, 4, std::vector<const char*>
        {"uResolution", "uWindowPos", "uTime", "uDeltaTime"}.data());

    userInputUB = new UniformBlockGL("user_input", 1, 3, std::vector<const char*>
        {"uMousePos", "uMouseBtnPressed", "uMouseDelta"}.data());

    appInfoUB->Init(appShader->GetID());
    userInputUB->Init(appShader->GetID());

    appInfoUB->SetShaderBinding(appShader->GetID());
    userInputUB->SetShaderBinding(appShader->GetID());
}