#ifndef OPENGL_STUFF_H
#define OPENGL_STUFF_H

#define MAX_TEXTURE_UNITS           16

#include "GL/glew.h"
#include "ShaderGL.h"
#include "UniformBlockGL.h"

namespace ogl{
    extern ShaderGL        *appShader;
    extern UniformBlockGL  *appInfoUB;
    extern UniformBlockGL  *userInputUB;
    void init();
    void setTextureData(
        GLuint textureUnit,
        int width,
        int height,
        unsigned char *data,
        GLuint format = GL_RGB,
        GLuint wrapS = GL_REPEAT,
        GLuint wrapT = GL_REPEAT,
        GLuint filterMin = GL_LINEAR,
        GLuint filterMag = GL_LINEAR
    );
    void setAppShader(ShaderGL *);
}

#endif