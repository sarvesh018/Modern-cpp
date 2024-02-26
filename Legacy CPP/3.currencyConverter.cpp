#include <iostream>

//RULE: base class has to go with aggregation

class iCurrencyConvertor{ // INTERFACE
    public:
    // at runtime memory will not be allocated to const (constant)
    // memory will be allocated at compile time
    virtual std::string getCurrency() const = 0;

    // iCurrencyConvertor() = delete; //we cannot create class using delete

    iCurrencyConvertor() = default; 
    virtual ~iCurrencyConvertor() = default; // if we do not have body for destructor we can use default
};

class CurrencyAsString : public iCurrencyConvertor{
    public:
    CurrencyAsString(std::string str){
        cur = str;
    }
    std::string getCurrency() const override{
        return cur;
    }
    private:
    std::string cur;
};

class CurrencyFormater{
    private:
    const iCurrencyConvertor* convertor;
    public:
    CurrencyFormater(const iCurrencyConvertor* convertor) : convertor(convertor){}

    std::string getFormattedCurrency() const{
        std::cout<<"Formated Currency ";
        std::string curr = convertor->getCurrency();

        if(curr == "RS"){
            // std::cout<<"Rs. = \u20b9"<<std::endl;
            return "Rs. = \u20b9";
        }
        else if(curr == "Dollar"){
            // std::cout<<"Dollar = $"<<std::endl;
            return "Dollar = $";
        }
        else if(curr == "Yen"){
            // std::cout<<"Yen = \u00A5"<<std::endl;
            return "Yen = \u00A5";
        }
        else if(curr == "Arab"){
            // std::cout<<"Arab = \u6041"<<std::endl;
            return "Arab = \u6041";
        }
        else{
            // std::cout<<"Unknown Currency..."<<std::endl;
            return "Unknown Currency...";
        }
    }
};


int main(){
    std::cout<<"Currency Convertor"<<std::endl;

    CurrencyAsString currencyAsString("RS");
    CurrencyFormater currencyFormater(&currencyAsString);
    std::cout<<currencyFormater.getFormattedCurrency()<<std::endl;

    return 0;
}
