#include <iostream>
using namespace std;

// Abstract class Stack
class Stack {
public:
    virtual void enqueue(int data) = 0;
    virtual int dequeue() = 0;
    virtual int top() = 0;
    virtual int bottom() = 0;
    virtual bool isEmpty() = 0;
};

// Stack interface
class iStack : public Stack{
};

class StackArray : public iStack{
    public:
        int topOfStack;
        int bottomOfStack;
        int store[20];
    public:
        void enqueue(int value) override{
            if(topOfStack < 20){
                store[++topOfStack] = value;
            }
            else{
                cout<<"Stack is Full"<<endl;
            }
        }
        int dequeue() override{
            if(topOfStack>=0){
                store[--topOfStack];
            } 
            else{
                cout<<"Stack is Empty"<<endl;
            }
            return -1;
        }
        int top() override{
            if(topOfStack>=0){
                return store[--topOfStack];
                topOfStack++;
            }
            else{
                cout<<"Stack is Empty"<<endl;
            }
            return -1;
        }
        int bottom() override{
            if(topOfStack>=0){
                return store[bottomOfStack];
            }
            else{
                cout<<"Stack is Empty"<<endl;
            }
            return -1;
        }
        bool isEmpty(){
            if(topOfStack<0){
                return false;
            }
            else return true;
        }
};

class FIFO_Stack: public Stack{
    private:
        Stack* stack;
    public:
        FIFO_Stack(Stack* st) : stack(st){}

        void enqueue(int value) override{
            stack->enqueue(value);
        }
        int dequeue() override{
            Stack *temp = new StackArray;
            while(!stack->isEmpty()){
                temp->enqueue(stack->dequeue());
            }
            stack = temp;
            stack->dequeue();
        }
        int top() override{
            stack->bottom();
        }
        int bottom() override{
            stack->top();
        }
        bool isEmpty(){
            stack->isEmpty();
        }
};


int main(){

    Stack* stack = new StackArray;
    stack->enqueue(10);
    stack->enqueue(20);

    Stack* fifo = new FIFO_Stack(new StackArray);
    fifo->enqueue(30);
    fifo->enqueue(40);

    cout<<"Stack: "<<stack->dequeue()<<" "<<stack->dequeue()<<endl;
    cout<<"FIFO: "<<fifo->dequeue()<<" "<<fifo->dequeue()<<endl;

    return 0;
}


