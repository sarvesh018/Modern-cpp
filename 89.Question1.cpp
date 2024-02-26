#include <iostream>
#include <type_traits>
#include <ranges>

// Abstract class Stack
class iStack {
public:
    virtual void push(int64_t data) = 0;
    virtual void pop() = 0;
    virtual int64_t top() = 0;
    virtual bool isEmpty() = 0;
};

// Stack Class 
class Stack : public iStack{
    public:
        int64_t topOfStack;
        int64_t store[20];
    public:
        Stack() : topOfStack(-1){}

        void push(int64_t value) override{
            store[++topOfStack] = value;
        }
        
        void pop() override{
            store[--topOfStack];
        }
        
        int64_t top() override{
            int64_t result = store[--topOfStack];
            topOfStack++;

            return result;
        }
        
        bool isEmpty(){
            if(topOfStack<0){
                return false;
            }
            else return true;
        }
};

template <typename Data>
concept CheckType = requires(Data data){
    requires std::is_same_v<decltype(data), int64_t>;
};

// Bug Fix Class
template <CheckType T>
class StackBugFix{
    private:
        Stack stack;
    public:
        StackBugFix(Stack& st) : stack(st){}

        void push(T&& value) {                  // passing raw value which is rValue
            if(stack.topOfStack < 20){          // check if stack is not full
                stack.push(std::forward<T>(value));
            }
            else{
                std::cout<<"Stack is Full"<<std::endl;
            }
        }
        
        void pop() {
            if(stack.topOfStack>=0){            // checks if the stack is empty or not
                stack.pop();
            } 
            else{
                std::cout<<"Stack is Empty"<<std::endl;
            }
        }
        
        T top() {
            if(stack.topOfStack>=0){  
                stack.top();                    // checks if the stack is empty or not
            }
            else{
                std::cout<<"Stack is Empty"<<std::endl;
            }
            return -1;
        }
        
        bool isEmpty(){
            return stack.isEmpty();
        }

};


int main(){

    Stack st;
    // stack.push(10);
    // stack.push(20);
    // stack.pop();
    // stack.pop();
    // stack.pop();

    // Bug Fixed Stack
    StackBugFix<int64_t> stack(st);     // making stack of integer type
    stack.push(10);
    stack.push(20);

    // stack.push("30");

    stack.pop();
    stack.pop();
    stack.pop();

    return 0;
}
