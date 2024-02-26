#include <iostream>
#include <variant>
#include <functional>
 
class Machine{
    public:
        void on(){
            std::cout<<"Machine is turned on"<<std::endl;
        }
        std::function<void(void)> off = [](){
            std::cout<<"Machine is turned off"<<std::endl;
        };
};
 
int main(){
    using MachineFSM = std::variant<std::function<void(Machine&)>>;
    MachineFSM machinePTR[] = {
        [](Machine& m){m.off();},
        [](Machine& m){m.on();}
    };
 
    Machine fsm;
    int yourOption;
    std::cout<<"0 / 1    : ";
    std::cin>>yourOption;
 
    std::visit(
                [yourOption, &fsm](auto& func){
                    if constexpr(std::is_invocable_v<decltype(func), Machine&>){
                        if( yourOption == 0 || yourOption == 1 ){
                            func(fsm);
                        }
                        else{
                            std::cout<<"Invalid Option"<<std::endl;
                        }
                    }
                    else{
                        std::cout<<"Invalid Function"<<std::endl;
                    }
                }, 
                machinePTR[yourOption]
    );
}
 
 