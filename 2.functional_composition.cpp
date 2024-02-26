#include<iostream>
#include<type_traits>
#include<cstdio>
#include <functional>

// functional compostion -> parallel execution

const std::string message = "I'm here";
const std::string& foo(){
    return message;
}

auto& increment(int &a){ // auto will not understand betweem reference and value, so we have to put &
    a++;
    return a;
}


struct A{
    double x;
};
const A* a;
decltype(a->x) y; // decltype(a->x) it will take datatype of  
decltype(a->x) z = y;


// trailing data type
auto f(float x) -> auto{
    return  x + 23.2;
}
auto getData1() -> int(&)[2]{ // taking memory address for two elements
    int arr[] = {10, 20};
    return arr;
}


// function composition
constexpr auto add(const int x, const int y) -> int{
    return x+y;
}
// callback function | function pointer (*)() (Legacy Way)
int (*myFuPointer) (int x, int y) = add;


// FUNCTION COMPOSITION
auto resultCalculation(std::function<int(int, int)> OP, const int x, const int y) -> decltype(OP(x, y)){
    return (OP)(x, y); // composition of x and y into add
}


// TEMPLATE FUNCTION COMPOSITION
template <typename FN, typename T, typename U>
constexpr auto resultCalculation2(
                        const FN& op, 
                        const T x,
                        const U y
                        ) -> decltype(op(x, y))
                    {
                        return op(x, y);
                    }

// CHECKING IF THE TEMPLATE IS INVOCABLE OR NOT
template <typename T>
struct is_variable : std::is_object<T>{}; // creating our own isvariable by inheriting std
                                          // to check T is "value" or not

template <typename FN1, typename T1, typename T2>
struct is_invocable : std::__is_invocable<FN1, T1, T2>{};

template <typename FN2, typename T3, typename T4>
constexpr auto resultCalculation3(
                        const FN2& op, 
                        const T3 x,
                        const T4 y
                        ) -> std::enable_if_t<
                            is_invocable<FN2, T3, T4>::value &&
                            is_variable<T3>::value &&
                            is_variable<T4>::value,

                            decltype(op(x, y))
                            >
{
    return op(x, y);
}


// Passing multiple arguments
template <typename FN1, typename... Args>
constexpr auto resultCalculation4(const FN1& op, Args...args) -> decltype(op(args...)){
    return op(args...);
}

// adding multiple arguments
template <typename... Args>
constexpr auto add2(Args... args) -> int{ 
    return (args + ...);
}


int main(){
    std::cout<<"\nauto decltype type triats functional composition\n"<<std::endl;

    const auto f1 = foo();
    decltype(foo()) f2 = foo(); // decltype is more powerfull than auto
    decltype(auto) f3 = foo(); // it can take function inside it and identify the data type

    std::cout<<f1<<std::endl;
    std::cout<<f2<<std::endl;
    std::cout<<f3<<std::endl;    

    int x = 100;
    int& y = increment(x);

    std::cout<<"x = "<<x<<" y = "<<y<<std::endl;


    std::cout<<"\nLegacy Way of adding"<<std::endl;
    std::cout<<"10 + 20 = "<<myFuPointer(10,20)<<std::endl;

    std::cout<<"\nRegular way (composition)"<<std::endl;
    std::cout<<"100 + 200 = "<<resultCalculation(add, 100, 200)<<std::endl;

    std::cout<<"\nRegular way (template)"<<std::endl;
    std::cout<<"109 + 500 = "<<resultCalculation2(add, 109, 500)<<std::endl;

    std::cout<<"\nRegular way with checking conditions"<<std::endl;
    std::cout<<"450 + 290 = "<<resultCalculation3(add, 450, 290)<<std::endl;

    std::cout<<"\nTaking multiple arguments"<<std::endl;
    std::cout<<"345 + 234 + 100 = "<<resultCalculation4(add2<int, int, int>, 345, 234, 100)<<std::endl;
}