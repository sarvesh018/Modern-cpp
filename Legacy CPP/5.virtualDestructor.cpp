#include<iostream>
using namespace std;

class Base{
    public:
    Base(){
        cout<<"Base constructor"<<endl;
    }

    // if we make it virtual than first derived destructor will be called
    // then base destructor will be called
    virtual ~ Base(){
        cout<<"Base Destructor"<<endl;
    }
};

class Derived:public Base{
    public:
    Derived(){
        cout<<"Derived constructor"<<endl;
    }
    ~ Derived(){
        cout<<"Derived Destructor"<<endl;
    }
};

int main(){
    Base* base = new Derived;

    delete base;
}