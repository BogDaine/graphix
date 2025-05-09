//#define GLEW_STATIC

#include <iostream>
//#include "window.h"
#include "GL/glew.h"
#include "glfw3.h"

float vertexdata[]={
    -0.5f, 0.f, 0.f,
    0.f, -.5f, 0.f,
    .5f, 0.f, 0.f,
    0.f, 0.5f, 0.f,
};
unsigned int indices[]={
    0, 1, 3,
    1, 3, 2,
};

const char *vertexShaderSource = "#version 330 core\n"
 "layout (location = 0) in vec3 aPos;\n"
 "void main()\n"
 "{\n"
 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

GLuint VBO, VAO, EBO;
GLuint shaderProgram, vertexShader, fragmentShader;

void setupBuffers(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW);

    GLsizei stride = 3 * sizeof(float);
    
    int pointer = 0;
    int count = 3;
    //vertex position
    glVertexAttribPointer(0, count, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
    pointer += count * sizeof(float);
    //pentru ca sunt [count] [float]-uri^^
    glEnableVertexAttribArray(0);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //ramane bind-uit la VAO :)
    glBindVertexArray(0);
    //~
    
}

int shaderCompileStatus(GLuint shader){
    GLint success;
    GLchar info[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, info);
        std::cout << info;
    }
    return success;
}
int shaderLinkStatus(){
    GLint success;
    GLchar info[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, info);
        std::cout << info;
    }
    return success;
}

void setupShader(){
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int vshader_ok, fshader_ok;
    vshader_ok = shaderCompileStatus(vertexShader);
    fshader_ok = shaderCompileStatus(fragmentShader);
    if(!(vshader_ok || fshader_ok))
        return;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    shaderLinkStatus();
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void setupOpenGL(){
    glewInit();
    glClearColor(0.5f,0.5f,0.5f, 1.f);
    setupBuffers();
    setupShader();
    //wireframe mode
    glPolygonMode(GL_BACK, GL_LINE);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void drawScene(){
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}

void framebufferSizeCallback(GLFWwindow  __attribute__((__unused__)) * window, int width, int height){
    glViewport(0, 0, width, height);
    //void(window);
}

void windowSizeCallback(GLFWwindow * window, int width, int height){
    //glViewport()
    //void(window);
    //void(width);
    //void(height);
    //framebufferSizeCallback(window, width, height);
}

int main(){
    if (!glfwInit()){
        exit(-1);    
    }

    GLFWwindow *window = glfwCreateWindow(640, 480, "Na că merge drăcia", NULL, NULL);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    //GLINT

    if (!window)
    {
        std::cout << " WINDOW IS NULL!" << std::endl;
    }

    setupOpenGL();

    while (!glfwWindowShouldClose(window)){
        
        

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        drawScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}