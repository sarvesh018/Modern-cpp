#include <iostream>
#include <cstdlib>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>
#include <vector>

void extractedDelay(){
    for(int i=0; i<80000; i++){
        for(int j=0; j<80000; j++){

        }
    }
}

int main(){
    // we use std::packaged_task which can be used to wrap the target that called as a async calls
    
    // it is a wrapper
    std::packaged_task<int()> task ( [](){
        std::this_thread::sleep_for(std::chrono::seconds( 3 ));
        return 3;
    });

    std::future< int > result = task.get_future();

    std::thread( std::move(task) ).detach();

    std::cout<<"Waiting..."<<std::endl;

    result.wait();
    std::cout<<"Done! \n"<<"Future result is "<<result.get()<<std::endl;
}