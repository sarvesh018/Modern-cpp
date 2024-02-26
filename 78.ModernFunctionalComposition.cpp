#include <iostream>
#include <functional>
#include <tuple>

int add(int a, int b){
    return a+b;
}

float multiply(float a, int b){
    return a*b;
}

std::string concatenate(const std::string& s1, const std::string& s2){
    return s1 + s2;
}


template<typename... Funcs, typename... Args>
void printResult(const std::tuple<std::function<Funcs>...>& tuple, Args&&... args){
    auto invokeFunction = [&](auto&& func){

        using FunctionType = std::decay_t<decltype(func)>;
        
        if constexpr (std::is_invocable_v<FunctionType>){
            std::cout<<"Result: "<< func() << std::endl;
        }
        else{
            std::cout<<"Error: Invalid function"<<std::endl;
        }
    };

    std::apply([&](auto&&... funcs){
        (invokeFunction(funcs), ...);
    }, tuple);
}


int main(){
    std::tuple<std::function<int()>, std::function<float()>, std::function<std::string()>> funcTuple(
        [](){ return add(3, 4); },
        [](){ return multiply(5, 3.3); },
        [](){ return concatenate("Hello", "World"); }
    );

    printResult(funcTuple);
}