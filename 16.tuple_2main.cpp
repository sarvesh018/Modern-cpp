//
//  main.cpp
//  Tuple_1
//
//  Created by Sathya Babu on 07/02/24.
//

#include <iostream>
#include <tuple>
using namespace std;

std::tuple<int, std::string ,double> f(){
    int i{ 108 };
    std::string s{"Some Text "};
    double d{ 12.22};
    return {i,s,d };
}
void myTuple(){
    
    typedef  tuple<int, char, float > tp ;
    tp t1(100,'A',100.11);
    tp t2(200,'B',200.22);
    tp t3 = make_tuple(300,'C',300.33);
    
    //  Display all the stored elements
    cout << get< 0 >(t1) << endl ;  // 100
    cout << get< 1 >(t1) << endl ;  //  B
    cout << get< 2 >(t1) << endl ;  //   100.11
    
    int i = get<0>(t1);
    cout << " From tuple index 0 " << i << endl;
    
    int first;
    char second ;
    float third ;
    tie( first,second,third) = t2 ;
    cout << "Display set t2 " << first << endl;
    cout << "Display set t2 " << second << endl;
    cout << "Display set t2 " << third << endl;
    
    tie( first,second,third) =   make_tuple(300,'Z',123.33) ;
    cout << "Display set t3 " << first << endl;
    cout << "Display set t3 " << second << endl;
    cout << "Display set t3 " << third << endl;
    
    
    
}

    auto get_student(int id)
    {
        if (id == 0)
            return std::make_tuple(3.8, 'A', "Sharan");
        if (id == 1)
             return std::make_tuple(2.9, 'C', "Sathya");
        if (id == 2)
            return std::make_tuple(1.7, 'D', "Suresh");
    // it is not allowed to return 0 directly
    // return type is std::tuple<double, char, std::string> return std::make_tuple(0.0, 'D', "null");
        return std::make_tuple(0.0, 'n', "nullptr");
    }

void mySecondTuppleCode(){
    
    
    auto student = get_student(0); 
    
                 std::cout << "ID: 0, "
                  << "GPA: "   << std::get<0>(student) << ", "
                  << "Grade: " << std::get<1>(student) << ", "
                  << "Name: "  << std::get<2>(student) << '\n';
        
        double gpa;
        char grade;
        std::string name;
        

        
        std::tie(gpa, grade, name) = get_student(1);
        std::cout << "ID: 1, "
        <<"GPA:" <<gpa<<","
        << "Grade: " << grade << ", "
        << "Name: "  << name << '\n';
        
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
  
    auto [ x , y , z ] = f();
    cout << x << y << z << endl;
    myTuple();
    
    get_student(0);
    mySecondTuppleCode();
    
    return 0;
}
