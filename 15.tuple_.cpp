//
//  main.cpp
//  TupleApply
//
//  Created by Sathya Babu on 07/02/24.
//

#include <iostream>
#include <bits/stdc++.h>
#include <tuple>

// Function to add three integers
int add(int a, int b, int c) {
    return a + b + c;
}

void printSum(int a, int b) {
    std::cout << "Sum: " << (a + b) << std::endl;
}

struct Foo {
    void printProduct(double x, double y) {
        std::cout << "Product: " << (x * y) << std::endl;
    }
};

int main() {
    // Create a tuple of arguments
    std::tuple<int, int, int> args(1, 2, 3);

    // Apply the add function to the tuple of arguments
    int result = std::apply(add, args);

    // Print the result
    std::cout << "Result: " << result << std::endl;
    
    // Phase II
    
    auto argss = std::make_tuple(10, 20);
        std::apply(printSum, argss);  // Equivalent to printSum(10, 20)

        // Example using std::invoke
        Foo foo;
        std::invoke(&Foo::printProduct, foo, 2.5, 3.5);  // Equivalent to foo.printProduct(2.5, 3.5)


    return 0;
}
