#include <iostream>
#include <string_view>
#include <array>
#include <algorithm>

struct Car{
    std::string make{};
    std::string model{};
};

int main(){
    std::array<Car, 3> cars{{{"Volkswagen", "Golf"}, {"Toyota", "Corolla"}, {"Honda","Civic"}}};

    int comparisons{0};
    std::sort(cars.begin(), cars.end(), // if we not use & inside [] we have to write mutable
        [&comparisons](const auto& a, const auto& b)  {
            ++comparisons;
            return(a.make < b.make);
        });

    std::cout<<"Comparison compared and sorted "<< comparisons+1 << std::endl;
    for(const auto& car : cars){
        std::cout<< car.make <<" " << car.model << std::endl;
    }


    return 0;
}

