#include <iostream>

int main() {
    int age;
    
    std::cout << "Write your age: ";
    std::cin >> age;
    std::cout << "Your age is " << age << "!\n";
    
    int x = 5;
    if (x == 0) std::cout << "no";
    else std::cout << 10 / x;
    
    return 0;
}