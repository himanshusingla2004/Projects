#include<bits/stdc++.h>
using namespace std;

class Huffman{
private:
    unordered_map<char,string> encoder;
    unordered_map<string,char> decoder;

    unordered_map<char,int> freq;

    public:
    class Node{
        public:
        char data;
        int cost; // Freq of this data
        Node* left;
        Node* right;

        Node(char d, int freqq) : data(d), cost(freqq), left(nullptr), right(nullptr) {}
    };

    priority_queue<pair<int,Node*>, vector<pair<int,Node*>>, greater<pair<int,Node*>>> minHeap;

    public:

    // Step 1
    string encode_Form(string str){
        for(char ch : str){
            freq[ch]++;
        }

        for(auto it : freq){
            char key = it.first;
            int cost = it.second;
            Node* newNode = new Node(key, cost);
            minHeap.push({cost,newNode});
        }
    }

    // Function to Build Huffman Tree
    // Step 2
    Node* huffmanTree(){

        while(minHeap.size() > 1){
            auto top = minHeap.top();
            minHeap.pop();

            auto next = minHeap.top();
            minHeap.pop();

            int currCost = top.first + next.first;
            char currChar = '\0';

            Node* currNode = new Node(currChar, currCost);
            currNode->left = top.second;
            currNode->right = next.second;

            // insert in Min Heap
            minHeap.push({currCost, currNode});
        }

        //Return the root of the Huffman tree
        return minHeap.top().second;
    }

    // Step 3
    void generateCodes(Node* root, string code) {
        if (root) {
            if (root->data != '\0') {
                encoder[root->data] = code;
                decoder[code] = root->data;
            }

            generateCodes(root->left, code + "0");
            generateCodes(root->right, code + "1");
        }
    }

    // Step 4
    // Function to encode a given string using the Huffman tree
    string encode(string str) {
        string encodedString = "";

        for (char ch : str) {
            encodedString += encoder[ch];
        }

        return encodedString;
    }

    // Step 5
    // Function to decode the Encoded Form 
    string decode(string str){
        string decodedString = "";
        string curr = "";

        for(auto it : str){
            curr += it;
            if(decoder.find(curr) != decoder.end()){
                decodedString += decoder[curr];
                curr = "";
            }
        }

        return decodedString;
    }
    
};



int main()
{
    string s;
    cout<<"Enter String : "<<endl;
    getline(cin, s); 

    Huffman obj;  // created Object

    obj.encode_Form(s);  // For frequency of each char and encoded form of each char and pushing in minHeap

    Huffman::Node* root = obj.huffmanTree(); // Generated Huffman tree

    obj.generateCodes(root, "");

    // Encode the input String
    string encodedStr = obj.encode(s);
    cout<<"Previous Size of Input String = "<<s.size()*8<<endl;
    cout<<"\nEncoded Form of The Input String = \n"<<encodedStr<<"   AND its size = "<<encodedStr.size();

    cout<<"\n\nNow decoding the encoded String "<<endl;

    string decodeStr = obj.decode(encodedStr);
    cout<<"\nDecoded Form of The Encoded String = \n"<<decodeStr<<endl;

    return 0;
}