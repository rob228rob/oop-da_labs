#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <string>
#include <initializer_list>

class dynamic_array
{
private:
    unsigned char *data;
    
    int size;
    
    int capacity;

public:
    dynamic_array();

    dynamic_array(const std::string &a);

    dynamic_array(const std::initializer_list<unsigned char> &t);

    dynamic_array(const size_t &n, unsigned char t = 0);

    dynamic_array(const dynamic_array &other);

    ~dynamic_array();
    
    void push_front(unsigned char value);
    
    void del_front();
    
    void push_back(unsigned char value);
    
    int get_size();
    
    unsigned char &operator[](int index);
    
    bool operator==(const dynamic_array& other) const;
    
    unsigned char *begin();
    
    unsigned char *end();
};

#endif // DYNAMIC_ARRAY_H