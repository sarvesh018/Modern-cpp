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

// Interface
class iStack : public Stack {
    virtual void enqueue(int data) = 0;
    virtual int dequeue() = 0;
    virtual int top() = 0;
    virtual int bottom() = 0;
    virtual bool isEmpty() = 0;
};

// Stack array
class StackArray : public iStack {
private:
    int arr[20];
    int topIndex = -1;

public:
    void enqueue(int data) override {
        if(topIndex < 20){
            arr[++topIndex] = data;
        }
        else{
            cout<<"Stack is Full"<<endl;
        }
    }

    int dequeue() override {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        return arr[topIndex--];
    }

    int top() override {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        return arr[topIndex];
    }

    int bottom() override {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        return arr[0];
    }

    bool isEmpty() override {
        return topIndex == -1;
    }
};

// Implementing Stack_FIFO using stack
class Stack_FIFO {
private:
    Stack* st;
public:
    Stack_FIFO(iStack* stack) : st(stack) {}

    void enqueue(int data){
        st->enqueue(data);
    }

    int dequeue(){
        Stack *temp = new StackArray;
        while(!st->isEmpty()){
            temp->enqueue(st->dequeue());
        }
        st = temp;
        return st->dequeue();
    }

};

int main() {

    Stack* stack = new StackArray;
    stack->enqueue(10);
    stack->enqueue(20);

    Stack_FIFO fifo (new StackArray);
    fifo.enqueue(30);
    fifo.enqueue(40);

    cout<<"Stack: "<<stack->dequeue()<<" "<<stack->dequeue()<<endl;
    cout<<"FIFO: "<<fifo.dequeue()<<" "<<fifo.dequeue()<<endl;

    return 0;
}
