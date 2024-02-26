#include <iostream>

struct singleton_t {
    static singleton_t &instance () {
        static singleton_t instance;
        return instance;
    }

    // how can we use move constructor here ??
    
    singleton_t(const singleton_t &) = delete;
    singleton_t & operator = (const singleton_t&) = delete; // will not allow deep copy

    private:
        singleton_t() {std::cout<<"Singleton Constructor"<<std::endl; }
        ~singleton_t() {std::cout<<"Singleton Destructor"<<std::endl; }

    public:
        void out(){
            std::cout<<"out\n";
        }
};

int main(){
    singleton_t::instance().out();
}
