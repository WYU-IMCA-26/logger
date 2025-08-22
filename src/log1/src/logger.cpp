
#include <iostream>
#include <ctime>
#include <vector>
#include <string.h>
#include <sstream>
#include <filesystem>


#include "log1/logger.hpp"
// #include "de.hpp"
#include "log1/admin.h"
namespace fs = std::filesystem;
Logger::Logger(){}
Logger::~Logger(){
    shutdown();
}
Logger& Logger::instance(){
    static Logger logger;
    return logger;
}
std::string getCurrentTimestampDay(){
    auto now = std::time(nullptr);//获取时间
    char buf[80];//存储格式化时间的缓冲区
    //格式化时间格式
    std::strftime(buf,sizeof(buf),"%Y-%m-%d",std::localtime(&now));
    return std::string(buf);
}
std::string getCurrentTimestamp(){
    auto now = std::time(nullptr);//获取时间
    char buf[80];//存储格式化时间的缓冲区
    //格式化时间格式
    std::strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",std::localtime(&now));
    return std::string(buf);
}
// #define DEBUG debug
#if DEBUG



void Logger::init( const std::string& logFilePath ){
    fs::path dir = "../loggers/"+getCurrentTimestampDay()+"/";
    if(fs::create_directories(dir)){
        std::cout << "创建日志目录成功：" << dir.c_str()<< std::endl;
    }
    else{
        std::cout << "日志目录已存在：" << dir.c_str()<< std::endl;
    }
    if(m_running){
        return;
    }
    m_logFile.open(dir.c_str()+logFilePath,std::ios::app);
    if(!m_logFile.is_open()){
        std::cerr<<"无法打开："<< dir.c_str()+logFilePath <<std::endl;
        return;
    }
    m_running = true;
    // 创建并启动日志处理线程
    m_logThread = std::thread(&Logger::processLogQueue,this);
}
void Logger::log( const std::string& message,bool write , bool out ){
    this->Write = write;
    this->Out = out;
    if(!m_running){
        return;
    }
    {
        //保护队列
        std::unique_lock<std::mutex> lock(m_queueMutex);
        // 将带时间戳的消息加入队列
        m_logQueue.push(getCurrentTimestamp() + " - " + message);
    }
    // 通知日志处理线程有新消息
    m_cv.notify_one();
}

void Logger::processLogQueue(){
    while (m_running)
    {
        std::string message;
        {
            // 加锁从队列中获取消息
            std::unique_lock<std::mutex> lock(m_queueMutex);
            // 等待有新消息或停止标志
            m_cv.wait(lock,[this]{return !m_logQueue.empty()||!m_running;});
            // 如果停止且队列为空，退出循环
            if(!m_running && m_logQueue.empty()){
                return;
            }
            // 从队列中取出消息
            message = std::move(m_logQueue.front());
            m_logQueue.pop();
        }
        // 写入日志
        
        writeToLog(message);
    }
}

void Logger::writeToLog(const std::string& message){
    if(m_logFile.is_open()&&this->Write){
        m_logFile << message <<std::endl;
        m_logFile.flush();
    }
    if(this->Out){
    std::cout << message <<std::endl;
    //std::cout << "\033[30m"<<  message << "\033[0m " <<std::endl;
    }
}

void Logger::shutdown(){
    if(!m_running){
        return;
    }
    {
        // 加锁修改运行标志
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_running = false;
    }
    // 通知所有等待的线程
    m_cv.notify_all();
    //等待结束
    if(m_logThread.joinable()){
        m_logThread.join();
    }
    //关闭
    if(m_logFile.is_open()){
        m_logFile.close();
    }
}
// template<typename... Args>
// void log_(Args... args,bool write, bool out)
// {
    // stringstream ss;
    // (ss << args);
    // Logger::instance().log(ss.str());
//}
#else
void Logger::processLogQueue(){
    while (m_running){}//空实现
}
void Logger::init( const std::string& logFilePath ){
    string s = logFilePath;
}
void Logger::shutdown(){}
#endif
