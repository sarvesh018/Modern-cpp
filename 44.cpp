/*
1. create  a interface iFlightStatus for communication across class
2. create a jetAir which will register and communicate with users
3. create a customer class (Passengers)
4. lets have a vector to store the user credentials in JetAir
5. Whenever the state of jetair changes (pilot on leave) 0/1
6. notifyUsers
*/

#include <bits/stdc++.h>
#include <algorithm>
#include <functional>
using namespace std;

class iFlightStatus{
    public:
        virtual void flightOnTime() = 0;
        virtual void flightDelay() = 0;
};

class JetAir{
    public:
        using User = std::function<void(int)>;
        vector<User> user1;
        vector<class iFlightStatus*> users;
    public:
        // set users using lambda expression
        User setNewUser(std::string name){
            return [](int state){
                (state) ? std::cout<<"Flight on Time" : std::cout<<"Flight is delayed"<<std::endl;                
            };
        }

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

class Suresh : public iFlightStatus{
    public:
    Suresh(){
        cout<<"Suresh is created"<<endl;
    }
    void flightOnTime() override{
        cout<<"Fight on Time"<<endl;
    }
    void flightDelay() override{
        cout<<"Flight Delayed"<<endl;
    }
};

class Saksham : public iFlightStatus{
    public:
    Saksham(){
        cout<<"Saksham is created"<<endl;
    }
    void flightOnTime() override{
        cout<<"Fight on Time"<<endl;
    }
    void flightDelay() override{
        cout<<"Flight Delayed"<<endl;
    }
};

class Sarvesh : public iFlightStatus{
    public:
    Sarvesh(){
        cout<<"Sarvesh is created"<<endl;
    }
    void flightOnTime() override{
        cout<<"Fight on Time"<<endl;
    }
    void flightDelay() override{
        cout<<"Flight Delayed"<<endl;
    }
};

int main(){
    JetAir jet;
    Sarvesh sarvesh;
    Suresh suresh;
    Saksham saksham;

    jet.register_(&sarvesh);
    jet.register_(&suresh);
    jet.register_(&saksham);

    jet.setState(0);

    cout<<"Total Passengers: "<<jet.getSize()<<endl;

    jet.unRegister_(&saksham);

    cout<<"Total Passengers: "<<jet.getSize()<<endl;

    return 0;
}


