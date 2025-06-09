#include "shaderplayground.h"
#include "openglstuff.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>
#include <iostream>

char *texturePaths[MAX_TEXTURE_UNITS];

//char *text = new char[512];
char *fragmentShaderPath = new char[255];

void initUI(){
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(info::getWindow(), true);
    ImGui_ImplOpenGL3_Init();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


    //TODO: free memory on exit
    for(int i = 0; i < MAX_TEXTURE_UNITS; ++i){
        texturePaths[i] = new char[256];
        strcpy(texturePaths[i], "");
    }
}


#include "myutils.h"

void UIElements(){
    ImGui::Begin("Textures :D");


    //int i = 0;
    for(int i = 0; i < MAX_TEXTURE_UNITS; i++){
        ImGui::InputText(std::to_string(i).c_str(), texturePaths[i], 255 * sizeof(char), ImGuiInputTextFlags_AllowTabInput);
        ImGui::SameLine();
        if(ImGui::Button((std::string("texture_")+std::to_string(i)).c_str(), ImVec2(72, 24))){
            loadImage(i, texturePaths[i]);
        }
    }
    //TODO:
    //delete text;
    
    ImGui::End();


    ImGui::Begin("shaders :D");
    
    //TODO: Fix the properly null terminated?? assert 
    //gdb -g etc....
    
    ImGui::InputText("path", fragmentShaderPath, 255 * sizeof(char), ImGuiInputTextFlags_AllowTabInput);
    ImGui::SameLine();
    if(ImGui::Button(std::string("load").c_str(), ImVec2(72, 24))){
        loadShader("..\\..\\shaders\\default.vert", fragmentShaderPath);
        std::cout << fragmentShaderPath << std::endl;
        //std::cout << MyUtils::readFile(fragmentShaderPath) << std::endl;


        
    }


    ImGui::End();
}

void showUI(){
     ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        UIElements();

        // ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        auto io = ImGui::GetIO();
        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            // Update and Render additional Platform Windows
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
}
