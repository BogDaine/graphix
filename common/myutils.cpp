#include "myutils.h"

#include <list>
#include <iostream>

#include <exception>

typedef struct DelayedFunction{
    void (*f)()         = nullptr;
    //double timeCalled   = 0;
    double delay        = 0;
};

static std::list<DelayedFunction> functionsToExecute = {};

static MyUtils::TimeFunctionS *timeFuncS        = nullptr;
static MyUtils::TimeFunctionS *deltaTimeFuncS   = nullptr;

static MyUtils::TimeFunctionMs *timeFuncMs      = nullptr;

void MyUtils::executeAfterS(void (*x)(), double delayS){

    functionsToExecute.push_back({x, delayS});
}

void MyUtils::executeAllDelayedFunctions(){
    try{
        if(deltaTimeFuncS == nullptr)
        {
            BasicException e("EXCEPTION: deltaTimeFuncS is null\n");

            throw e;
        }
    }
    catch(BasicException e){
        std::cout << e.what();
        //exit(0);
        return;
    }
    double deltaTime = deltaTimeFuncS();

    for (std::list<DelayedFunction>::iterator it = functionsToExecute.begin(); it != functionsToExecute.end();){
        it->delay -= deltaTime;
        if(it->delay <= 0){
            it->f();
            it = functionsToExecute.erase(it);
        }
        else ++it;
    }

}

void MyUtils::setDeltaTimeFunctionS(TimeFunctionS *f){
    deltaTimeFuncS = f;
}
void MyUtils::setTimeFunctionS(TimeFunctionS *f){

}


#include <fstream>
#include <sstream>

std::string MyUtils::readFile(const char *path){
        std::ifstream file;
    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path, std::ifstream::binary);
        std::stringstream filestream;
        filestream << file.rdbuf();
        file.close();
        std::string fileContents = filestream.str();
        //std::cout << fileContents << std::endl;
        return fileContents;
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::BULLSHIT ERROR:: FUCK YOU :D" << std::endl;
        std::cout << e.what();
        //return;
    }
    return std::string();
}