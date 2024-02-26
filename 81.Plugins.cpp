#include <iostream>
#include <memory>

class Connect{
    public:
        virtual ~Connect() {}
        virtual void use_BT_AUX() = 0;          // use interface segregation principle 
};

class AUX : public Connect{
    public:
        void use_BT_AUX() override{
            std::cout<<"Got connected with AUX"<<std::endl;
        }
};

class BT : public Connect{
    public:
        void use_BT_AUX() override{
            std::cout<<"Got connected with BT"<<std::endl;
        }
};


class Pannel{
    protected:
    std::shared_ptr<Connect> plugIn;

    public:
    virtual ~Pannel() = default;
    virtual void usePlugIn() = 0;
    void setConnect(std::shared_ptr<Connect> plug){
        plugIn = plug;
    }
};

class CellPhone : public Pannel{
    public:
        void usePlugIn() override{
            plugIn->use_BT_AUX();
        }
};  
class GoogleMaps : public Pannel{
    public:
        void usePlugIn() override{
            plugIn->use_BT_AUX();
        }
};  



int main(int args, const char * argv[]){

    std::cout<<"\nConnecting BT AUX to the media pannel\n";

    auto aux = std::make_shared<AUX>();
    auto bt = std::make_shared<BT>();

    auto mediaPlayer = std::make_unique<CellPhone>();
    mediaPlayer->setConnect( aux );
    mediaPlayer->usePlugIn();

    auto maps = std::make_unique<GoogleMaps>();
    maps->setConnect( bt );
    maps->usePlugIn();

    return 0;
}