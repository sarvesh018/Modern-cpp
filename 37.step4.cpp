#include <iostream>
#include <variant>
#include <vector>

using var_t = std::variant<int, const char*>;

/*
struct PrintInt{
    void operator()(int i){
        std::cout<< i << std::endl;
    }
}; 

struct PrintString{
    void operator()(const char* str){
        std::cout<< str << std::endl;
    }
};
*/

template<typename... T>
struct Print : T...{
    using T::operator()...;
};

int main(){
    std::cout<<" Lambda Overload \n"<<std::endl;

    std::vector<var_t> vars = {1, 2, "Hello World"};

    auto PrintInt = [](int i){std::cout<< i << std::endl;};
    auto PrintString = [](const char* i){std::cout << i << std::endl;};
    
    for(auto& v: vars){
        std::visit(
            Print<decltype(PrintInt), decltype(PrintString)>
            {PrintInt, PrintString},
            v); 
    }


    return 0;
}