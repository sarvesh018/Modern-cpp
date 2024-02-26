#include <iostream>
#include <vector>

using namespace std;

class A{
    public:
        int mx;
        double my;

        // A(int a, int b) : mx(a), my(b){} 
};

class B{
    public:
        int mx;
        double my;
        // B(int x, int y) : mx(x), my(y){}
        B(const std::initializer_list<int>& v){ //----> initializer list or aggregate
            mx = *(v.begin());
            my = *(v.begin()+1);
        }
};

class MyNumber{
    private:
        std::vector<int> myvec;
    public:
        MyNumber(const std::initializer_list<int>& v){
            myvec.insert(myvec.end(), v.begin(), v.end());
        }

        void print(){
            for(const auto& x: myvec){
                std::cout<<x<<" "<<std::endl;
            }
        }
};

int main(){
    A a{10, 20};  //----> uniform initialization or aggregate

    B b{23, 78};


    MyNumber myNumber{10,20,30};
    myNumber.print();

    // take data from class
    auto[aa, bb] = a;
    std::cout<< aa << " " << bb <<std::endl;
}