#include "shaderplayground.h"
#include "input.h"

#include "myutils.h"

// #define IMGUI_IMPL_OPENGL_LOADER_CUSTOM


#include <glfw3.h>

#include <iostream>


static GLFWwindow* window;

void framebufferSizeCallback(GLFWwindow  __attribute__((__unused__)) * window, int width, int height){
    glViewport(0, 0, width, height);
    info::updateResolution(width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos){
    input::updateMousePos(xpos, ypos);
    //std::cout << "mouse pos: x = " << xpos << ", y = " << ypos << std::endl;
}

void initWindow(){
    if(!glfwInit()){
        std::cout << "NOT glfwinit!" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

}



void createWindow(){
    initWindow();
    window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
        WINDOW_TITLE, NULL, NULL);
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetCursorPosCallback(window, mouseCallback);
        
        info::setWindow(window);

        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        //TODO: TICK RATE!
        glfwSwapInterval(1);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //exit(2);
}

void mainLoop(){
    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        info::updateTime(glfwGetTime());

        MyUtils::executeAllDelayedFunctions();

        drawScene();

        showUI();
       
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);


    }
}