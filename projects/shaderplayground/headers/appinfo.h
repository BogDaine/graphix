#ifndef APP_INFO_H
#define APP_INFO_H

#define WINDOW_TITLE            "Shader Playground :D"

#define DEFAULT_WINDOW_WIDTH    800
#define DEFAULT_WINDOW_HEIGHT   600

typedef struct GLFWwindow GLFWwindow;

namespace info{
    extern int windowWidth;
    extern int windowHeight; 

    void init();

    void updateTime(const double &time);
    void updateResolution(const int &width, const int &height);

    double getTime();
    double getDeltaTime();

    GLFWwindow *getWindow();
    void setWindow(GLFWwindow *w);

    void setShaderPath(const char*);
    const char *getShaderPath();
}


#endif