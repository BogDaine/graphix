#include "shaderplayground.h"
#include "input.h"

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
        
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSwapInterval(1);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //exit(2);
}

void mainLoop(){
    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        info::updateTime(glfwGetTime());

        drawScene();


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //updateUniforms();

        //if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            // Update and Render additional Platform Windows
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            // TODO for OpenGL: restore current GL context.
        }
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);


    }
}