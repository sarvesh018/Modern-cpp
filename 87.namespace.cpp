#include <iostream>

namespace Wifi_App_Versioning{
    namespace version_1{
        void transmitPacket(){
            std::cout<<"Transmiting via Packets version 1"<<std::endl;
        }
    }

    inline namespace version_2{     // inline makes it default
        void transmitPacket(){
            std::cout<<"Transmiting via Wifi version 2"<<std::endl;
        }
    }

    namespace version_3{
        [[deprecated("Deprecated Version, transmitPacket()")]]
        void transmitPacket(){
            std::cout<<"Transmiting via Wifi version 3"<<std::endl;
        }
        void transmitPacketViaIP(){
            std::cout<<"Transmiting via IP version 3"<<std::endl;
        }
    }
}

int main(){
    Wifi_App_Versioning::version_1::transmitPacket();
    Wifi_App_Versioning::transmitPacket();
    Wifi_App_Versioning::version_3::transmitPacketViaIP();
}