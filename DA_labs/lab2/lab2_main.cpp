#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <random>

struct bst_node {
    std::pair<std::string, unsigned long long> data;
    
    bst_node* left;
    
    bst_node* right;
    
    int priority;

    bst_node(const std::string& key, unsigned long long value)
        : data(std::make_pair(key, value)), 
          left(nullptr), 
          right(nullptr),
          priority(generate_priority()) 
          {

          }
private:

    int generate_priority() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 10000);
        return dist(gen);
    }
};

class binary_search_tree {

    bst_node *root;

    void delete_tree(bst_node *p) {
        if (p == nullptr) {
            return;
        } else {
            delete_tree(p->left);
            delete_tree(p->right);
            delete p;
        }
    }
    
    std::pair<bst_node*, bst_node*> split_sofia(bst_node* t, std::string k) {
        if (t == nullptr) return std::pair<bst_node*, bst_node*>(nullptr, nullptr);

        if (k <= t->data.first) {
            auto splitted = split_sofia(t->left, k);
            auto t1 = splitted.first;
            auto t2 = splitted.second;

            t->left = t2;

            return std::pair<bst_node*, bst_node*>(t1, t);
        }

        auto splitted = split_sofia(t->right, k);
        auto t1 = splitted.first;
        auto t2 = splitted.second;

        t->right = t1;

        return std::pair<bst_node*, bst_node*>(t, t2);
    }

    static void split_test(bst_node *root_node, std::string const & key, bst_node *&first, bst_node *&second) {
        if(!root_node) {
            first = second = nullptr;
            return;
        }
        if( (root_node->data).first < key){
            split_test(root_node->right, key, root_node->right, second);
            first = root_node;
        } else {
            split_test(root_node->left, key, first, root_node->left);
            second = root_node;
        }
    }

    static void split_test_equal(bst_node *root_node, std::string key, bst_node *&first, bst_node *&second) {
        if(!root_node) {
            first = second = nullptr;
            return;
        }
        if( (root_node->data).first <= key){
            split_test_equal(root_node->right, key, root_node->right, second);
            first = root_node;
        } else {
            split_test_equal(root_node->left, key, first, root_node->left);
            second = root_node;
        }
    }

    bst_node* merge_subtrees(bst_node *first_subtree, bst_node *second_subtree) {
        if (first_subtree == nullptr) return second_subtree;
        if (second_subtree == nullptr) return first_subtree;

        if (first_subtree->priority >= second_subtree->priority) {
            first_subtree->right = merge_subtrees(first_subtree->right, second_subtree);
            return first_subtree;
        }

        second_subtree->left = merge_subtrees(first_subtree, second_subtree->left);
        return second_subtree;
    }


    bst_node* find_node(bst_node *p, std::string const & k) {
        while (p != nullptr && k != (p->data).first) {
            p = (k < (p->data).first) ? p->left : p->right;
        }
        return p;
    }


public:
    binary_search_tree() {
        root = nullptr;
    }

    ~binary_search_tree() {
        delete_tree(root);
    }

    void dispose(std::string const &key) {
        bst_node *less, *equal, *greater;
        split_test(root, key, less, greater);
        split_test_equal(greater, key, equal, greater);
        root = merge_subtrees(less, greater);
    }

    bst_node* search_sofia(std::string const &k) {
        return find_node(root, k);
    }

    void insert_sofia(std::pair<std::string, unsigned long long> const & k) {
        auto splitted = split_sofia(root, k.first);
        auto t1 = splitted.first;
        auto t2 = splitted.second;

        t1 = merge_subtrees(t1, new bst_node(k.first, k.second));
        root = merge_subtrees(t1, t2);
    }

};

void str_to_lower(std::string& str) {
        std::transform(
            str.begin(), 
            str.end(), 
            str.begin(),    
            [](unsigned char c) { return std::tolower(c); });
    }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    binary_search_tree tree;
    std::string s;

    // std::ifstream in("input.txt");
    //std::ofstream out("output.txt");

    while (std::cin >> s) {
        if (s.empty()) {
            continue;
        }

        str_to_lower(s);

        switch (s[0]) {
            case '+': {
                std::string key;
                std::cin >> key;
                unsigned long long value;
                std::cin >> value;
                str_to_lower(key);
                if (tree.search_sofia(key) == nullptr) {
                    tree.insert_sofia({key, value});
                    std::cout << "OK" << std::endl;
                } else {
                    std::cout << "Exist" << "\n";
                }

                break;
            }

            case '-': {
                std::string key;
                std::cin >> key;
                str_to_lower(key);

                if (tree.search_sofia(key) != nullptr) {
                    tree.dispose(key);
                    std::cout << "OK" << "\n";
                } else {
                    std::cout << "NoSuchWord" << "\n";
                }

                break;
            }

            default: {
                if (tree.search_sofia(s) == nullptr) {
                    std::cout << "NoSuchWord" << "\n";
                } else {
                    std::cout << "OK: " << tree.search_sofia(s)->data.second << "\n";
                }

                break;
            }
        }
    }

    return 0;
}