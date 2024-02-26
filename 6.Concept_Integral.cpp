/**
* This code requires 20th version of c++
* g++ -std=c++20 P9.c++ --for compiling in c++ 20
*/
#include <iostream>
#include <bits/stdc++.h>
/**
* instead of struct and using, we will use concept
*/
//uncomment this for compiling it in gcc 12 or lower than 20
// template <typename T> using Integral = typename std::is_integral<T>::value;
/**
* Phase 1
*/
 
/**
* Below part will only works for c++ 20, coz usage of concept
*/
template <typename T>
concept Integral = std::is_integral<T>::value;
 
 
// Integral auto gcd( Integral auto a, Integral b){
//     if(b == 0) return a;
//     else return gcd(b, a%b);
// }
 
/**
* Phase 2
*/
 
// template<Integral T>  //this all will work fine
template<typename T>
    T gcd(T a, T b){
        if(b == 0) return a;
        return gcd(b, a%b );
    }
 
// last lecture
template <typename T> 
concept Addable = requires(T a, T b){
    { a + b} -> std::same_as< T >;
};
/**
* this will look up, (usually the templates will look down,) , if it passes the Addable then only the prorgam will work
* for the below function, the Addable is the prerequistive
*/
template< Addable T > T addTwoValues(T a, T b){
    return a + b;
}
int main(){
    std::cout<<"gcd: "<<gcd(10, 20)<<std::endl;
    std::cout<<"Add: "<<addTwoValues(10, 20)<<std::endl;
    // std::cout<<"Add: "<<addTwoValues(10, 20.9)<<std::endl;//it wont work, coz the requirements are not met (both are not same)
 
    return 0;
}