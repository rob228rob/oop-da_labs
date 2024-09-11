#ifndef UTILS_H
#define UTILS_H

#include <string>

#include "dynamic_array.h" 
#include "octal.h" 

dynamic_array str_to_reverse_dynamic_array(const std::string &a);

void throwIfNumberIsNotRepresentOctal(std::string const &number);

void do_equal_length(dynamic_array &a, dynamic_array &b);  

std::string main_func(std::string const &first, char operand, std::string const &second);

std::string main_func(octal first, char operand, octal second);

#endif // UTILS_H