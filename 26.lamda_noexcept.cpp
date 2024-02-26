#include <iostream>

/*
Write "noexcept" if lambda will not throw any error, it helps compiler
*/

int global = 10;

int main(){
    std::cout<< global << std::endl;

    auto foo = [=] () mutable noexcept { global++;};
    foo();
    std::cout<< global << std::endl;

    const auto foo2 = [] () noexcept { global++;};
    foo2();
    std::cout<< global << std::endl;
}