//
//  main.cpp
//  FinalCode
//
//  Created by Sathya Babu on 08/02/24.
//

// ****  Study code

#include <iostream>
#include <vector>
#include <typeinfo>
#include <variant>
using namespace std;


template<typename ... Ts>
struct Overload : Ts ...
{
    using Ts::operator() ...;
};
template<class... Ts>               //
Overload(Ts...) -> Overload<Ts...>; // trailing return type to convert the datatype

int main(){
  
    std::cout << '\n';
     
    auto TypeOfIntegral = Overload {     // (1)  holds following varadic lambda's
               [](char)           { return "char"; },
               [](int)            { return "int"; },
               [](unsigned int)   { return "unsigned int"; },
               [](long int)       { return "long int"; },
               [](long long int)  { return "long long int"; },
               [](auto)           { return "unknown type"; },
    };
    
     
    //(2)
    std::variant<char, int, float> var = 123;
    std::cout << std::visit(TypeOfIntegral, var) << '\n';
    
    std::cout << " end of  Phase I" << endl ;
    
    // (3)   ****************************************** END of Ist Phase
    
              std::vector<std::variant<char, long, float, int, double, long long>>  // (1)
                         vecVariant = {5, '2', 5.4, 100ll, 2011l, 3.5f, 2017};

              for (auto v : vecVariant) {                                           // (3)
                   std::cout << std::visit(TypeOfIntegral, v) << '\n';
                 }

              std::cout << " end of  Phase II" << endl ;
    
    // (4)   ****************************************** END of IInd  Phase
    
    std::cout << '\n';

        std::vector<std::variant<std::vector<int>, double, std::string>>      // (4)
            vecVariant2 = { 1.5, std::vector<int>{1, 2, 3, 4, 5}, "Hello "};

        auto DisplayMe = Overload {                                           // (5)
            [](std::vector<int>& myVec) {
                    for (auto v: myVec) std::cout << v << " ";  // display all vector data
                    std::cout << '\n';
                },
            [](auto& arg) { std::cout << arg << '\n';},
        };


        for (auto v : vecVariant2) {                                         // (6)
            std::visit(DisplayMe, v);
        }

    std::cout << " end of  Phase III" << endl ;
  
}
