#include <iostream>

int main(){
    int ammo{20};

    auto shoot{ // we have to make labda mutable to make changes inside lambda
       
        [ammo] () mutable {
            std::cout<<__PRETTY_FUNCTION__<<std::endl;
            ammo--;
            std::cout<<"Shoot! "<<ammo<<" Shots remaining."<<std::endl;
        }
    };

    shoot();
    shoot();
}
