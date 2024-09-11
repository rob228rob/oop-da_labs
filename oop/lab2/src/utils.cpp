#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>
#include <typeinfo>

#include "../include/octal.h"
#include "../include/dynamic_array.h"
#include "../include/utils.h"

void throwIfNumberIsNotRepresentOctal(std::string const &number) {
    for (const auto digit : number)
    {
        if (digit < '0' || digit > '7')
        {
            throw std::invalid_argument("Invalid octal digit detected");
        }
    }
}

dynamic_array str_to_reverse_dynamic_array(const std::string &a)
{
    std::string res;
    res.resize(a.length());

    for (int i = 0; i <= a.length() - 1; i++)
    {
        res[i] = a[a.length() - i - 1];
    }
    dynamic_array result;
    for (char c : res)
    {
        result.push_back(static_cast<unsigned char>(c));
    }

    return result;
}

void do_equal_length(dynamic_array &a, dynamic_array &b)
{
    int delta = a.get_size() - b.get_size();
    if (delta > 0)
    {
        for (int i = 0; i < delta; i++)
        {
            b.push_back('0');
        }
    }
    else if (delta < 0)
    {
        for (int i = 0; i < -1 * delta; i++)
        {
            a.push_back('0');
        }
    }
}

std::string main_func(std::string const &first, char operand, std::string const &second) 
{
    try {
        octal first_oct(first);
        octal second_oct(second);
        return main_func(first_oct, operand, second_oct);
    } catch (std::invalid_argument const &e) {
        return e.what();
    }
}

std::string main_func(octal first, char operand, octal second)
{
    try {
        if (operand == '+')
        {
            return first.sum(second).to_string();
        }
        else if (operand == '-')
        {
            return first.diff(second).to_string();
        }
        else if (operand == '>')
        {
            return first.more_than(second);
        }
        else if (operand == '<')
        {
            return first.less_than(second);
        }
        if (operand == '=')
        {
            return first.equal(second);
        }
        return "";
    }
    catch (std::invalid_argument const &e) {
        return "invalid input :(";
    }
    
}