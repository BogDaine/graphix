#ifndef OPENGL_STUFF_H
#define OPENGL_STUFF_H

#include "GL/glew.h"
#include "ShaderGL.h"
#include "UniformBlockGL.h"

namespace ogl{
    extern ShaderGL        *appShader;
    extern UniformBlockGL  *appInfoUB;
    extern UniformBlockGL  *userInputUB;
}
void initOpenGL();
#endif