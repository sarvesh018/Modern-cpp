// we cannot write template on the top of lambda

#include <iostream>

void print(){}

template<typename First, typename... Rest>
void print(const First& f, const Rest... rest){
    std::cout<<f<<std::endl;
    print(rest...);
}


// fold expression
template<typename ...T>
auto doSomething(T... t){
    return (t+...);
}

// lambda expression
// we can use class || typename
constexpr auto add = [] <class... T>(T ...args) 
{
    return (args+...);
};

int main(){
    //std::function<void<Args...>> variadic_lambda = [] (auto... parm){print(parm)}

    // LAMBDA EXPRESSION
    auto variadic_lambda = [] (auto... parm){ print(parm...); };

    variadic_lambda(123, "Sarvesh", 23, 2.3);

    std::cout<<"\nDo something: "<<doSomething(23,43,45,34,23)<<std::endl;
    std::cout<<"Lamda Add: "<<add(23,23,34,45,64)<<std::endl;

    return 0;
}