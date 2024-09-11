#ifndef OCTAL_H
#define OCTAL_H

#include "dynamic_array.h"
#include <string>
#include <stdexcept>

class octal
{
private:
    dynamic_array Array_value;
public:

    octal(const std::string &mass);

    void show();

    std::string to_string();

    
    octal sum(octal num);
    
    octal diff(octal num);
    
    std::string less_than(octal num);
    
    std::string more_than(octal num);
    
    std::string equal(octal num);
};

#endif // OCTAL_H