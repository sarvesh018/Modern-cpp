//
//  main.cpp
//  Variants
//
//  Created by Sathya Babu on 07/02/24.
//
 
#include <iostream>
 
#include <variant>
#include <iostream>
#include <cassert>
using namespace std;
 
 
// Union Phase I
 
union Value{
    int i;
    double d;
};
 
Value v;
 
 
// variant Phase II
 
struct S
{
    S(int i) : i(i) {}
    int i;
};
 
class Derived : public std::variant<int, std::string> {
  };
 
// Phase VI
 
 
 
class MyType
{
public:
    MyType() { std::cout << "MyType::MyType \n"; }
    ~MyType() { std::cout << "MyType::~MyType\n"; }
};
 
class OtherType
{
public:
    OtherType() { std::cout << "OtherType::OtherType \n"; }
    OtherType(const OtherType&) {
        std::cout << "OtherType::OtherType(const OtherType&) \n";
    }
    ~OtherType() { std::cout << "OtherType::~OtherType \n"; }
};
 
 
 
int main() {
    /*
     Memory used By :
     
     unions save memory because they allow a single piece of memory to be used for different types of objects
      at different times. Consequently, they can be used to save memory when we have several objects that are
       never used at the same time.
 
     std::variant uses the memory similar to the union. It will take the max size of the underlying types.
     However, std::variant will take a little extra space for all the type-safe functionality provided to us.
     But the extra memory space is well-spent.
     
     
     In order to be able to tell, we need some information about which type of value is being held currently
     in the union. Thus we need to keep track of which type is currently active.
 
     */
 
    // Phase 1
    
    v.d = 76.12345;  // v now holds a double
    cout << v.d << endl; // 76.12345;
    
    cout << v.i << endl; // bad access: 1346901744
    
    // Phase 2
    variant<int, float> vv{99};
 
    // access by index
    cout << "access by index "<<(get<0>(vv)) << endl;  // 99
// access by index 99
    // access by type
    cout <<  "access by type  " << (get<int>(vv)) << endl;  // 99
   // access by index 99
 
                           
    // Phase 4
    //  variants are unions
    std::variant<int, std::string> var5{120},var6{"hi"};
    // index      0          1
    
    std::cout << "  var 5 int   "<< std::get<0>(var5) << '\n';  //  var 5 int   120
    std::cout << "  var 6 data  "<< std::get<1>(var6) << '\n';  //  var 6 data  hi
    std::cout << "  var 5 index "<< var5.index() << '\n';       // var 5 index 0
    std::cout << "  var 6 index "<< var6.index() << '\n';       // var 6 index 1
    std::cout << "  fetch data from Union  0 " << std::get<0>(var5);   // fetch data from Union  0 120
   
    using  variant =  std::variant<int, std::string> ;
    variant var;
    var ="Sathya";
    std::cout << std::endl << " var name "<< std::get<1>( var) << " index "
                                                               << var.index() << endl ; // var name Sathya index 1
    
    var = 110;
    std::cout << std::endl << " var num "<< std::get<0>( var) << " index "
                                                               << var.index() << endl ; // var num 110 index 0
    
   
 
    Derived d = {"hello"};
    std::cout << d.index() << '\n'; std::cout << std::get<1>(d) << '\n'; d.emplace<0>(77); // 1 , hello
    std::cout << std::get<0>(d) << '\n';  // 77
    // prints: 1
    // prints: hello
    // initializes int, destroys string // prints: 77
    
    
 
}