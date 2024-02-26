#include <iostream>
#include <ranges>

struct MyRange{
    int data [5] = {10, 20, 30, 40, 50};

    // auto begin() const { return std::begin(data); }
    // auto end() const -> decltype( std::end(data))
    //  { return std::end(data); }
};  

template <class T>
concept Range = requires(T& t){
    std::ranges::begin(t);
    std::ranges::end(t);
};

template <Range R>
void printRange(const R& r){
    for(const auto& value : r){
        std::cout<<" R "<<value<<" ";
    }
}

auto range(int start, int end){
    return std::views::iota(start, end);
}
 
int main(){

    for(int i : std::views::iota(1, 10)){
        std::cout<< i <<" ";
    }
    
    std::cout<<"\n";
    for(int i : std::ranges::iota_view{1, 10}){  // lazy way
        std::cout<< i <<" - ";
    }

    std::cout<<"\n";
    for(int i : range(1, 10)){
        std::cout<< i <<" - ";
    }

    std::cout<<"\n";
    MyRange myRange;
    printRange(myRange.data);

    //printRange(myRange);  // works when we define begin and end inside the class

}