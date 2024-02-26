#include <iostream>
using namespace std;

int foo(){
    return 10;
}

std::string myCat(){
    return "CAT";
}


class Vector{
    public:
        int* elements;
        int size;
    
    public:
        Vector(int s) : size(s){
            elements = new int[size];
            for(int j=0; j<size; j++){
                elements[j] = j;
            }
            cout<<"Regular Constructor"<<endl;
        }
        ~Vector(){
            cout<<"Regular Destructor"<<endl;
            delete [] elements;
            size = 0;
        }
        // copy constructor
        Vector(const Vector& vector) : size(vector.size){
            cout<<"Copy Constructor"<<endl;
            elements = new int[vector.size];
            for(int i=0; i<vector.size; i++){
                elements[i] = vector.elements[i];
            }
        }

        // move constructor
        Vector(Vector&& vector) : size(0), elements(nullptr){
            cout<<"Move constructor"<<endl;
                        // size = vector.size;
                        // elements = vector.elements;

                        // // deleting the passed Vector object
                        // vector.elements = nullptr; 
                        // vector.size = 0;   
            std::swap(elements,vector.elements); // reduced the number of cycles
            std::swap(size, vector.size);        // more effective code
        }

        int getSize(){
            return size;
        }

        // operator overloading
        int& operator[](int ind){
            return elements[ind];
        }
};

// creating iterator
int* begin(Vector& v){
    cout<<"begin()"<<endl;
    return v.elements;
}

int* end(Vector& v){
    cout<<"end()"<<endl;
    return v.getSize()!=0 ? &v[0] + v.getSize() : nullptr;
}

int main(){
    std::cout<<"Expressions lvalue and rvalue"<<std::endl;

    int *arr;
    int *p;
    int x;
    int y;  //lValue

    // rValue
    foo();
    12;
    x+y;

    int& lValue = x;
    int&& rValue = 30;

    const int& L_r_value = 23; // do not get const infront of lvalue

    nullptr_t myVar; //prValue (pure value)
    // NULL xyz; // (void*)0

    std::string s("Cat");
    std::string s2(s); // copy Constructor | MOVE Constructor
    std::string s3(myCat()); 
    std::string s4(std::move(myCat())); // move constructor -> do its job and return rValue and clear memory



    // Move constructor
    Vector v1(10); // regular constructor
    // Vector v2(v1); // copy construtor

    for(auto i: v1){
        cout<<i<<" ";
    }
    cout<<endl;

    Vector v3(static_cast<Vector&&> (v1)); // forcing v1 rValue
    Vector v4(std::move(v1)); // move will convert everything into rValue

    for(auto i: v1){
        cout<<i<<" ";
    }
    cout<<endl;

}

