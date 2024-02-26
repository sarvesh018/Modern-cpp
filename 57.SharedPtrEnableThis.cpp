// //
// //  main.cpp
// //  Shared_ptr_EnableThis
// //
// //  Created by Sathya Babu on 15/02/24.
// //

// #include <iostream>
// #include <memory>
// // Phase II
// class MyClass2{
//     public :
//     void printFromMyCalss2(){
//         std::cout << "Hello I'm in MyClass2 !! " << std::endl ;
        
//     }
// };
// class MyClass : public std::enable_shared_from_this< MyClass>{
// private:
//     int var = 123 ;
//     MyClass2 myClass2 ;
//     public :
//             // Phase II
           
    
//     std::shared_ptr< MyClass> getShared(){
//        // return(*this );
//         return shared_from_this();
//     }
//     void print(){
//         std::cout << "Hello I'm in MyClass!! " << std::endl ;
        
//     }
//   void  getmyVarAndObject(){
//        var = 567 ;
//       std::cout << " getmyVarAndObject " << var << std::endl;
//        myClass2.printFromMyCalss2();
//     }
// };

// int main(int argc, const char * argv[]) {
//     // insert code here...
//     std::cout << "Enable shared ptr...!\n";
    
//     std::shared_ptr< MyClass > obj = std::make_shared< MyClass >();
//     std::shared_ptr< MyClass > sharedObject = obj->getShared();
//     sharedObject->print();
//     obj->print();
//     // Phase II
//     //sharedObject->myClass2.printFromMyCalss2();
//     sharedObject->getmyVarAndObject();
//     return 0;
// }




#include<iostream>
#include<memory>
class Mediator;
class iC{
    public:
    void dis(){
        std::cout<<"JJJJ"<<std::endl;
    }
    virtual void kk() = 0;
};
class C1: public iC{
    std::shared_ptr<Mediator> ptr;
public:
 
C1(std::shared_ptr<Mediator> _ptr){
    ptr = _ptr;
}
    void kk() override {
        std::cout<<"11111"<<std::endl;
    }
};
class C2: public iC{
    std::shared_ptr<Mediator> ptr;
public:
C2(std::shared_ptr<Mediator> _ptr){
    ptr = _ptr;
}
    void kk() override {
        std::cout<<"222222"<<std::endl;
    }
};
class Mediator{
    std::unique_ptr< iC > ptr;
    public:
    void setPtr(std::unique_ptr<iC> _ptr){
        ptr = std::move(_ptr);
    }
    void req(){
        ptr->kk();
    }
 
};
int main(int argc, char const *argv[])
{
    // Mediator m;
    std::shared_ptr< Mediator > m = std::make_shared< Mediator > ();
    m->setPtr( std::make_unique<C2>(m));
    m->req();
    return 0;
}

