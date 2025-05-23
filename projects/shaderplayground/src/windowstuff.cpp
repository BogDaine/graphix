#include "shaderplayground.h"
#include "glfw3.h"

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
        
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSwapInterval(1);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //exit(2);
}

void mainLoop(){
    while(!glfwWindowShouldClose(window)){

        info::updateTime(glfwGetTime());
        drawScene();

        //updateUniforms();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}