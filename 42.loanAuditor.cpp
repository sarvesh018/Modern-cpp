#include <iostream>
#include <variant>
#include <vector>

struct CarLoan{
    float monthlyAmount;
    float interest;
};

struct HomeLoan{
    float monthlyAmount;
    float interest;
};

template<typename T>
struct Auditor{
    float operator()(const T& t){
        return t.monthlyAmount + t.monthlyAmount*t.interest;
    }
};

int main(){
    std::cout<<"Auditor Loan"<<std::endl;
    CarLoan carLoan{50000.0f, 0.25};
    HomeLoan homeLoan{65670.0f, 0.20};

    float totalAmount = 0.0f;

    using Loans = std::variant<CarLoan, HomeLoan>;
    std::vector<Loans> loan_vec = {carLoan, homeLoan};   

    for(auto& v: loan_vec){
        totalAmount += std::visit(
            [](auto& loan){
                return Auditor<std::decay_t<decltype(loan)>>{}(loan);
            }, v
        );
    }

    std::cout<<"Total Amount Calculated by Auditor: "<< totalAmount <<std::endl;
}
