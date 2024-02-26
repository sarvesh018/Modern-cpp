#include <iostream>

// Phase I
class Widget{
    public:
        void doWork() &{ // put & to return lvalue from function
            std::cout<<"working on lvalue object"<<std::endl;
        }
        void doWork1() &&{ // put && to return rvalue from function
            std::cout<<"working on rvalue object"<<std::endl;
        }
};

int main(){
    Widget widget1;
    widget1.doWork(); // returning lvalue

    Widget().doWork1(); // retruning rvalue
}