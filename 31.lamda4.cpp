#include <iostream>
#include <vector>

void forEach(const std::vector<int>& values, void(*funPtr)(int)){ // functional composition
    for(int value: values){
        std::cout<<" about to call lamda {}"<<std::endl;
        funPtr(value);
    }
}

int main(){
    std::vector<int> values = {1,4,5,6,3};
    forEach(values, [](int value){std::cout<<"Value: "<<value<<std::endl;});

    return 0;
}
