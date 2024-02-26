#include <iostream>
#include <memory>

class A; class B;

class A{
    public:
        std::shared_ptr<B> pointer;
        
        A(){
            std::cout<<"Constructor of A"<<std::endl;
        }
        ~A(){
            std::cout<<"Destructor of A"<<std::endl;
        }
};

class B{
    public:
        std::shared_ptr<A> pointer;
        
        B(){
            std::cout<<"Constructor of B"<<std::endl;
        }
        ~B(){
            std::cout<<"Destructor of B"<<std::endl;
        }
};

int main(){
    std::shared_ptr<A> a = std::make_shared< A >();
    std::shared_ptr<B> b = std::make_shared< B >();

    a->pointer = b;
    b->pointer = a;

}