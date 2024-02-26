#include <iostream>
#include <mutex>
#include <thread>

int myCash = 0;
std::mutex m;

void addMoney(){
    m.lock();
        ++myCash;
    m.unlock();
}

int main(){
    std::thread t1(addMoney);
    std::thread t2(addMoney);

    t1.join();
    t2.join();
}
