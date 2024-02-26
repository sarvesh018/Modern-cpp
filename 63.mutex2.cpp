#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>

template<typename Func, typename Iterator>
void executeThreads( Func&& func, Iterator begin, Iterator end ){
    std::vector< std::thread > threads;             // kind of a thread poll
    
    for(auto it = begin; it != end; it++){
        std::lock_guard< std::mutex > lock( std::mutex );
        std::this_thread::sleep_for(std::chrono::seconds(3));  // blocks thread for 3 seconds

        //                        function              parameters        <------ thread              
        threads.emplace_back(std::forward<Func>(func), std::ref(*it));
    }

    for(auto& thread : threads){
        std::cout<<thread.get_id()<<std::endl;
        thread.join();          // joining threads for complete execution
    }
}

// this function is thread as well as callback
void processEngineIOTs(int& value){
    std::string iot[5] = {"Oil IOT", "Petrol IOT", "Piston IOT", "Cumbersion", "Coolent"};
    
    std::cout<<"\tState Processing"<<std::endl;
    std::cout<<"IOT Processed "<<iot[value]<<std::endl; 
    std::cout<<"\tState process completed"<<std::endl;    
}



int main(){
    std::vector<int> values = {1, 2, 3, 4, 5};

    executeThreads(processEngineIOTs, values.begin(), values.end());

    return 0;
}