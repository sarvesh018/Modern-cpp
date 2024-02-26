#include<iostream>
#include<functional>
void foo(int x, int y){
    std::cout<<"foo("<<x<<", "<<y<<")"<<std::endl;
}

class Bar{
    public:
        void bar(int x, int y){
            std::cout<<"Bar:bar("<<x<<", "<<y<<")"<<std::endl;
        }
};

int main(){

    // example with invoke
    std::invoke(foo, 5, 6); //calls (5,6)

    // example with bind
    auto f1 = std::bind(foo, 1, std::placeholders::_1);
    f1(2);

    Bar b;
    auto f2 = std::bind(&Bar::bar, &b, std::placeholders::_2, std::placeholders::_1);
    f2(3, 4);

    Bar b2;
    std::invoke(&Bar::bar, &b2, 7, 8); // calls b2.bar(7, 8)

    return 0;
}