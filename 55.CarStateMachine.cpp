#include <bits/stdc++.h>
#include <iostream>
#include <variant>
#include <functional>
 
//----------------------------------Visitor-----------------------------------
 
class VisitorController{
    public:
        float fuel;
        int8_t int8_t_battery;
    
        VisitorController() = default;
        VisitorController(float f, int8_t b) : fuel(f), int8_t_battery(b){}
 
        using IOT = std::variant<float, int8_t>;
        std::vector<IOT> check = {fuel, int8_t_battery};
 
        bool checkFuel(){
            bool flag = false;
            std::visit(
                [&](auto& fuel){
                    fuel-=10;
                    if(fuel > 15){
                        flag = true;
                    }
                }, check[0]
            );
            return flag;
        }
 
        bool checkBattery(){
            bool flag = false;
            std::visit(
                [&](auto& battery){
                    battery--;
                    if(battery > 50){
                        flag = true;
                    }
                }, check[1]
            );
            return flag;
        }
 
        float getFuel(){
            return fuel;
        }
        int8_t getBattery(){
            return int8_t_battery;
        }
};
 
 
// ------------------------ Abstraction Layer CarState ----------------------
 
class CarState{
    public:
        virtual void startCar() = 0;
        virtual void stopCar() = 0;
        virtual void accelarate() = 0;
        virtual void applyBreak() = 0;
};
 
 
// ------------------------- Concrete CAR Class ------------------------------------
 
class Car{
    
    CarState* carState;
    std::shared_ptr<VisitorController> vc;
    
    public:
        Car(std::shared_ptr<VisitorController> vc);
 
        void setCarState(CarState* state);
 
        void startCar(){
            carState -> startCar();
        }
        void stopCar(){
            carState -> stopCar();
        }
        void accelarate(){
            carState -> accelarate();
        }
        void applyBreak(){
            carState -> applyBreak();
        }
        bool checkFuel(){
            return vc->checkFuel();
        }
        bool checkBattery(){
            return vc->checkBattery();
        }
        float getFuel(){
            return vc->getFuel();
        }
        int getBattery(){
            return vc->getBattery();
        }
};
 
// ------------------------States-------------------------
 
// TURNOFF STATE
class TurnOff : public CarState{
    
    Car* newState;
 
    public:
        TurnOff(Car *currentState){
            newState = currentState;
            std::cout<<"Car is in turnoff state"<<std::endl;
        }
        ~TurnOff(){}
 
        void startCar();
        void stopCar() override{
            std::cout<<"Car is not moving"<<std::endl;
        }
        void accelarate() override{
            std::cout<<"First turn on the car"<<std::endl;
        }
        void applyBreak() override{
            std::cout<<"Car is not moving"<<std::endl;
        }
};
 
// TURNON STATE
class TurnOn : public CarState{
 
    Car* newState;
    
    public:
        TurnOn(Car *currentState){
            newState = currentState;
            std::cout<<"Car Started !!"<<std::endl;
            std::cout<<"Fuel: "<<newState->getFuel()<<std::endl;
            std::cout<<"Battery: "<<newState->getBattery()<<" %"<<std::endl;
        }
 
        void startCar() override{
            std::cout<<"Car is already started"<<std::endl;
        }
        void stopCar();
        void accelarate();
        void applyBreak() ;
};
 
// RUNNING STATE
class Running : public CarState{
 
    Car* newState;
    
    public:
        Running(Car *currentState){
            newState = currentState;
            std::cout<<"Car is running"<<std::endl;
        }
 
        void startCar() override{
            std::cout<<"Car is already started"<<std::endl;
        }
        void stopCar();
        void accelarate();
        void applyBreak();
};
 
// STOP STATE
class Stop : public CarState{
 
    Car* newState;
    
    public:
        Stop(Car *currentState){
            newState = currentState;
            std::cout<<"Car stopped!"<<std::endl;
        }
 
        void startCar() override{
            std::cout<<"Car is already started"<<std::endl;
        }
        void stopCar() override{
            std::cout<<"Car is not moving"<<std::endl;
        }
        void accelarate();
        void applyBreak() override{
            std::cout<<"Car is not moving"<<std::endl;
        }
};
 
// ------TURNOFF------
void TurnOff::startCar() {
    if(newState->checkBattery()){
        newState -> setCarState(new TurnOn(newState));
    }
    else{
        std::cout<<"Battery is low"<<std::endl;
    }
}
 
 
// --------TURNON-------
void TurnOn::stopCar()
{
    newState -> setCarState(new TurnOff(newState));
}
void TurnOn::accelarate(){
    if(newState->checkFuel()){
        newState -> setCarState(new Running(newState));
    }
    else{
        std::cout<<"You are running out of fuel"<<std::endl;
    }
}
void TurnOn::applyBreak() {
    newState -> setCarState(new Stop(newState));
}
 
 
// ----RUNNING------
void Running::stopCar() {
    newState -> setCarState(new TurnOff(newState));
}
void Running::accelarate() {
    if(newState->checkFuel()){
        newState -> setCarState(new Running(newState));
    }
    else{
        std::cout<<"You are running out of fuel "<<std::endl;
    }
}
void Running::applyBreak() {
    newState -> setCarState(new Stop(newState));
}
 
 
//------STOP-------
void Stop::accelarate(){
    if(newState->checkFuel()){
        newState -> setCarState(new Running(newState));
    }
    else{
        std::cout<<"You are running out of fuel"<<std::endl;
    }
}
 
 
//-----CAR----
Car::Car(std::shared_ptr<VisitorController> vc){
    this->vc = vc;
    carState = new TurnOff(this);
}
 
void Car::setCarState(CarState* state){
    carState = state;
}
 
 
 
// -----------------------MAIN---------------------
 
int main(){
    std::shared_ptr<VisitorController> vc = std::make_shared<VisitorController>(40.0f, 100);
    std::unique_ptr<Car> car = std::make_unique<Car>(vc);
 
    car->startCar();
    car->accelarate();
    car->accelarate();
    car->applyBreak();
    car->accelarate();
    car->stopCar();
 
}
