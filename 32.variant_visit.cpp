#include <iostream>
#include <vector>
#include <typeinfo>
#include <variant>

int main(){
    std::vector<std::variant<char, long, float, int, double, long long>> 
    vecVariant = {5, '2', 5.4, 101l, 2311l, 3.5f, 2017};

    for(auto& v: vecVariant){
        // std::visit(lambda, v);
        // lambda->visitable   v->visitor

        std::visit([](auto arg){std::cout<< arg << " ";}, v);
        std::visit([](auto arg){std::cout<< typeid(arg).name() << " ";}, v);

    }


    return 0;
}