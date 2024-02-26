//
//  main.cpp
//  Threads
//
//  Created by Sathya Babu on 14/02/24.
//


/*
   Class :
      
      A  B  C  D
 
      Abstraction..( Virtual functions )
 
      Concider threads.. as a wrapper
      Threading / Class( M V C  ) Arch..
      State MAchine..  / Embeded Timing diagrams..
      Observers..
 
      Exceptions..
 
      Thread's  :     processor - Cores..  ( No of threads can be executed ) Hz
       Stack..
 
       Call back (    )
 
                A
       B                  C
 
                D
 
 
      Co routines..
       on one socket it can dispatch numerous threads 100,000
 
           std::async();
 
      Thread pool(    )
           
      local class
      
       
 
 
 
 */
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

typedef  float  f;

f f1=10.12f;



ull EvenSum = 0 ;

ull OddSum = 0 ;

void findEven( ull start , ull end )
{
    for( ull i = start ; i <= end ; i++){
        if( i % 2 ){
            EvenSum += i ;
        }
    }
}


void findODD( ull start , ull end )
{
    for( ull i = start ; i <= end ; i++){
        if( !(i % 2) ){
            OddSum += i ;
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Threads..!\n";
    
    std::cout << "Just about t hreads...!\n";
       
    ull start = 0 , end =  1900000000;
    auto startTime = high_resolution_clock::now();

    std::thread t1 ( findEven,start,end );
    std::thread t2 ( findODD,start,end );
    
    // Blocking threads..
    t1.join();
    t2.join();

    cout << " Lets Watch the happenings here.....!!!!"<<  endl;
      
      
      auto stopTime = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stopTime - startTime);
      
      cout << " Executed even sum : "<<  EvenSum<<endl;
      cout << " Executed Odd  sum : "<< OddSum<< endl;
      
      cout << " Sec : "<< duration.count()/1000000 << endl;
      
    return 0;
}
