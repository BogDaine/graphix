#ifndef SHADERPLAYGROUND_H
#define SHADERPLAYGROUND_H

#include "appinfo.h"

void init();

void createWindow();
void mainLoop();

void loadImage(unsigned int textureUnit, const char *path);
void loadShader(const char *vertexPath, const char *fragmentPath);

void updateUniforms();
void drawScene();

void showUI();
void initUI();
void initUIText();
#endif