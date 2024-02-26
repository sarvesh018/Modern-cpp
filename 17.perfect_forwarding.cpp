#include <iostream>

void funda(int&& var){
    std::cout<<"R - value overload"<<std::endl;
}
void funda(int& var){
    std::cout<<"L - value overload"<<std::endl;
}

// perfect forwarding
template<typename T>
T my_forward(typename std::remove_reference<T>::type& param){
    std::cout<<"my forward "<<static_cast<T>(param)<<std::endl;
    return static_cast<T>(param);
}

template <typename T>
void call_funda(T&& parag){ // argument universal reference
    // funda(parag);   // calls l value
    // funda(std::move(parag)); // calls r value

    // funda(my_forward<T>(parag)); // seperatly calls rvlaue and l value

    // inbuilt function
    funda(std::forward<T>(parag));
}

int main(){

    std::cout<<"l value r value \n"<<std::endl;
    int myVar = 5;
    call_funda(myVar); // l value
    call_funda(4); // r value

    return 0;
}



