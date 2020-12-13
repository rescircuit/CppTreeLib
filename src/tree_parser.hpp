#ifndef TREE_PARSER_H
#define TREE_PARSER_H

#include <string>

struct Node {
    public:
        int val;
        Node *right, *left;
        Node(): val(0), right(nullptr), left(nullptr) {};
        Node(int x): val(x), right(nullptr), left(nullptr) {};
        Node(int x, Node *left, Node *right): val(x), right(right), left(left) {};
};

class TreeParser {
    private:
        static std::vector<Node*> parse_vector(std::string input);
        static Node* construct_tree(std::vector<Node*> vec);


    public:
        static Node* parse_from_file(std::string file_name);
        
        static void print_tree(Node* root);
};

#endif
