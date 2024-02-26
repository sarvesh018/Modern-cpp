#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

auto even = [](int i){ return i%2 == 0; };

void reverse(){
    const std::vector numbers = {4, 3, 1, 2, 5, 6, 7};
    std::vector< int > temp;

    std::copy_if(std::begin(numbers), std::end(numbers), std::back_inserter(temp), even);

    std::vector<int> temp2(std::begin(temp)+1, std::end(temp));

    std::cout<<"reverse the data - Bad Approach"<<std::endl;

    for(auto iter = rbegin(temp2); iter != rend(temp2); ++iter){
        std::cout<< *iter << " ";
    }

    std::cout<<"Better way of coding"<<std::endl;

    auto rv = std::views::reverse(std::views::drop(std::views::filter(numbers, even), 1));
}

void reverse2(){
    namespace rv = std::ranges::views;
    std::vector< int > n {1, 2, 3, 4, 4, 2, 6, 8, 9, 30};

    auto v = n  | rv::filter(even)
                | rv::reverse
                | rv::take(2);

    for(auto i : v){
        std::cout<<i<<" : ";
    }
}

int main(){
    reverse2();
}