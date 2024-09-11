#include <iostream>
#include <vector>
#include <bitset>

class utils {
public:
    static void swapIfNeeded(int &from, int &to) {
        if (from > to) {
            std::swap(from, to);
        }
    }

    static int countDigit1OfBinaryNumbersInRange(int from, int to) {
        swapIfNeeded(from, to);
        
        int count = 0;
        for (int i = from; i <= to; ++i) {
            count += std::bitset<32>(i).count(); 
        }
        
        return count;
    }
};