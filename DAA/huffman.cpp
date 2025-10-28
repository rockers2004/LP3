#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// Node structure for Huffman tree
struct Node {
    char ch;        // character
    int freq;       // frequency
    Node *left;     // left child
    Node *right;    // right child

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Custom comparator for min-heap
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;  // smaller freq = higher priority
    }
};

// Recursive function to generate Huffman Codes
void generateCodes(Node* root, string code, unordered_map<char, string> &huffmanCodes) {
    if (!root) return;

    // Leaf node → store code
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    // Traverse left → add "0"
    generateCodes(root->left, code + "0", huffmanCodes);
    // Traverse right → add "1"
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Huffman Encoding function
unordered_map<char, string> huffmanEncoding(vector<char> &chars, vector<int> &freqs) {
    // Step 1: Create a min-heap
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (size_t i = 0; i < chars.size(); i++) {
        minHeap.push(new Node(chars[i], freqs[i]));
    }

    // Step 2: Build the Huffman Tree
    while (minHeap.size() > 1) {
        // Extract 2 smallest nodes
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // Create new internal node
        Node* merged = new Node('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        // Push back to heap
        minHeap.push(merged);
    }

    // Step 3: Generate Huffman codes
    unordered_map<char, string> huffmanCodes;
    Node* root = minHeap.top();
    generateCodes(root, "", huffmanCodes);

    return huffmanCodes;
}

int main() {
    vector<char> chars = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freqs = {5, 9, 12, 13, 16, 45};

    unordered_map<char, string> huffmanCodes = huffmanEncoding(chars, freqs);

    cout << "Huffman Codes:\n";
    for (auto &pair : huffmanCodes) {
        cout << pair.first << " : " << pair.second << "\n";
    }

    return 0;
}

