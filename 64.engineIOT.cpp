#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>
#include <vector>

class Engine{
    public:
        virtual double showData() = 0;
        virtual std::string getName() = 0;
};

class Oil : public Engine{
    public:
        Oil(){
            data = 34.23;
        }
        double showData() override{
            return data;
        }
        std::string getName() override{
            return "OIL IOT";
        }
    private:
        double data;
};

class Petrol : public Engine{
    public:
        Petrol(){
            data = 89.34;
        }
        double showData() override{
            return data;
        }
        std::string getName() override{
            return "PETROL IOT";
        }
    private:
        double data;
};

class Coolent : public Engine{
    public:
        Coolent(){
            data = 74.47;
        }
        double showData() override{
            return data;
        }
        std::string getName() override{
            return "COOLENT IOT";
        }
    private:
        double data;
};



template<typename Func, typename Iterator>
void executeThreads( Func&& func, Iterator begin, Iterator end ){
    // std::vector< std::thread > threads;             
    
    for(auto it = begin; it != end; it++){

        std::lock_guard< std::mutex > lock( std::mutex );
        std::this_thread::sleep_for(std::chrono::seconds(3));  

        std::thread t(std::forward<Func>(func), std::ref(*it));
        std::cout<<t.get_id()<<std::endl;
        t.join();

        // threads.emplace_back(std::forward<Func>(func), std::ref(*it));
    }

    // for(auto& thread : threads){
    //     std::cout<<thread.get_id()<<std::endl;
    //     thread.join();        
    // }
}


void processEngineIOTs(Engine* iot){    
    std::cout<<"\tState Processing"<<std::endl;
    std::cout<<"IOT Processed "<< iot->getName() << " : "<< iot->showData()<<std::endl; 
    std::cout<<"\tState process completed"<<std::endl;    
}


int main(){
    Engine* oil = new Oil;
    Engine* petrol = new Petrol;
    Engine* coolent = new Coolent;
    std::vector<Engine*> iots = {oil, petrol, coolent};

    executeThreads(processEngineIOTs, iots.begin(), iots.end());

    return 0;
}