#ifndef SHADERGL_H
#define SHADERGL_H

#include "GL/glew.h"

#include <fstream>
#include <sstream>
#include <unordered_map>

class ShaderGL
{
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    ShaderGL(const char* vertexPath, const char* fragmentPath);
    
    ~ShaderGL();
    

    // activate the shader
    // ------------------------------------------------------------------------
    void Use()      const;
    void Bind()     const;
    void Unbind()   const;


    unsigned int GetID()    const;

    bool IsLinked()         const;

    // MVP
    unsigned int loc_model_matrix;
    unsigned int loc_view_matrix;
    unsigned int loc_projection_matrix;

    // utility uniform functions
    // void SetVec3(const std::string& name, const glm::vec3& value);
    
    // void SetVec3(const std::string& name, float x, float y, float z);
    
    // void SetMat4(const std::string& name, const glm::mat4& mat);
    
    // void SetMat3(const std::string& name, const glm::mat3& mat);

    void SetFloat(const std::string& name, const float& value);

    void SetInt(const std::string& name, const int& value);

    // void SetLight(const Light& val, const std::string& name = "light");

    void SetUniformBlockBinding(const GLchar* asd, const GLuint &Binding);

private:
    void Init(const char* vertexPath, const char* fragmentPath);

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
    
    int GetUniformLocation(const std::string& name);

private:
    unsigned int    m_ID;
    bool            m_linked = false;

    std::unordered_map<std::string, int> uniformLocationCache;
};

#endif