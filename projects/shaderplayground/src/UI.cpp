#include "shaderplayground.h"
#include "openglstuff.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

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

}

char *text = new char[512];
char *fragmentShaderPath = new char[512];
void UIElements(){
    ImGui::Begin("Hello, world!");


    //for(int i = 0; i < MAX_TEXTURE_UNITS; i++){
    int i = 0;
        ImGui::InputText("text", text, 512 * sizeof(char), ImGuiInputTextFlags_AllowTabInput);
        ImGui::SameLine();
        if(ImGui::Button((std::string("texture_")+std::to_string(i)).c_str(), ImVec2(72, 24))){
            loadImage(i, text);
        }
    //}
    //delete text;
    
    ImGui::End();


    ImGui::Begin("shaders :D");
    
    ImGui::InputText("path", fragmentShaderPath, 512 * sizeof(char), ImGuiInputTextFlags_AllowTabInput);
    ImGui::SameLine();
    if(ImGui::Button(std::string("load").c_str(), ImVec2(72, 24))){
        loadShader("..\\..\\shaders\\default_vert.shader", fragmentShaderPath);
    }


    ImGui::End();
}

void showUI(){
     ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        UIElements();

        //ImGui::ShowDemoWindow();
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
