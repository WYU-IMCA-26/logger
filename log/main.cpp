#include "logger.hpp"
#include <thread>
#include <vector>
#include <string.h> 
void workerThread(int id){
    for(int i = 0; i<1000; i++){
        log(std::to_string(id) + "hello" + std::to_string(i));
    }
}
int main(){
    Logger::instance().init("logger.log");
    std::vector<std::thread> threads;
    for(int i = 0; i<5; i++){
        threads.emplace_back(workerThread, i);
    }
    for(auto& t :threads){
        t.join();
    }
    Logger::instance().shutdown();
    return 0;
}
