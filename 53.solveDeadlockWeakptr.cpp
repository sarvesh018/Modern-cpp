#include <iostream>
#include <memory>

// weak pointer
std::weak_ptr<int> gw;

void observe(){
    std::cout<<"gw.useCount() = "<<gw.use_count()<<std::endl;

    if(std::shared_ptr<int> spt = gw.lock()){
        std::cout<<"*spt = "<<*spt<<std::endl;
    }
    else{
        std::cout<<"gw is expired"<<std::endl;
    }
}

int main(){
    {
        // sp is created locally

        auto sp = std::make_shared<int>(42); // use count will be one
        gw = sp;
        observe();

        // sp is destroyed
    }

    observe();
}