#ifndef LOG_HPP_
#define LOG_HPP_


#define INFO 1    //信息
#define WARNING 2 //警告
#define ERROR 3   //错误
#define FATAL 4   //致命

// #define WRITE true //写出
// #define OUT true   //输出
#include <iostream>
#include <sstream>
#include <string>

#include "logger.hpp"
#include "admin.h"
// #include "de.hpp"
// #define DEBUG debug
#if DEBUG



// class Logger;

std::string SecurityLevel(int security_level);

template<typename... Args>
void log(int security_level, Args... args)
{
   
    std::stringstream ss;
    (ss <<SecurityLevel(security_level) <<": " <<... << args);
    Logger::instance().log(ss.str(), WRITE, OUT);
}

#else
template<typename... Args>
void log(int security_level, Args... args){
     std::stringstream ss;
    (ss << security_level <<... << args);
    
    }

#endif

#define LOG_INFO(...) log(INFO, __VA_ARGS__)
#define LOG_WARNING(...) log(WARNING, __VA_ARGS__)
#define LOG_ERROR(...) log(ERROR, __VA_ARGS__)
#define LOG_FATAL(...) log(FATAL, __VA_ARGS__)
#endif