#include "shaderplayground.h"
#include "openglstuff.h"

#include "GLCall.h"
#include "myutils.h"

#include <vector>
#include <string>
#include <iostream>

ShaderGL        *ogl::appShader;
UniformBlockGL  *ogl::appInfoUB;
UniformBlockGL  *ogl::userInputUB;

static GLuint   textures[MAX_TEXTURE_UNITS];

void setShaderSamplerUniforms();
void prepShader(){
    using namespace ogl;
    appInfoUB->SetShaderBinding(appShader->GetID());
    userInputUB->SetShaderBinding(appShader->GetID());
    setShaderSamplerUniforms();
}


void ogl::init(){

    GLenum error = glewInit();
    if(error != GLEW_OK){
        std::cout << "GLEW ERROR::" << error << std::endl;
        exit(-1);
    }

    using namespace ogl;

    //TODO: auto generate default shader or just have the source here

    appShader = new ShaderGL(
        MyUtils::readFile("..\\..\\shaders\\default.vert").c_str(),
        MyUtils::readFile("..\\..\\shaders\\basic.frag").c_str()
    );

    appInfoUB = new UniformBlockGL("app_info", 0, 4, std::vector<const char*>
        {"uResolution", "uWindowPos", "uTime", "uDeltaTime"}.data());

    userInputUB = new UniformBlockGL("user_input", 1, 3, std::vector<const char*>
        {"uMousePos", "uMouseBtnPressed", "uMouseDelta"}.data());

    appInfoUB->Init(appShader->GetID());
    userInputUB->Init(appShader->GetID());

    appInfoUB->SetShaderBinding(appShader->GetID());
    userInputUB->SetShaderBinding(appShader->GetID());

    glGenTextures(MAX_TEXTURE_UNITS, textures);
    for (size_t i = 0; i < MAX_TEXTURE_UNITS; ++i){
        glActiveTexture(i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    prepShader();
}

void setShaderSamplerUniforms(){
    using namespace ogl;
    for(size_t i = 0; i < MAX_TEXTURE_UNITS; ++i){
        appShader->SetInt("texture" + std::to_string(i), i);
    }
}


bool ogl::setAppShader(ShaderGL *newShader){
    if(!newShader->IsLinked()){
        return false;
    }
    delete appShader;
    appShader = newShader;
    prepShader();
    return true;
}

void ogl::setTextureData(
    GLuint textureUnit,
    int width,
    int height,
    unsigned char *data,
    GLuint format,
    GLuint wrapS,
    GLuint wrapT,
    GLuint filterMin,
    GLuint filterMag
)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textures[textureUnit]);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);
}