#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <execution>

int numEle = 1000;

int main(){
    std::vector<int> nums = {5, 2, 4, 1, 3};
    for(int i=0; i<numEle; i++){
        nums.emplace_back(i*10);
    }

    std::cout<<"Parellel Execution"<<std::endl;

    auto startTime = std::chrono::high_resolution_clock::now();

    //              important
    std::for_each(std::execution::par, nums.begin(), nums.end(), [](int& num){ num *= 2; });

    auto endTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime-startTime);

    // std::cout<<"Modified vector"<<std::endl;
    // for(int n: nums){
    //     std::cout<<n<<"\t";
    // }

    std::cout<<"\nexecution time: "<<duration.count()<<" microseconds"<<std::endl;
}
