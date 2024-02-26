// functional composition using std::bind
#include <iostream>
#include <functional>

constexpr auto add(const int x, const int y) -> int{
    return x+y;
}

int main(){
    using namespace std::placeholders;
    // std::function<int (int, int)> std_fun = std::bind(&add, _1, _2); // for multiple values
    std::function<int (int)> std_fun = std::bind(&add, 100, _1);
    int sum = std_fun(111);

    std::cout<<"Result: "<<sum<<std::endl;
}
