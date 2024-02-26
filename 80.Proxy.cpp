#include <iostream>
#include <memory>

enum class AtmState{
    IDLE, HAS_CARD, NO_CARD, HAS_PIN, NO_CASH
};

std::string CardState[7] = {
    "IDLE", "HAS_CARD", "NO_CARD", "HAS_PIN", "NO_CASH"
};


class AtmMachine : public std::enable_shared_from_this<AtmMachine>{
    private:

    public:
        AtmState atmState;
        double cashInTheMachine;
        AtmMachine() : cashInTheMachine(5000), atmState(AtmState::HAS_CARD) {}

        double getCashFormMachine(){
            return cashInTheMachine;
        }

        std::shared_ptr<AtmMachine> getThisPointer(){
            return shared_from_this();
        }
};

class GetAtmData{
    public:
        virtual AtmState getAtmState() = 0;
        virtual double getCashFormMachine() = 0;
};

class AtmProxy : public GetAtmData{     // proxy class for user to request cash
    private:    
        std::shared_ptr<AtmMachine> atmMachine;
    
    public:
        AtmProxy(std::shared_ptr<AtmMachine> atmMachineTmp) : atmMachine( atmMachineTmp ){}
        AtmState getAtmState() override{
            return atmMachine->atmState;
        }
        double getCashFormMachine() override{
            atmMachine->cashInTheMachine -= 500;
            return atmMachine->cashInTheMachine;
        }
};

int main(){

    std::shared_ptr<AtmMachine> atmMachine = std::make_shared<AtmMachine>();

    // std::cout<< atmMachine->getThisPointer()->cashInTheMachine << std::endl;

    AtmProxy atmProxy(atmMachine);
    std::cout<<atmProxy.getCashFormMachine();

    return 0;
}

