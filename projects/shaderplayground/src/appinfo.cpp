#include "appinfo.h"
#include "openglstuff.h"


double  info::appTime;
double  info::deltaTime;
int     info::windowWidth       =       DEFAULT_WINDOW_WIDTH;
int     info::windowHeight      =       DEFAULT_WINDOW_HEIGHT;

static double lastTime = 0;

void info::init(){
    info::updateResolution(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
}

void info::updateTime(const double &time){
    using namespace info;
    
    appTime = time;
    deltaTime = appTime - lastTime;
    lastTime = time;
    
    ogl::appInfoUB->SetUniformValue("uTime", (float)time);
}
void info::updateResolution(const int &width, const int &height){
    using namespace info;

    const float res[2] = {(float)width, (float)height};
    ogl::appInfoUB->SetUniformValue("uResolution", res);

    windowWidth = width;
    windowHeight = height;
    
}