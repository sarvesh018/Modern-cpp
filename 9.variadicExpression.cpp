#include <iostream>

template <typename T>
void print(const T& t){
    std::cout<<"in me: "<<t<<std::endl;
}

template <typename first, typename... rest>
void print(const first& f, const rest&...r){
    // for debugging
    // std::cout<<__PRETTY_FUNCTION__<<std::endl;

    std::cout<<f<<" "; // printing first part
    print(r...); // recursion for rest part
}

// adding numbers
template<typename...T>
auto addNumbers(T ...t){
    // std::cout<<__PRETTY_FUNCTION__<<std::endl;
    return (t+...);
}


// CALLING FUNCTIONS
auto add(){
    std::cout<<"\nAdding"<<std::endl;
}
auto sub(){
    std::cout<<"Subtract"<<std::endl;
}
auto divi(){
    std::cout<<"Division"<<std::endl;
}
auto mul(){
    std::cout<<"Multiple"<<std::endl;
}


template<typename T>
void call(T f){
    f();
}

template <typename TF, typename ...T>
void call(TF f1, T ...f2){
    f1();
    call(f2...);
}



// Calling functions with operator and operand
auto addition(int x, int y){
    std::cout<<"\nAddition: "<<x+y<<std::endl;
}
auto subtract(int x, int y){
    std::cout<<"Subtraction: "<<x-y<<std::endl;
}
auto divide(int x, int y){
    std::cout<<"Division: "<<x/y<<std::endl;
}
auto multiply(int x, int y){
    std::cout<<"Multiply: "<<x*y<<std::endl;
}

template<typename fun, typename O1, typename O2>
void calculate(fun func, O1 x, O2 y){
    func(x, y);
}

template<typename fun, typename O1, typename O2, typename ...Rest>
void calculate(fun func, O1 x, O2 y, Rest ...rest){
    func(x, y);
    calculate(rest...);
}



int main(){
    //first template
    print(123);
    
    // second template
    print(1,"One", 2, "Two", 3, "Three");

    // adding numbers using variadic epressions
    std::cout<<"Sum: "<<addNumbers(2,3,4,3,4,6,5)<<std::endl;

    // calling different functions
    call(add, sub, divi, mul);

    // Calling functions with operator and operand
    calculate(addition,2,3, subtract,4,5, divide,10,5, multiply,3,5);
}