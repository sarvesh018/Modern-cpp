#include<bits/stdc++.h>
using namespace std;
 
class House;
class StudentLoan;
 
 
//auditor - he is preparing to enter the visitable
class Visitor{
    public:
    virtual double visit(House&) = 0;
    virtual double visit(StudentLoan&) = 0;
};

//us - visitable.
//the virtual function here is preparing for the vistor(auditor) to enter
 
class Visitable{
    public:
    virtual double accept(Visitor&) = 0;
};
 
 
class House : public Visitable{
    public:
    House(double v) : value(v){};
 
    double getValue() { return value;} // this is houses function to provide to the auditor for his calculation
    double accept(Visitor& v) override{ // accept is used to take the auditor in
 
        return v.visit(*this); // this pointer here is the house. v is the visitor obj and visit is its func. to thst we are passing the house
    }
    private:
    double value;
    
};
 
class StudentLoan : public Visitable{
    public:
    StudentLoan(double a) : amount(a){};
 
    double getAmount() { return amount;} // this is student loan's function to provide to the auditor for his calculation
    double accept(Visitor& v) override{ // accept is used to take the auditor in
 
        return v.visit(*this); // this pointer here is the house. v is the visitor obj and visit is its func. to thst we are passing the house
    }
    private:
    double amount;
    
};
 
 
class TaxVisitor : public Visitor{
    public:
       
    double visit(House &house) override{
        cout<<"Housing load --> ";
        return house.getValue() * 0.1;
 
    }
 
    //this wrong, a seperate class for the for the student loan calculation
 
    double visit(StudentLoan& studentloan) override{
        cout<<"Student Loan--> ";
        return studentloan.getAmount() * 0.05;
 
    }
};
 
int main(){
 
    cout<<"Visitor!\n";
 
    vector<Visitable* > visitable; // visitable is us
    visitable.emplace_back(new House(50000));
    visitable.emplace_back(new StudentLoan(10000));
 
    TaxVisitor taxvisitor;
    double totalTax = 0.0;
 
    for(auto asset : visitable){
        totalTax += asset->accept(taxvisitor);
    }
 
    cout<<"Total tax calculated by the visitor(auditor) : "<<totalTax << endl;
 
    
    std::vector< std::variant<House, StudentLoan>> loans = {House(50000), StudentLoan(10000)};
 
    TaxVisitor taxvisitor2;
    for(auto& loan : loans){
        double tax = std::visit([&taxvisitor2](auto&& s){return s.accept(taxvisitor2);} , loan); 
        cout<<"Variant visit TaxVisitor: "<<tax<<endl;
    }
}