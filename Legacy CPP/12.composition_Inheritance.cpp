#include <iostream>

class CredentialsInterface{
    public:
        virtual void setUsername(std::string s) = 0;
        virtual std::string getUsername() = 0;
        virtual void setPassword(int n) = 0;
        virtual int getPassword() = 0;
};

class User : public CredentialsInterface{
    public:
        std::string username;
        int password;
        std::string name;
        int age;
        std::string id;
    public:
        User(std::string n, int a, std::string i) : name(n), age(a), id(i){}
        User(std::string n, int a, std::string i, std::string u, int p) : name(n), age(a), id(i), username(u), password(p){} 
        void setUsername(std::string s) override{
            username = s;
        }
        std::string getUsername() override{
            return username;
        }
        void setPassword(int n) override{
            password = n;
        }
        int getPassword() override{
            return password;
        }
        void showDetails(){
            std::cout<<"\nName: "<<name<<std::endl;
            std::cout<<"ID: "<<id<<std::endl;
            std::cout<<"username: "<<username<<std::endl;
            std::cout<<"password: "<<password<<std::endl;
        }
};

// example of composition
class ShowDetailsComposition{
    private:
        User* admin;
    
    public:
        ShowDetailsComposition(User user) : admin(&user){}
        void showDetails(){
            std::cout<<"\nName: "<<admin->name<<std::endl;
            std::cout<<"ID: "<<admin->id<<std::endl;
        }
};

// example of inheritance
// we will get all the properties of User
class ShowDetailsInheritance : public User{
    public:
        ShowDetailsInheritance(std::string n, int a, std::string i, std::string u, int p) : User(n, a, i, u, p){}
        void showDetails(){
            User::showDetails();
        }
};


int main(){
    User user1("User1", 30, "A001");
    user1.setUsername("user1");
    user1.setPassword(123);
    ShowDetailsComposition showDetailsComposition(user1);
    showDetailsComposition.showDetails();

    User user2("User2", 31, "B002");
    user2.setUsername("user2");
    user2.setPassword(334);
    ShowDetailsInheritance showDetailsInheritance(user2.name, user2.age, user2.id, user2.getUsername(), user2.getPassword());
    showDetailsInheritance.showDetails();

    return 0;

}