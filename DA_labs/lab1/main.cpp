#include <iostream>
#include <vector>
#include <string>

const int MAX_KEY = 65535;
const int FIXED_STRING_LENGTH = 64;

struct key_value_pair {
    int key;
    std::string value;
};

std::string add_zero_to_fixed_string_length(const std::string& str) {
    return str + std::string(FIXED_STRING_LENGTH - str.size(), '\0');
}

void counting_sort(std::vector<key_value_pair>& pairs) {
    std::vector<int> count(MAX_KEY + 1, 0);

    for (const auto& pair : pairs) {
        count[pair.key]++;
    }

    for (int i = 1; i <= MAX_KEY; ++i) {
        count[i] += count[i - 1];
    }

    std::vector<key_value_pair> sorted(pairs.size());
    for (int i = pairs.size() - 1; i >= 0; --i) {
        sorted[--count[pairs[i].key]] = std::move(pairs[i]);
    }

    pairs = std::move(sorted);
}

void print_pairs(const std::vector<key_value_pair>& pairs) {
    for (const auto& pair : pairs) {

        std::cout << pair.key << '\t' << add_zero_to_fixed_string_length(pair.value).c_str() << std::endl;
    }
}

int main() {
    std::vector<key_value_pair> pairs;
    int key;
    std::string value;

    while (std::cin >> key >> value) {
        pairs.push_back({key, value});
    }

    counting_sort(pairs);

    print_pairs(pairs);

    return 0;
}

