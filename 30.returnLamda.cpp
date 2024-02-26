#include <iostream>

const auto less_than = [](auto x){ // first lamda
    return [x](auto y){ // return the second lamda
        std::cout<<"x: "<<x<<", y: "<<y<<std::endl;
        return x<y;
    };
};

int main(){
    auto less_than_five = less_than(5);

    std::cout<<"True: "<<less_than_five(3);


    return 0;
}