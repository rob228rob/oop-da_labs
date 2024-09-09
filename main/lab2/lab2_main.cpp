#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>
#include <initializer_list>

#include "include/utils.h"
#include "include/dynamic_array.h"
#include "include/octal.h"

void start_console() {
    std::string first;
    std::string second;
    char operand;

    std::cout << "Input first number:" << std::endl;
    std::cin >> first;
    throwIfNumberIsNotRepresentOctal(first);
    std::cout << std::endl;

    std::cout << "Input operation:" << std::endl;
    std::cin >> operand;
    std::cout << std::endl;

    std::cout << "Input second one:" << std::endl;
    std::cin >> second;
    throwIfNumberIsNotRepresentOctal(second);
    std::cout << std::endl;

    
    std::cout << first << " " << operand << " " << second << " IS equals TO ";
    std::cout << main_func(first, operand, second);
    std::cout << std::endl;
}

int main()
{
    try {
        start_console();
    } 
    catch(std::invalid_argument const & e) 
    {
        std::cout << "Invalid input: " << e.what() << std::endl;
        return 1;
    } 
    catch(std::exception const & e) 
    {
        std::cout << e.what();
    }

    return 0;
}