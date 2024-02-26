#include <iostream>
#include <thread>
#include <vector>

int main(){
    int a = 10, b = 20, c = 30;
    std::vector<int*> vecPtr = {&a, &b, &c};
    for(auto ptr : vecPtr){
        *ptr += 5;
    }

    for(auto ptr : vecPtr){
        std::cout<< *ptr << " ";
    }

    std::cout<<std::endl;
    // using reference wrapper
    std::vector<std::reference_wrapper<int>> vecPtr2 = {a, b, c};
    for(auto ptr : vecPtr2){
        std::cout<< ptr.get() << " ";
    }

    // int a = 20;
    // int *b = &a;

    // std::cout<<*b;

}