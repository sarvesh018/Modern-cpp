#include <iostream>

template<typename State>
struct TransactionTo{
    template<typename Machine>
    void execute( Machine& machine){
        machine.template transactionTo<State>();
    }
};

struct machine{
    template<typename State>
    void transactionTo(){
        std::cout<<"In transaction with state: "<< typeid(State).name() << std::endl;
    }
};

struct MyState{};
struct YourState{};

int main(){
    machine machine;
    TransactionTo< YourState > transaction;
    transaction.execute(machine);
}