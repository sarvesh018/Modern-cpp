 // & will take reference from above
 // = global capture
 // [&, age, id]


// higher order function will be goes with parellel execution
// lambdas are constant functions

#include <iostream>

auto makeMeAdeveloper(const std::string& name){
    // returning function pointer using lambda expression
    int age = 21;
    int id = 9;
    return [&]() mutable {
        id += 10;
        std::cout<<"My name is: "<<name<<", "<<id<<std::endl;
    };
}

int main(){
    int x{10};
    auto sayName{ makeMeAdeveloper("Sarvesh")};

    sayName();
}