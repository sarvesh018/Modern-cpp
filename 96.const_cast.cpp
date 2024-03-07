#include <iostream>

int main(){
    int num = 100;
    const int* const_ptr = &num;

    std::cout<<"Original num : " << num <<std::endl;    

    // *const_ptr = 100;        // it cannot be modified as ptr is const

    // we can remove the const-ness using const_cast
    int* non_const_ptr = const_cast<int*>(const_ptr);

    // now we can modify num
    *non_const_ptr = 200;

    std::cout<<"Modified num : " << num <<std::endl;
}