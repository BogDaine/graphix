#ifndef SHADERPLAYGROUND_H
#define SHADERPLAYGROUND_H

#include "openglstuff.h"
#include "appinfo.h"
#include "input.h"

#include <iostream>

void init();

void createWindow();
void mainLoop();

void updateUniforms();
void drawScene();

#endif