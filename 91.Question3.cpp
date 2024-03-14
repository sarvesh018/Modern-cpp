#include <iostream>

const int64_t size = 10;

template<typename T>
class Array{
    public:
        T array [size];

        Array() = default;                   // default constructor

        Array(const Array& obj){
            for(T i=0; i<size; i++){
                array[i] = obj.array[i];
            }
        }

        Array(const Array&& obj){
            for(T i=0; i<size; i++){
                array[i] = obj.array[i];
            }

            delete obj;
        }

        void setValue(T&& value, T&& index){
            std::cout<<"Inside rvalue"<<std::endl;
            array[index] = value;
        }

        void setValue(T& value, T& index){
            std::cout<<"Inside lvalue"<<std::endl;
            array[index] = value;
        }

        template <typename F>
        void setArrayValue(F&& value, F&& index){                           // perfect forwarding
            setValue(std::forward<F>(value), std::forward<F>(index));   // calls lValue or rValue function
        }

        int operator[](int ind){
            return array[ind];
        }

        ~Array() = default;                   // default destructor
        
};

template<typename T>
void setValue(T&& value, T&& index){
    std::cout<<"Inside rvalue"<<std::endl;
    // array[index] = value;
}

template<typename T>
void setValue(T& value, T& index){
    std::cout<<"Inside lvalue"<<std::endl;
    // array[index] = value;
}

template <typename F>
void setArrayValue(F&& value, F&& index){                           // perfect forwarding
    setValue(std::forward<F>(value), std::forward<F>(index));   // calls lValue or rValue function
}



int main(){
    Array<int64_t> array1;
    for(int i=0; i<size; i++){
        array1.array[i] = i+1;
    }

    Array<int64_t> array2(array1);

    int val = 10;
    int ind = 0;
    array2.setArrayValue(val, ind);         // passing lValue  
    array2.setArrayValue(20, 1);            // passing as rValue

    setArrayValue(val, ind);         // passing lValue      // perfect forwarding works fine outside class
    setArrayValue(20, 1);            // passing as rValue

    std::cout<<array1[ind]<<" "<<array1[1]<<std::endl;
    std::cout<<array2[ind]<<" "<<array2[1]<<std::endl;
}

