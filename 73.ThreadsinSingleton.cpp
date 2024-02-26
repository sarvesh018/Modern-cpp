#include <iostream>
#include <mutex>

class Singleton{
    public:
        static Singleton& getInstance(){    // use std::reference_wrapper
            std::call_once(flag_, [](){std::cout<<"At getinstance()"<<std::endl; instance_ = new Singleton;});
            return *instance_;
        }

    private:
        Singleton (){}
        static Singleton* instance_;    // use unique_ptr
        static std::once_flag flag_;
};

Singleton* Singleton::instance_ = nullptr;
std::once_flag Singleton::flag_;

int main(){
    Singleton& s1 = s1.getInstance();
    Singleton& s2 = s1.getInstance();
    Singleton& s3 = s1.getInstance();

    if(&s1 == &s2){
        std::cout<<"Singleton Works"<<std::endl;
    }
}