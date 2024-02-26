#include <iostream>

int global = 10;
auto testSpeedTesting = [] (int speed) -> std::string {
    if(speed > 100){
        return "Fast Driver";
    }
    else{
        return "Composed Driver";
    }
};

// std::function<<void>(int)> func
void callWithNumber(void(*bar)(int)){
    bar(10);
}

int main(){
    auto check = testSpeedTesting(101);
    std::cout<<check<<std::endl;


    struct{
        using f_ptr = void(*)(int);
        void operator()(int s) const {return call(s);};
        operator f_ptr() const {return& call;}

        private:
        static void call(int s){std::cout<<s<<std::endl;}
    } baz;

    callWithNumber(baz);
    callWithNumber([](int x){std::cout<<x<<std::endl;});
}