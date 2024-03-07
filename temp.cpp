#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class Observer;

// Subject interface
class Subject{
public:
    virtual void attach(std::shared_ptr<Observer> obs) = 0;
    virtual void detach(std::shared_ptr<Observer> obs) = 0;
    virtual void setPrice(int stockPrice_) = 0;
    virtual void notify() = 0;
    virtual int getStockPrice() = 0;
};

// Observer interface
class Observer : public std::enable_shared_from_this<Observer>{
protected:
    Subject* subject;
    int numberOfStocks;

public:
    Observer(Subject* sub, int num) : subject(sub), numberOfStocks(num){
        subject->attach(shared_from_this());
    }
    int getNumberOfStock(){
        return numberOfStocks;
    }
    virtual void update() = 0;
};

// Concrete Subject
class ConcreteSubject : public Subject{
private:
    std::vector<std::shared_ptr<Observer>> investors; 
    int stockPrice;

public:
    void attach(std::shared_ptr<Observer> obs) override{
        investors.push_back(obs);
    }
    void detach(std::shared_ptr<Observer> obs) override{
        investors.erase(std::remove(investors.begin(), investors.end(), obs), investors.end());
    }
    void setPrice(int stockPrice_) override{
        stockPrice = stockPrice_;
        notify();
    }
    void notify() override{
        for(const auto& obs : investors){
            obs->update();
        }
    }
    int getStockPrice() override{
        return stockPrice;
    }
};

// Investor -> concerete class for all the observers
class Investor : public Observer{
public:
    Investor(Subject* sub, int stocks) : Observer(sub, stocks){}
    void update() override{
        std::cout << "Total Earnings : " << (subject->getStockPrice() * getNumberOfStock()) << std::endl;
    }
};

int main(){

    ConcreteSubject subject;
    auto investor1 = std::make_shared<Investor>(&subject, 13);
    auto investor2 = std::make_shared<Investor>(&subject, 34);

    std::cout<<"Earning on day 1 : "<<std::endl;
    subject.setPrice(219);

    std::cout<<"Earning on day 2 : "<<std::endl;
    subject.setPrice(193);
    return 0;
}
