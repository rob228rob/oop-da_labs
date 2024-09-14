#include "include/allocator.h"
#include "include/vector.h"

#include <map>
#include <unordered_map>
#include <iostream>

using namespace lab5;

int main() {
    std::map<int, int, std::less<int>, BinAllocator<std::pair<const int, int>>> a;
    a[0] = 1;
    a[1] = 2;
    for (const auto &p : a) {
        std::cout << p.first << " " << p.second << std::endl;
    }
    Vector<int, BinAllocator<int>> b;
    b.pushBack(1);
    b.pushBack(2);
    b.pushBack(3);
    for (const auto& i : b) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
