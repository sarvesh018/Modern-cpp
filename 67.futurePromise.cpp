#include <iostream>
#include <cstdlib>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>

void threadFun(std::promise<int>& prom){
    std::this_thread::sleep_for(std::chrono::seconds( 3 ));
    prom.set_value( 894 ); // rValue
}

int main(){
    std::promise<int> myPromise;
    std::future<int> handleToFuture = myPromise.get_future();

    std::cout<<"Fire the thread"<<std::endl;

    std::thread t1{threadFun, std::ref(myPromise)};

    std::cout<<"In main thread "<<handleToFuture.get()<<std::endl;

    t1.join();
}