#include "huffman.h"
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Comparison object to be used to order the heap
struct comp {
    bool operator()(Node* l, Node* r) {
        // Highest priority item has lowest frequency
        return l->freq > r->freq;
    }
};

// Traverse the Huffman Tree and store Huffman Codes in a map.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode) {
    if (root == nullptr) return;

    // Found a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Builds Huffman Tree and prints the Huffman Codes followed by "###" and the encoded text
string buildHuffmanTree(const string &text) {
    if (text.length() < 1) { cout << "Invailid input" << endl; return "no"; }
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
    ofstream char_code_file {"huffman_code.txt"};
    for (auto pair: huffmanCode) {
         char_code_file << pair.first << " " << pair.second << endl;
    }

    string encodedString;
    for (char ch: text) {
        encodedString += huffmanCode[ch];
    }

    return encodedString;
}

// Function to reconstruct the Huffman tree from the given Huffman codes
Node* buildTreeFromCodes(const std::unordered_map<char, std::string>& codes) {
    Node* root = new Node();
    for (const auto& pair : codes) {
        Node* current = root;
        for (char bit : pair.second) {
            if (bit == '0') {
                if (!current->left) current->left = new Node();
                current = current->left;
            } else { // bit == '1'
                if (!current->right) current->right = new Node();
                current = current->right;
            }
        }
        current->ch = pair.first;
    }
    return root;
}

// Function to decode the encoded string
void decode(Node* root, int &index, const std::string &str, std::string &decoded) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        decoded += root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str, decoded);
    else
        decode(root->right, index, str, decoded);
}

std::string readAndDecode(std::istream& s) {
    std::unordered_map<char, std::string> huffmanCodes;
    std::string line, encodedString;
    ifstream char_code_file {"huffman_code.txt"};
    if (!char_code_file.good()) { throw std::runtime_error("File does not exist: huffman_code.txt"); }

    while (std::getline(char_code_file, line)) {
        std::stringstream ss(line);
        char ch;
        std::string code;
        ss >> std::noskipws >> ch; // Read character
        if (ss.peek() == ' ') ss.get(); // Skip space
        std::getline(ss, code); // Read the rest of the line as code
        huffmanCodes[ch] = code;
    }

    // Read the encoded string
    std::getline(s, encodedString);

    Node* root = buildTreeFromCodes(huffmanCodes);

    // Decode the string
    std::string decodedString;
    int index = -1;
    while (index < (int)encodedString.length() - 1) {
        decode(root, index, encodedString, decodedString);
    }

   return decodedString;
}
