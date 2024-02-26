#include <iostream>
#include <memory>

class MyClass2{
    public:
        void printMyClass2(){
            std::cout<<"I'm in a MyClass2"<<std::endl;
        }
};

class MyClass : public std::enable_shared_from_this<MyClass>{
    public:
        MyClass2 myClass2;

        std::shared_ptr< MyClass > getShared(){
            // return (*this); //legacy code

            return shared_from_this();
        }

        void print(){
            std::cout<<"I'm in a MyClass"<<std::endl;
        }
};

int main(){
    std::cout<<"Shared this pointer !!"<<std::endl;

    std::shared_ptr< MyClass > obj = std::make_shared< MyClass >();  
    std::shared_ptr< MyClass > sharedObj = obj->getShared();

    obj->print();
    sharedObj->print();
    
    sharedObj->myClass2.printMyClass2();
}