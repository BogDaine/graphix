#include "shaderplayground.h"
#include "openglstuff.h"
#include "appinfo.h"
#include "input.h"

#include "myutils.h"

#include <iostream>
#include <vector>
#include <imgui.h>
#include <glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


ShaderGL *current_shader = nullptr;
UniformBlockGL *UB = nullptr;
UniformBlockGL *appInfoUB = nullptr;

float rectangleVertices[] ={
	// Coords       // texCoords
	-1.0, -1.0, 0.0,    0.0, 0.0,
    1.0, 1.0, 0.0,      1.0, 1.0,
    -1.0, 1.0, 0.0,     0.0, 1.0,
    1.0, -1.0, 0.0,     1.0, 0.0,
    
};
unsigned int rectangleIndices[] ={
    0, 1, 2,
    0, 3, 1,
};

struct vec4{
    float x = 0, y = 0, z = 0, t = 0;
};


GLuint VBO, VAO, EBO;

void setupBuffers(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

    GLsizei stride = 3 * sizeof(float) + 2 * sizeof(float);
    
    //vertex position
    int pointer = 0;
    int count = 3;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, count, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
    pointer += count * sizeof(float);
    //pentru ca sunt [count] [float]-uri^^

    //texture coordinates
    count = 2;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, count, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
    pointer += count * sizeof(float);
    //pentru ca sunt [count] [float]-uri^^

    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //ramane bind-uit la VAO :)
    glBindVertexArray(0);
    //~
    
}


void drawScene(){
    ogl::appShader->Bind();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(rectangleIndices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void init(){
    createWindow();
    ogl::init();
    initUI();
    
    info::init();
    MyUtils::setDeltaTimeFunctionS(info::getDeltaTime);

    setupBuffers();

    stbi_set_flip_vertically_on_load(true);
}


void loadImage(unsigned int textureUnit, const char *path){
    
	//fileName = path.substr(path.find_last_of('/') + 1);
	unsigned char *data = NULL;
    int width, height, channels;
	data = stbi_load(path, &width, &height, &channels, 0);
    
    if(!data){
        return;
    }

    GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

    ogl::setTextureData(textureUnit, width, height, data, format);
    free(data);
}

void loadShader(const char *vertexPath, const char *fragmentPath){
    auto vertexSrc = MyUtils::readFile(vertexPath);//.c_str();
    auto fragmentSrc = MyUtils::readFile(fragmentPath);//.c_str();
    std::cout << vertexSrc << std::endl;
    std::cout << fragmentSrc << std::endl;
    auto newShader = new ShaderGL(vertexSrc.c_str(), fragmentSrc.c_str());
    ogl::setAppShader(newShader);
}

int main(){
    
    init();

    // loadImage(0, "textures\\rainbow_cat.jpg");
    loadImage(0, "textures\\Masha.jpg");
    mainLoop();
    return 0;
}