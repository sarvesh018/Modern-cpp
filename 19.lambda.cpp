/*
---------Lambda vs Function object-------

operator overloading () -> is called as funtion object
lamda is function object, it is const, it can throw an error

lamdas are function object, anonymous class with operator overloading
*/

// [ ] called as capture list
// format of lambda -> [] () {}

#include <iostream>

class Annoynmous{
    public:
       template <typename T1, typename T2>
       constexpr auto operator()(const T1 a, const T2 b){
        return a+b;
       }
};

// template<typename T1, typename T2>
constexpr auto sum = [](const auto& a, const auto& b){ return a+b;};

int main(){
    // std::cout<<
    Annoynmous obj;
    std::cout<<obj(4,5)<<std::endl;
    std::cout<<sum(2,3)<<std::endl;
}

