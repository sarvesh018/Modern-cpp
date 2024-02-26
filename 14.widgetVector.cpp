// Phase II

#include <iostream>
#include <vector>

class WidgetVector{
    public:
        using DataType = std::vector<double>; // dataType is a vector

        WidgetVector(){
            values = {1.10, 3.34, 4.35, 34.54, 4.6};
        }

        DataType& data() &{
            return values;
        }

        DataType data() &&{
            return std::move(values); // after returning values will be deleted
        }

    private:
        DataType values;
};

int main(){
    WidgetVector wv1;
    std::cout<<"Display data from lvalue object"<<std::endl;
    for(const auto& x: wv1.data()){ // using object it will return lvalue returning
        std::cout<<x<<" ";
    }

    std::cout<<"\nDisplay data from rvalue object"<<std::endl;
    for(const auto& x: WidgetVector().data()){ // usign classname it will call rvalue returning func
        std::cout<<x<<" ";
    }

    WidgetVector wv2;
    std::cout<<"\nDisplay data from lvalue object"<<std::endl;
    for(const auto& x: wv2.data()){
        std::cout<<x<<" ";
    }
}