#include <iostream>
#include <vector>
#include <string>

class z_utils {
public:

    static std::vector<int> compute_z_block(const std::string& src_string) {
        int length = src_string.length();
        std::vector<int> z_blocks(length);
        int left = 0, right = 0;
        for (int i = 1; i < length; ++i) {
            if (i <= right) {
                z_blocks[i] = std::min(right - i + 1, z_blocks[i - left]);
            }
            while (i + z_blocks[i] < length && src_string[z_blocks[i]] == src_string[i + z_blocks[i]]) {
                ++z_blocks[i];
            }
            if (i + z_blocks[i] - 1 > right) {
                left = i;
                right = i + z_blocks[i] - 1;
            }
        }

        return z_blocks;
    }

};

int main() {

    std::string text, pattern;
    std::cin >> text >> pattern;

    std::string combined = pattern + "#" + text;
    std::vector<int> Z = z_utils::compute_z_block(combined);

    int pattern_length = pattern.length();
    int text_length = text.length();
    
    for (int i = 0; i < text_length; ++i) {
        if (Z[pattern_length + 1 + i] == pattern_length) {
            std::cout << i << std::endl;
        }
    }

    return 0;
}