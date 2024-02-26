#include <iostream>
using namespace std;

enum class CarType{ Mercedes, Ferrari};

class Engine{
    public:
        Engine() = default;
        virtual void start() = 0;
};

class AmgEngine : public Engine{
    void start() override{
        cout<<"Amg Engine Started"<<endl;
    }
};

class FerrariEngine : public Engine{
    void start() override{
        cout<<"Ferrari Engine Started"<<endl;
    }
};
 
class SeriveProviderFactory{
    private:
        Engine* engine;

    public:
        Engine* getEngine(CarType carType){
            if(carType == CarType::Mercedes){
                engine = new AmgEngine;
            }
            else if(carType == CarType::Ferrari){
                engine = new FerrariEngine;
            }
            else{
                cout<<"Requested engine not found"<<endl;
                return nullptr;
            }
            return engine;
        }
};

class Car{
    private:
    public:
    Car(){
        cout<<"Base Car Created"<<endl;
    }
    Engine* engine;
    virtual void start(Engine* e) = 0;
};
class AmgCar : public Car{
    public:
        void start(Engine* engine) override{
            cout<<"Mercedes car started"<<endl;
            this->engine = engine;
            engine->start();
        }
};
class FerrariCar : public Car{
    public:
        void start(Engine* engine) override{
            cout<<"Ferrari car started"<<endl;
            this->engine = engine;
            engine->start();
        }
};


int main(){
    cout<<"Engine Provider"<<endl;
    SeriveProviderFactory* provider = new SeriveProviderFactory;
    Engine* engine = provider->getEngine(CarType::Ferrari);

    FerrariCar car;
    car.start(engine);


    return 0;
}