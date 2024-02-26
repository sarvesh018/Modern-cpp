#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>
using namespace std;
using namespace std::chrono;

typedef unsigned long long ull ;
using lll = long long ;

ull EvenSum = 0 ;
ull OddSum = 0 ;

void findEven( ull start , ull end )
{
    std::cout<<"Find even thread id: "<<std::this_thread::get_id()<<std::endl;
        
    for( ull i = start ; i <= end ; i++){
        if( i % 2 == 0 ){
            EvenSum += i ;
        }
    }
}

void findODD( ull start , ull end )
{
    std::cout<<"Find odd thread id: "<<std::this_thread::get_id()<<std::endl;
    for( ull i = start ; i <= end ; i++){
        if( i % 2 != 0 ){
            OddSum += i ;
        }
    }
}

int main(){

    ull start = 0, end = 1900000000;
    std::cout<<"Main function thread id: "<<std::this_thread::get_id()<<std::endl;

    auto startTime = high_resolution_clock::now();

    // ------------------------- Async ---------------------
    std::future<void> evenFuture = std::async(std::launch::async, findEven, start, end);
    std::future<void> oddFuture = std::async(std::launch::async, findODD, start, end);

    oddFuture.wait();   // waits for the threads to complete 
    
    cout << " Executed even sum : "<< EvenSum << endl;
    cout << " Executed Odd  sum : "<< OddSum << endl;
    // evenFuture

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    
    cout << " Sec : "<< duration.count()/1000000 << endl;
}
