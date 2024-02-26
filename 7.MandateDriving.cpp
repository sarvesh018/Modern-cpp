#include <iostream>
using namespace std;
// first take pass and fail cases than write code 
// rules for engine to run, 

// checking for minimum required fuel
template <float fuel> 
float pump(float additionalOil) requires(fuel>10.0f){
    float minimumFuel = 20.0f;
    if(fuel + additionalOil < minimumFuel){
        throw std::runtime_error("Car can stop any minute!!");
    }
    return fuel + additionalOil;
}

template <typename T>
concept MandateDriving = requires(T t){ // concept or predicate can also be used
    {t.accelerator()};
    {t.applyBreak()};
    {t.fuel};
 
    // requires is hardcoded condition
    requires std::is_same_v<decltype(t.fuel), float>;

    // checking for minimum fuel
    {pump<11.0f>(t.fuel)};
    // {pump<static_cast<float>(t.fuel)>(t.fuel)};
};

// avoid using float it is heavy, instead use double

class Engine{
    public:
        void accelerator(){
            std::cout<<"Pump the accelerator"<<std::endl;
        }
        void applyBreak(){
            std::cout<<"Apply the breaks"<<std::endl;
        }
        // so its not declared at concept MandateWhileDriving = requires
        void notRelatedToEngine(){
            std::cout<<"This fun not related to engine..."<<std::endl;
        }
        float fuel = 20.0f;
};

class Car{
    public:
    template<MandateDriving T>
    void drive(T arg){
        arg.accelerator();
        arg.applyBreak();
    }
};

int main(){
    
    try{
        Engine e;
        Car c;
        c.drive(e);
    }
    catch(const std::runtime_error(& e)){
        cout<<"Exception : "<<e.what()<<endl;
    }
    cout<<"End of the code "<<endl;
    return 0;
}