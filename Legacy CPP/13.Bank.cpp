#include <iostream>

class RBI_Bank {
    public:
        virtual void deposit(long amount) = 0;
        virtual void withdraw(long amount) = 0;
};

class CitiBank : public RBI_Bank {
    private:
        long balance;

    public:
        CitiBank(long amount){
            balance = amount;
        }
        void deposit(long amount) override {
            balance += amount;
            std::cout<<amount<<" \u20b9 added"<<std::endl;
            std::cout<<"Available Balance: "<<balance<<" \u20b9"<<std::endl;
        }

        void withdraw(long amount) override {
            if (balance >= amount) {
                balance -= amount;
                std::cout << "CitiBank withdraw amount: " << amount <<"\u20b9"<< std::endl;
                std::cout<<"Available Balance: "<<balance<<" \u20b9"<<std::endl;
            }
            else{
                std::cout << "Citi Bank -> Insufficient Amount." << std::endl;
            }
        }

        void illegalWithdraw(long amount){
            std::cout << "Citi Bank -> Illegal Withdraw amount "<<amount<< std::endl;
        }
};

class HDFC_Bank : public RBI_Bank {
    private:
        long balance;

    public:
        HDFC_Bank(long amount){
            balance = amount;
        }
        void deposit(long amount) override {
            balance += amount;
            std::cout<<amount<<" \u20b9 added"<<std::endl;
            std::cout<<"Available Balance: "<<balance<<" \u20b9"<<std::endl;
        }

        void withdraw(long amount) override {
            if (balance >= amount) {
                balance -= amount;
                std::cout << "CitiBank withdraw amount: " << amount <<"\u20b9"<< std::endl;
                std::cout<<"Available Balance: "<<balance<<" \u20b9"<<std::endl;
            } else {
                std::cout << "HDFC Bank -> Insufficient Amount." << std::endl;
            }
        }
};

class User{
    private:
        RBI_Bank* rbi_bank;
    public:
        User(RBI_Bank* account) : rbi_bank(account){}

        void depositeMoney(long amount){
            rbi_bank->deposit(amount);
        }
        void withdrawMoney(long amount){
            rbi_bank->withdraw(amount);
        }
};

int main() {

    RBI_Bank* citiBank = new CitiBank(10000);
    RBI_Bank* hdfc_bank = new HDFC_Bank(20000);

    User u1(citiBank);
    u1.depositeMoney(1900);
    u1.withdrawMoney(20000);
    // u1.illegalWithdraw(300);

    User u2(hdfc_bank);
    u2.depositeMoney(1900);
    u2.withdrawMoney(2500);

    return 0;
}
