#ifndef MYUTILS_H 
#define MYUTILS_H

#include <string>

typedef struct std::exception;

namespace MyUtils{
    
    typedef double TimeFunctionS();
    typedef unsigned int TimeFunctionMs();

    void executeAfterS(void (*f)(), double delayS);
    void executeAllDelayedFunctions();
    
    void setTimeFunctionS       (TimeFunctionS *f);
    void setDeltaTimeFunctionS  (TimeFunctionS *f);


    class BasicException    :   public std::exception{
        public:
            BasicException(const char *msg): _msg(msg){}
            const char *what()              {return _msg.c_str();}
            ~BasicException()               {}
        
        private:
            std::string _msg;

    };

}

#endif