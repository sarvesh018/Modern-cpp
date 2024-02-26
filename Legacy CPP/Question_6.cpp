#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class iFlightStatus{
    public:
        virtual void flightOnTime() = 0;
        virtual void flightDelay() = 0;
};

class Jet{
    public:
        vector<class iFlightStatus*> users;
    public:
        void register_(iFlightStatus* iFlightUser){
            users.emplace_back(iFlightUser);
        }
        
        void unRegister_(iFlightStatus* iFlightUser){
            auto it = std::find(users.begin(), users.end(), iFlightUser);
            if(it != users.end()){
                users.erase(it);
            }
        }

        //get trigerred from external class
        void setState(int state){
            notify(state);
        }

        void notify(int state){
            if(state){
                for(auto x: users){
                    x->flightOnTime();
                }
            }
            else{
                for(auto x: users){
                    x->flightDelay();
                }
            }
        }      

        int getSize(){
            return users.size();
        }
};

// creating user to handle all the users
class User : public iFlightStatus {
private:
    std::string name;
 
public:
    User(const std::string& userName) : name(userName) {
        std::cout << "New user: "<<name << std::endl;
    }
    const std::string& getName() const {
        return name;
    } 
    void flightDelay() override {
        std::cout << "Flight Delayed, " << std::endl;
    }
    void flightOnTime() override {
        std::cout << "Flight On Time, " << std::endl;
    }
};

int main(){
    Jet jet;
    
    User User1("User1");
    User User2("User2");
    User User3("User3");
 
    jet.register_(&User1);
    jet.register_(&User2);
    jet.register_(&User3);
 
    jet.setState(1);
    cout<<"Total Passengers: "<<jet.getSize()<<endl;

    jet.unRegister_(&User1);
    jet.setState(0);
    cout<<"Total Passengers: "<<jet.getSize()<<endl;

    return 0;
}


