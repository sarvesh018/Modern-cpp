#include <iostream>
using namespace std;

class Singleton{
    private:
        static Singleton* instance;
        static int refCounter;
        Singleton(){
            cout<<"Object Created"<<endl;
        }

    public:
        static Singleton getInstance(){
            cout<<"Calling singleton getInstance()"<<endl;
            if(!instance){
                instance = new Singleton;
                refCounter++;
                cout<<"Holding ref to the user "<<refCounter<<" Log."<<endl;
            }
            refCounter++;
            cout<<"Holding ref to the user "<<refCounter<<" Log."<<endl;
            return *instance;
        }

        static int getReference(){
            return refCounter;
        }

        static void clearReference(){
            refCounter--;
        }
};

Singleton* Singleton::instance = nullptr;
int Singleton::refCounter = 0;

int main(){

    Singleton s1 = Singleton::getInstance();
    Singleton s2 = Singleton::getInstance();
    Singleton s3 = Singleton::getInstance();
    Singleton s4 = Singleton::getInstance();

    cout<<"Number of people using: "<<s1.getReference()<<endl;

    cout<<"Removing user"<<endl;
    Singleton::clearReference();

    cout<<"Number of people using: "<<s1.getReference()<<endl;

    return 0;
}