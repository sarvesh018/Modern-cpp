#include <iostream>
#include <functional>
#include <tuple>

using S = std::string;

S convertToCaps(std::string str){
    for(int i=0; i<str.size(); i++){
        str[i] = str[i]-32;
    }
    return str;
}

S addCurlyBracket(std::string str){
    return "{ " + str + " }";
}

S addAdot(std::string str){
    return str+"..";
}

S addHello(std::string str){
    return "HELLO " + str;
}

S acceptAString(std::string str){
    return str;
}

template<typename Func, typename Rest>
auto compose(Func func, Rest rest){
    return [func, rest](const auto& args){
        return func(rest(args));
    };
}

template<typename Func, typename... Rest>
auto compose(Func func, Rest... rest){
    return [func, rest...](const auto& args){
        return func(compose(rest...)(args));
    };
}

int main(){
    auto functionComposition = compose(addCurlyBracket, addHello, addAdot, convertToCaps, acceptAString);
    auto result = functionComposition("sarvesh");

    std::cout<<result;
}
