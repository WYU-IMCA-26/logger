#include "log1/logger.hpp"
#include "log1/log.hpp"
#include <thread>
#include <vector>
#include <string.h> 
#include "log1/admin.h"
// #include "de.hpp"
void workerThread(int id){
    for(int i = 0; i<1000; i++){
        LOG_INFO("hello ", id," ", i,"a a");
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
