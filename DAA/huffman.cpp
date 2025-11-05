#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

//Node structure for hufffamn tree

struct Node{
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f){
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare{
    bool operator()(Node* a, Node* b){
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<char, string> &huffmanCode ){
    if(!root)
        return;
    if(!root->left && !root->right)
        huffmanCode[root->ch] = code;

    generateCodes(root->left, code +"0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

void buildHuffmanTree(string text){
    unordered_map<char, int> freq;
    for(char ch : text)
        freq[ch]++;
    

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for(auto pair:freq)
        pq.push(new Node(pair.first, pair.second));

    while(pq.size() != 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        Node *sum = new Node('\0', left->freq+right->freq);
        sum->left = left;
        sum->right = right;

        pq.push(sum);
    }

    Node* root = pq.top();
    
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout<<"\n Huffman codes: \n";
    for(auto pair:huffmanCode)
        cout<< pair.first<<" -> "<< pair.second<< '\n';

    string encodedString = "";
    for(char ch: text)
        encodedString += huffmanCode[ch];

    cout<<"\n Original text: " << text << '\n';
    cout<<"Encoded text:"<< encodedString<<'\n';


}

int main(){
    string text;
    cout<< "Enter text to encode: ";
    getline(cin, text);
    buildHuffmanTree(text);
    return 0;
}