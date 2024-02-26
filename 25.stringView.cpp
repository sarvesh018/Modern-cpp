/*
    Never use std::string while printing data, use string_view instead, it makes the work easier
*/

#include <iostream>


void printSubString(std::string_view str){
    // str += "Changed";  // string_view cannot modify the string
    std::cout<<"Sub String: "<< str <<std::endl;
}


int main(){
    const char* str = "Hello World";

    std::string_view view(str, 5); // view first five char
    std::cout<< view <<std::endl;

    printSubString(view);


    // Phase 3
    std::cout<<"\nPhase 3"<<std::endl;

    std::string originalString = "Hello World";
    std::string_view subStringView(originalString.c_str() + 6, 5);

    printSubString(subStringView);
    std::cout<<"Original String: "<<originalString<<std::endl;
}