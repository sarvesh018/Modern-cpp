#include <iostream>
#include <string_view>
#include <functional>
#include <array>
#include <algorithm>

int main(){
    std::array<int, 10> s = {4,5,3,5,6,7,6,4,2,3};

    auto print = [&s](std::string_view const rem){
        for(auto a: s){
            std::cout<<a<<" ";
        }
        std::cout<<" : "<<rem<<std::endl;
    };

    std::sort(s.begin(), s.end());
    print("Sorted with default operator < ");

    std::sort(s.begin(), s.end(), std::greater<int>()); // sort in decending order
    print("Sorted with greater api");

    struct{
        bool operator()(int a, int b) const {return a<b;}
    }customless;
    std::sort(s.begin(), s.end(), customless);
    print("Sorted with custom less");

    std::sort(s.begin(), s.end(), [](int a, int b){
        return a>b;
    });

    std::sort(s.begin(), s.end(), [](int a, int b){return a>b;});    

    print("Sorted with lamda");
    return 0;
}