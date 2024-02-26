#include <iostream>
using namespace std;

class MyClass{
    public:
        int data;

        MyClass(int&& value){
            data = value;
            cout<<"Move constructor in myclass called"<<endl;
        }
        ~MyClass() = default;
};

int myFunction(){
    return 123; // rValue (any raw value)
}

MyClass createObject(){
    cout<<"Creating Object"<<endl;
    MyClass obj(5);

    return obj; // rValue construct
}

int main(){
    int value = 123;
    MyClass obj(value+1); // value+1 is rValue
    cout<<"obj.data = "<<obj.data<<endl;

    MyClass obj2(myFunction());

    // this constructor is indentified as move constructor
    MyClass obj6 = createObject();
    MyClass obj61 (createObject());
}

// perfect forwarding ??