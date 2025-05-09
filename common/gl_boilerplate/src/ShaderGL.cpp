#include "ShaderGL.h"

#include <iostream>

ShaderGL::ShaderGL(const char* vertexPath, const char* fragmentPath)
{
    Init(vertexPath, fragmentPath);
}

ShaderGL::~ShaderGL()
{
    glDeleteProgram(m_ID);
}

void ShaderGL::Use() const
{
    glUseProgram(m_ID);
}


void ShaderGL::Bind() const
{
    glUseProgram(m_ID);
}

void ShaderGL::Unbind() const
{
    glUseProgram(0);
}


unsigned int ShaderGL::GetID() const
{
    return m_ID;
}

// void ShaderGL::SetVec3(const std::string& name, const glm::vec3& value)
// {
//     Use();
//     auto location = GetUniformLocation(name);
//     glUniform3fv(location, 1, &value[0]);
// }

// void ShaderGL::SetVec3(const std::string& name, float x, float y, float z)
// {
//     Use();
//     int location = GetUniformLocation(name);
//     glUniform3f(location, x, y, z);
// }

// void ShaderGL::SetMat4(const std::string& name, const glm::mat4& mat)
// {
//     Use();
//     int location = GetUniformLocation(name);
//     glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
// }

// void ShaderGL::SetMat3(const std::string& name, const glm::mat3& val)
// {
//     Bind();
//     int location = GetUniformLocation(name);
//     GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(val)));
// }


void ShaderGL::SetFloat(const std::string& name, const float& value)
{
    Use();
    int location = GetUniformLocation(name);
    glUniform1f(location, value);
}

void ShaderGL::SetInt(const std::string& name, const int& value)
{
    Use();
    int location = GetUniformLocation(name);
    glUniform1i(location, value);
}

// void ShaderGL::SetLight(const Light& val, const std::string& name)
// {
//     Bind();
//     int location = GetUniformLocation(name + ".position");
//     GLCall(glUniform3f(location, val.position.x, val.position.y, val.position.z));

//     location = GetUniformLocation(name + ".ambient");
//     GLCall(glUniform3f(location, val.ambient.x, val.ambient.y, val.ambient.z));

//     location = GetUniformLocation(name + ".diffuse");
//     GLCall(glUniform3f(location, val.diffuse.x, val.diffuse.y, val.diffuse.z));

//     location = GetUniformLocation(name + ".specular");
//     GLCall(glUniform3f(location, val.specular.x, val.specular.y, val.specular.z));
// }

void ShaderGL::Init(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    // shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    CheckCompileErrors(m_ID, "PROGRAM");

    // 3. delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void ShaderGL::CheckCompileErrors(unsigned int shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

int ShaderGL::GetUniformLocation(const std::string& name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    //GLCall(unsigned int location = glGetUniformLocation(ID, name.c_str()));
    unsigned int location = glGetUniformLocation(m_ID, name.c_str());
    //ASSERT(location != -1);
    //if (location == -1)
    //{
    //    std::cout << "[WARNING]:" << " UNIFORM <" << name << "> does not exist" << std::endl;
    //}
    return uniformLocationCache[name] = location;
    //return location;
}
