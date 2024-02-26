#include <iostream>
#include <string>
#include <memory>
using namespace std ;
 
enum class  ModeOfPayment{ Card,Gpay };
#define CARD 1
#define GPAY 2
 
//class PaymentWithRetrofit   ;
//class PaymentWithVolley  ;
 
class  PaymentStrategy{
    public :
    void virtual payment_bill_download(string url ,int amount2, string filename , string path) = 0 ;
};
 
//1
class PaymentWithRetrofit : public PaymentStrategy{
public :
    void payment_bill_download(string url, int amount2,string filename, string path) {
        cout << "Payment through " << url <<  endl;
        cout << "PaymentAmount " << amount2 <<  endl;
        cout << "store   "<< filename  <<  endl;
    }
};
 
//2
class PaymentWithVolley : public PaymentStrategy{
public :
    void  payment_bill_download(string url, int amount2,string filename, string path) {
        cout << "Payment through " << url <<  endl;
        cout << "PaymentAmount " << amount2 <<  endl;
        cout << "store   "<< filename  <<  endl;
    }
};
 
    
class PaymentCheck {        
PaymentWithRetrofit  pr ;
        PaymentWithVolley pv ;
            
    public:
//        class Payment {
//            public :
            
            bool isConnect  = false ;
            string  url     = "" ;
            int  amount1    =0;
            int  amount2    =0;
            string filename = "" ;
            int libName     =0  ;
            string path     = "";
             //Payment(){}
        PaymentCheck checkNetwork(string url) {
               this->isConnect = true;
               this->url = url;
            return *this ;
            }
        PaymentCheck  calculate(int amount2) { this->amount2=amount2 ;  return *this ;}
        PaymentCheck  paymentby_method(string fileName) { this->filename = fileName;
           // cout << "Payment method "<< fileName <<  endl;
            return *this ;}
        PaymentCheck  useLib(int  libName) { this->libName = libName;
           // cout << "Payed through "<< libName <<  endl;
            return *this ;}   // Card , Gpay Cash
        PaymentCheck   store(string path){ this->path = path;
          //  cout << "store  "<< path <<  endl;
            return *this ;}
        
            void payment_bill_download() {
                if(isConnect==true){
                   switch(libName){ //
                       case  CARD :
                           pr
                           .payment_bill_download(url,amount2,filename,path) ; // checkout( builder, PayByCard(), ammount())
                                                         case GPAY: pv.payment_bill_download(url,amount2,filename,path);
                       default : cout << "wrong lib name"<< endl;
                    }
                }else{
                    cout << "Out of network "<< endl;
                }
            }
                                                        
    };
// Phase II A simple builder approach
 
//add std::reference_wrapper in place of & use return shared_from_this(); in place of *this  in the following codes
#include <iostream>
#include <string>
 
class Bill : public std::enable_shared_from_this<Bill> {
public:
    std::shared_ptr<Bill> product(const std::string& productName) {
        product_ = productName;
        return shared_from_this();
    }
 
    std::shared_ptr<Bill> brand(const std::string& brandName) {
        brand_ = brandName;
        return shared_from_this();
    }
 
    std::shared_ptr<Bill> cost(double costAmount) {
        cost_ = costAmount;
        return shared_from_this();
    }
 
    std::shared_ptr<Bill> tax(double taxPercentage) {
        tax_ = taxPercentage;
        return shared_from_this();
    }
 
    void display() const {
        double totalCost = cost_ + (cost_ * (tax_ / 100));
        std::cout << "Product: " << product_ << std::endl;
        std::cout << "Brand: " << brand_ << std::endl;
        std::cout << "Cost: " << cost_ << std::endl;
        std::cout << "Tax: " << tax_ << "%" << std::endl;
        std::cout << "Total Cost (including tax): " << totalCost << std::endl;
    }
 
private:
    std::string product_;
    std::string brand_;
    double cost_;
    double tax_;
};
 
void simpleCode() {
    Bill bill;
    bill.product("pen")->brand("Shefer")->cost(32)->tax(10);
    bill.display();
}
 
//----------------------
    
int main(int argc, const char * argv[]) {
    /*
 
   PaymentCheck pc;
    
//       pc
//       // .Payment()
//            .checkNetwork("www.google.com")
//            .calculate(200)
//            .paymentby_method("Payment Done by CARD ")
//            .useLib(CARD)   // CARD
//            .store("/desktop/")
//            .payment_bill_download();
 
        pc  //.Payment()
            .checkNetwork("www.jio.com")
            .calculate(200)
            .paymentby_method("Payment Done by Gpay")
            .useLib(GPAY)      // GPAY
            .store("/Computer/")
            .payment_bill_download();
    
    // Prerequsite for the above code called as Phase II
    cout << endl << endl;
    simpleCode() ;
    */

   simpleCode();
    
    return 0;
 
    }
 
/*
Payment through www.Yahoo.com
PaymentAmount 200
store   Payment Done by Gpay
wrong lib name
Program ended with exit code: 0
*/
 