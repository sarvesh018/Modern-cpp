//
//  main.cpp
//  Singleton_SharedPtr
//
//  Created by Sathya Babu on 14/02/24.
//

#include<iostream>
#include<vector>
#include <memory>
using namespace std;

class Singleton {
    public:
    
    Singleton( Singleton const& ) = delete ;
    Singleton& operator = ( Singleton const&) = delete;
    class iterator_my ;
    static std::shared_ptr<  Singleton> instance(){
        
        static std::shared_ptr< Singleton > s { new Singleton };
        cout << " The number of shared objects " << s.use_count() << endl ;
        return s ;
    }
    ~Singleton (){
        cout << " NO one is using the object( Idel ) " <<  endl ;
//        if( refpointer == 0)   // we should not delete the object..
//             delete instance;
    }
    
    private :
    Singleton(){}
    
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance

int main(){
    
    cout << " Lets create a Singletonb "  << endl;
    std::shared_ptr< Singleton > obj1 = Singleton::instance();
    //std::shared_ptr< Singleton > obj2 = Singleton::instance();
    std::shared_ptr< Singleton > obj2 = obj1 ;
    std::shared_ptr< Singleton > obj3 = obj1 ;
    std::shared_ptr< Singleton > obj4 = obj1 ;
    
    
   // Singleton        ::iterator_my itr2;
    std::vector<int> ::iterator itr ;
    
    cout << " ref count " << obj1.use_count();
    
    std::vector<int> vec={1,2,3,4,5,6,7,8,9,10};
    
   
    
    
    
   return 0;
}
