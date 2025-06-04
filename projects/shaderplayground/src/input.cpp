#include "input.h"
#include <iostream>

//static double   mousePos[2] = {0.0, 0.0};
static float    mousePosf[2] = {0.0, 0.0};

void input::updateMousePos(double xpos, double ypos){
    mousePosf[0] = (float)xpos;
    mousePosf[1] = (float)ypos;
    ogl::userInputUB->SetUniformValue("uMousePos", mousePosf);
}
