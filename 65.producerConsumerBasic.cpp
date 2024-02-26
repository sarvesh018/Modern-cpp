#include <iostream>
#include <cstdlib>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>
#include <vector>

std::mutex g_mutex;
bool g_ready = false;
int g_data = 0;

int produceData(){
    int randomNumber = rand() % 1000;
    std::cout << "produce data: " << randomNumber << "\n";
    return randomNumber;
}

void consumeData(int data) {
    std::cout << "recieve data: "<< data << std::endl;
}

void consumer(){
    while(true){
        while(!g_ready){
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        std::unique_lock<std::mutex> ul ( g_mutex );
        consumeData( g_data );
        g_ready = false;
    }
}

void producer(){
    while(true){
        std::unique_lock<std::mutex> ul (g_mutex);
        g_data = produceData();
        g_ready = true;
        ul.unlock();  

        while(g_ready){
            // sleep for a second
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void consumerThread() { consumer(); }
void producerThread() { producer(); }

int main(){

    std::thread t1(consumerThread);
    std::thread t2(producerThread); 

    t1.join();
    t2.join();   

}