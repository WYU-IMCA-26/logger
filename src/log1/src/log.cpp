#include <iostream>
#include "log1/log.hpp"
#include "log1/admin.h"
// #include "de.hpp"
// #define DEBUG debug
#if DEBUG


#define INFO 1    //信息
#define WARNING 2 //警告
#define ERROR 3   //错误
#define FATAL 4   //致命

std::string SecurityLevel(int security_level){
     switch (security_level)
    {
    case INFO:
        /* code */
        return "INFO";
    case WARNING:
        /* code */
        return "WARNING";
    case ERROR:
        /* code */
        return "ERROR";
    default:
        return "FATAL";
    }
}
#endif