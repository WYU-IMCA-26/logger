#include <iostream>
#include <queue>
#include <thread>
#include <fstream>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string>
#include <sstream>
using namespace std;
#define WRITE true
#define NO_WRITE false
#define OUT true
#define NO_OUT false
class Logger{
    public:
    //获取单例实例
    static Logger& instance();
    //禁用拷贝构造和赋值运算符，单例特性
    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;
    //初始化
    void init(const std::string& logFilePath = "logger.log");
    //写入
    void log(bool write = NO_WRITE, bool out = OUT, const std::string& message);
    //关闭
    void shutdown();
    
    private:
    Logger();
    ~Logger();
    //主
    void processLogQueue();
    //写入文件和标准输出
    void writeToLog(const std::string & message);

    bool Write = false;//是否写入文件 默认不写入
    bool Out = true;//是否输出 默认输出
    std::queue<std::string> m_logQueue;//存储队列
    std::mutex m_queueMutex;//互斥锁，保护
    std::condition_variable m_cv;//线程间通信的条件变量
    std::thread m_logThread;//后台线程处理
    std::ofstream m_logFile;//日志文件流
    std::atomic<bool> m_running{false};//指示日志库是否运行的原子标志
    std::string message;//日志消息
};

std::string getCurrentTimestamp();
template<typename... Args>
void log_(bool write = NO_WRITE, bool out = OUT, Args... args);
