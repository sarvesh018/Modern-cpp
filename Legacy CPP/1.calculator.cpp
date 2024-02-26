#include<iostream>

// creating abstract class
class Calculator{
    public:
    virtual int add(int x, int y)  = 0;
    virtual int mul(int x, int y)  = 0;
    virtual int sub(int x, int y)  = 0;
    virtual int div(int x, int y)  = 0;
};

class BasicCalculator: public Calculator{
    public:
    int add(int x, int y) override {
        return x + y;
    }
    int mul(int x, int y) override {
        return x * y;
    }  
    int sub(int x, int y) override {
        return x - y;
    }  
    int div(int x, int y) override {
        return x / y;
    }    
};

class User{
    public:
    virtual void addRequestOperation(Calculator *calc, int x, int y) = 0;
    virtual void mulRequestOperation(Calculator *calc, int x, int y) = 0;
    virtual void subRequestOperation(Calculator *calc, int x, int y) = 0;
    virtual void divRequestOperation(Calculator *calc, int x, int y) = 0;
};

class Tom : public User{
    public:
    void addRequestOperation(Calculator *calc, int x, int y) override{
        std::cout<<"Sum: "<< calc->add(x,y)<< std::endl;
    }
    void mulRequestOperation(Calculator *calc, int x, int y) override{
        std::cout<<"Multiply: "<< calc->mul(x,y) <<std::endl;
    }
    void subRequestOperation(Calculator *calc, int x, int y) override{
        std::cout<<"Subtract: "<< calc->sub(x,y) <<std::endl;
    }
    void divRequestOperation(Calculator *calc, int x, int y) override{
        std::cout<<"Divide: "<< calc->div(x,y) <<std::endl;
    }    
};

int main(){
    Calculator* calc = new BasicCalculator();
    User* user = new Tom();

    user->addRequestOperation(calc, 4,5);
    user->mulRequestOperation(calc, 2,3);
    user->subRequestOperation(calc, 6,4);
    user->divRequestOperation(calc, 40,5);

    return 0;
}