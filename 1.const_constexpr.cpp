#include <iostream>
// constexpr will always comes in front of function
// const will not come in front of function

const double PI1 = 3.141592653589793;
constexpr double PI2 = 3.141592653589793;
constexpr double PI3 = PI2;

constexpr int i = 100;
int arr[i]; // if i is not const or constexpr it will throw an error, initilization of array i should not varry

const int func_const(const int x, const int y){
    return x + y + 12.3f;
}
constexpr int func_constexpr(int x, int y){
    return x + y + 12.3f;
}


// int arr1[func_const(10,20)]; // not allowed
int arr1[func_constexpr(10,20)]; // here func_constexpr is treated as const 
// int arr2[func_constexpr(10, rand())]; // using rand() will not make it const


//using constexpr with object
class Test{
    public:
        int value;

        constexpr Test(int v) : value(v){}
        constexpr int getValue() const{ // tells compiler that the function will hold a constant value
            return value;
        }
};
constexpr Test test(100);
int arr3[test.getValue()]; // as getvalue is const we can use to initialize the array


// using constexpr with auto
template<bool useFlag>
auto getValue(){
    if constexpr(useFlag){ // (Predicate) if we remove constexpr it will throw error, constexpr will help auto to understand
                           // deducing between double and int
        return 3.13;
    }
    else return 10;
}



// templates
template<typename T>
auto add(T x, T y){ // auto can be replaced with T
    return x+y;
}

int main(){
    int val1 = getValue<false>();
    std::cout<<"int val: "<<val1<<std::endl;

    double val2 = getValue<true>();
    std::cout<<"double val: "<<val2<<std::endl;

    // template example
    std::cout<<"int sum: "<<add(4,5)<<std::endl;
    std::cout<<"float sum: "<<add(4.5f, 34.45f)<<std::endl;

    return 0;
}