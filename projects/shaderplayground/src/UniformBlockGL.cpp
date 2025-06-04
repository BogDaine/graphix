#include "UniformBlockGL.h"
#include <iostream>
#include <cstring>

UniformBlockGL::UniformBlockGL( const std::string &name, const GLuint &binding,
                                const GLuint &uniformCnt, const char** uniformNames):
    m_Name(name),
    m_BindIndex(binding)
{
    for(size_t i = 0; i < uniformCnt; i++){
        m_UniformOffsets.insert(std::make_pair<std::string, GLint>(uniformNames[i], 0));
    }
}


void UniformBlockGL::Init(GLuint shader){
    

    GLuint blockIndex = glGetUniformBlockIndex(shader, m_Name.c_str());
    glGetActiveUniformBlockiv(shader, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &m_Size);

    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ID);

    glBindBufferBase(GL_UNIFORM_BUFFER, m_BindIndex, m_ID);         //just like a texture unit :D
    glBufferData(GL_UNIFORM_BUFFER, m_Size, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    //std::cout << "Uniform buffer "<< m_Name<<" is at index " << blockIndex  << " and is of size "<< m_Size << " bytes" << std::endl;


    size_t i = 0, cnt = m_UniformOffsets.size();
    char **uniformNames = new char*[cnt];
    for(const auto& kv : m_UniformOffsets){
        size_t size = kv.first.size();
        uniformNames[i] = new char[size+1];
        //+1 pentru caracterul nul
        std::memcpy(uniformNames[i++], kv.first.c_str(), size+1);
    }

    GLuint uniformIndices[cnt];
    GLint offsets[cnt];
    glGetUniformIndices(shader, cnt, uniformNames, uniformIndices);
    glGetActiveUniformsiv(shader, cnt, uniformIndices, GL_UNIFORM_OFFSET, offsets);

    for(i = 0; i < cnt; i++){
        //std::cout << uniformNames[i] << " has offset of " << offsets[i] << " bytes" << std::endl;
        m_UniformOffsets[uniformNames[i]] = offsets[i];
    }

    for(i = 0; i < cnt; ++i){
        delete(uniformNames[i]);
    }
    delete uniformNames;
    m_hasInitialized = true;
}



void UniformBlockGL::SetShaderBinding(GLuint shader){
    GLuint index = glGetUniformBlockIndex(shader, m_Name.c_str());
    glUniformBlockBinding(shader, index, m_BindIndex);
}

GLuint UniformBlockGL::GetID()          const{return this->m_ID;        }
std::string UniformBlockGL::GetName()   const{return m_Name;            }
GLuint UniformBlockGL::GetBindIndex()   const{return m_BindIndex;       }
bool UniformBlockGL::HasInitialized()   const{return m_hasInitialized;  }


UniformBlockGL::~UniformBlockGL(){

}