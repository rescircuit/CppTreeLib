#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <queue>

#include "tree_parser.hpp"

int calc_exp(int a, int b);

std::vector<Node*> TreeParser::parse_vector(std::string input) {
    // remove spaces
    std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
    input.erase(end_pos, input.end());

	if (input[0] != '[' || input[input.size()-1] != ']') {
        std::cerr << "Failed to parse." << std::endl;
        std::exit(-1);
    }
    input.erase(0, 1);
    input.erase(input.size()-1, 1);
    if (input.size()==0) { 
        std::vector<Node*> vec {nullptr};
        return vec;
    }
    
    std::vector<std::string> strings;
    size_t start, end = 0;
    while ((start = input.find_first_not_of(',', end)) != std::string::npos) {
        end = input.find(',', start);
        strings.push_back(input.substr(start, end-start));
    }
    std::vector<Node*> vec;
    for (std::string str : strings) {
        if (str.compare("null") == 0) {
            vec.push_back(nullptr);
            continue;
        }
        Node *node = new Node(std::stoi(str));
        vec.push_back(node);
    }
	return vec;
}

int calc_exp(int a, int b) {
    int out = 1;
    for (int i=0; i < b; i++) {
        out *= a;
    }
    return out;
}


Node *TreeParser::construct_tree(std::vector<Node*> vec) {
    if (!vec[0]) return nullptr;
    Node *root = vec[0];
    std::queue<Node*> que;
    que.push(root);
    for (int i = 2; calc_exp(2, i-1)-1 < vec.size(); i++) {
        int j = calc_exp(2, i-1)-1;
        int k = calc_exp(2, i)-1;
        for (int l=j; l < k && l < vec.size(); l++) {
            Node *tmp = que.front(); que.pop();
            if (tmp) { tmp->left = vec[l]; }
            que.push(vec[l]);
            l++; if (vec.size() <= l) break;
            if (tmp) { tmp->right = vec[l]; }
            que.push(vec[l]);
        }
    }
    return root;
}

Node* TreeParser::parse_from_file(std::string file_name) {
    std::ifstream file(file_name);
    std::string input;
    getline(file, input); 
    std::vector<Node*> vec = parse_vector(input);
    return construct_tree(vec);
}

void TreeParser::print_tree(Node* root) {
    std::cout << "Not implemented." << std::endl;
}

