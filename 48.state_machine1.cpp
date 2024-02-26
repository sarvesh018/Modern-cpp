#include <iostream>
#include <functional>
// class Machine{
//     public:
//         void on(){
//             std::cout<<"Machine is turned on"<<std::endl;
//         }
//         void off(){
//             std::cout<<"Machine is turned off"<<std::endl;
//         }
// };

// int main(){
//     void(Machine::*machinePTR[])() = {
//         &Machine::off, &Machine::on
//     };

//     Machine fsm; // finite state machine
//     int yourOption;
//     std::cout<<"0/1 : ";
//     std::cin>>yourOption;

//     (fsm.*machinePTR[ yourOption ])();
// }

class Machine{
    public:
        static void on(){
            std::cout<<"Machine is turned on"<<std::endl;
        }
        static void off(){
            std::cout<<"Machine is turned off"<<std::endl;
        }
};

int main(){
    Machine fsm;
    std::function<void()> machinePTR[] = {Machine::off, Machine::on};

     // finite state machine
    int yourOption;
    std::cout<<"0/1 : ";
    std::cin>>yourOption;

    machinePTR[ yourOption ]();
}
