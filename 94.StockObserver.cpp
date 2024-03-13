#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class Observer;

// Subject interface
class Subject{
public:
    virtual void attach(Observer* obs) = 0;
    virtual void detach(Observer* obs) = 0;
    virtual void setPrice(int stockPrice_) = 0;
    virtual void notify() = 0;
    virtual int getStockPrice() = 0;
};

// Observer interface
class Observer{
protected:
    Subject* subject;
    int numberOfStocks;

public:
    Observer(Subject* sub, int num) : subject(sub), numberOfStocks(num){
        subject->attach(this);
    }
    int getNumberOfStock(){
        return numberOfStocks;
    }
    virtual void update() = 0;
};

// Concrete Subject
class ConcreteSubject : public Subject{
private:
    std::vector<Observer*> investors;
    int stockPrice;

public:
    void attach(Observer* obs) override{
        investors.emplace_back(obs);
    }
    void detach(Observer* obs) override{
        investors.erase(std::remove(investors.begin(), investors.end(), obs), investors.end());
    }
    void setPrice(int stockPrice_) override{
        stockPrice = stockPrice_;
        notify();
    }
    void notify() override{
        // for(const auto& obs : investors){
        //     obs->update();
        // }
        std::for_each(investors.begin(), investors.end(), [](const auto& obs){obs->update();});
    }
    int getStockPrice() override{
        return stockPrice;
    }
};

// Investor -> concerete class for all the observers
class Investor : public Observer{
public:
    Investor(Subject* sub, int stocks) : Observer(sub, stocks){}
    void update(){
        std::cout << "Total Earnings : " << (subject->getStockPrice() * getNumberOfStock()) << std::endl;
    }
};

int main(){

    ConcreteSubject subject;
    Investor investor1(&subject, 13);
    Investor investor2(&subject, 34);

    std::cout<<"Earning on day 1 : "<<std::endl;
    subject.setPrice(219);

    std::cout<<"Earning on day 2 : "<<std::endl;
    subject.setPrice(193);
    return 0;
}