#include <iostream>
#include <variant>
#include <vector>

using var_t = std::variant<int, const char*>;

template<typename... T>
struct Print : T...{
    using T::operator()...;
};

template<typename... Ts>
auto MakePrint(Ts... ts){
    return Print<Ts...>{ts...};
}

int main(){
    std::cout<<" Lambda Overload \n"<<std::endl;

    std::vector<var_t> vars = {1, 2, "Hello World"};

    auto PrintInt = [](int i){std::cout<< i << std::endl;};
    auto PrintString = [](const char* i){std::cout << i << std::endl;};
    
    for(auto& v: vars){
        std::visit(
            MakePrint(
                [](int i){std::cout<< i << std::endl;},
                [](const char* i){std::cout << i << std::endl;}
            ), v); 
    }


    return 0;
}