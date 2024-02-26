#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <functional>
#include <future>

void execute( const std::function< void()>& callback){
    std::thread t(callback);
    t.join();
    
}

int main(){
    std::vector<int> numbers = {19, 32, 56, 15, 20};

    auto callBack = [&numbers](){
        for(auto num : numbers){
            (num%2 == 0) ? std::cout<<"Even"<<std::endl : std::cout<<"Odd"<<std::endl;
        }
    };

    for(int i=0; i<5; i++){
        std::future<void> futures = std::async(std::launch::async, execute, callBack);
    }
}
