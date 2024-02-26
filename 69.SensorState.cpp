#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <functional>
#include <future>

enum class ThreadState{
    Running, Completed, Errored
};

void run_with_callback( const std::function< void(ThreadState)>& callback){
    std::thread t([callback](){

        try{
            std::this_thread::sleep_for( std::chrono::seconds (2));
            callback( ThreadState::Completed);
        }
        catch(...){
            callback(ThreadState::Errored);
        }   
    });

    // task is running
    callback(ThreadState::Running);
    t.join();
}

int main(){

    std::vector< std::future <ThreadState> > futures;

    auto callBack = [](ThreadState state){
        switch(state){
            case ThreadState::Running :
                std::cout<<"Thread is running"<<std::endl;
                break;
            case ThreadState::Completed :
                std::cout<<"Thread is completed"<<std::endl;
                break;
            case ThreadState::Errored :
                std::cout<<"Error occured"<<std::endl;
                break;
        }
    };

    for(int i=0; i<5; i++){
        decltype( auto ) f = std::async(std::launch::async, run_with_callback, callBack);
    }

    // for(auto& f: futures){
    //     auto state = f.get();
    //     callBack(state);
    // }
}