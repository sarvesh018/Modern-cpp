#include<iostream>

class Operands;

class Operator{
    public:
        void addition(Operands& op);
};

class Operands{
    int x;
    int y;
    public:
        Operands(int&& x, int&& y) : x(x), y(y){}

        // declaring friend function
        friend void Operator::addition(Operands&);
};


// as it is friend function, it can access private variables of Operands class
void Operator::addition(Operands& op){ 
    std::cout << "Addition: " << (op.x + op.y) << std::endl;
}

int main(){
    Operands obj{10, 20};

    Operator opr;
    opr.addition(obj);
}