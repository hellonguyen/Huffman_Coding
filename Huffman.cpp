#include "huffman.h"
#include <sstream>
using namespace  std;
unordered_map<char,int> Huffman::frequency(string filename)
{
    // 1. put the '\3' at the end of text file as a terminator
    ofstream input(filename, ios::app); // appending the end text character at
    // the end of the input file as a signal to stop reading until reach the character.
    if (input.is_open())
    {
        input << "\3";
        input.close();
    }
    else
    {
        cout << "Can not open the file";
    }
    // 2.read each letter from file and build up the frequency table
    ifstream infile;
    char letter;
    unordered_map<char,int> fre;
    // the initial table with all characters having fre=0
    for (int i=0;i<128;i++)
    {
        char c = i;
        fre[c]=0;
    }
    infile.open(filename); // open input file to read the data
    if(infile.fail())
    {
        cout << "Can not read the file";
    }
    else {
        while (infile.get(letter)) // create a frequency table for characters in the file
        {
            fre[letter]++;
        }
    }
    infile.close();
    return fre;
}

priority_queue<Node*, vector<Node*>,compareWeights> Huffman::createQueue(string filename)
{
    //building the frequency table from text file
    unordered_map<char,int> fre = frequency(filename);
    priority_queue<Node*, vector<Node*>,compareWeights> queue;
    for (auto x:fre)
    {
        // a node with character and its frequency
        Node * element=new Node(x.first,x.second);
        if (element->weight!=0)
        {queue.push(element);} // put it into priority queue
        // if the fre=0, which means that char doesnt exist in textfile ->ignore that
    }
    return queue;
}
// it seems the function creates node by combining 2 characters in the queue
Node* Huffman::buildTree(priority_queue<Node*, vector<Node*>, compareWeights> &Q)
{

    while(!Q.empty())
    {
        Node * newNode = new Node ('\0',0);
        newNode->zero=Q.top();
        Q.pop();
        newNode->one=Q.top();
        Q.pop();
        newNode->weight= (newNode->zero->weight)+ (newNode->one->weight);
        Q.push(newNode);
    }
    return Q.top();
}

//build up the table with character and its code
void Huffman::GiveCode(Node *tree,string s, unordered_map<char,string> &table)
{
    if (tree==nullptr)
    {
        return;
    }
    if (tree->zero==nullptr&&tree->one==nullptr)
    {
        table[tree->letter]=s;
    }
    else
    {
        GiveCode(tree->zero,s+"0",table);
        GiveCode(tree->one,s+"1",table);
    }
}
void Huffman::Compressed(string infile,string outfile)
{
    string header;
    // build priority queue
    priority_queue<Node*, vector<Node*>,compareWeights> queue = createQueue(infile);
    // build up the tree
    root= buildTree(queue);
    unordered_map<char,string> table;
    string s="";
    GiveCode(root,s,table);
    Storage* storage = new Storage();
    if (!storage->open(outfile, "write"))
    {
        cout << "There was an error opening the file." << std::endl;
        exit(0);
    }
    for (auto x: table)
    {
        header+=x.first+x.second+'\4'; // header string contains the table as a string
    }
    storage->setHeader(header);
    ifstream in;
    string line;
    char ch;
    in.open(infile);
    if (in.fail())
    {
        cout << "Can't read file";
    }
    else
    {
        while(in.get(ch))
        {
            auto got = table.find(ch);
            storage->insert(got->second);
        }
    }
    storage->close();
    in.close();
}
Node * Huffman::RebuildTree(unordered_map<char,string>& table)
{
    // take the binary string from the table to build tree
    // create new node on the left if 0 and on the right if 1
    // then put the letter at the end
    Node * tree= new Node('\0',0);
    for (auto x: table)
    {
        string code = x.second;
        Node *temp=tree;
        for (auto ch:code)
        {
            if(ch=='0')
            {
                if(temp->zero==nullptr)
                {
                    temp->zero= new Node('\0',0);
                }
                temp=temp->zero;
            }
            else
            {
                if (temp->one== nullptr)
                {
                    temp->one = new Node ('\0',0);
                }
                temp=temp->one;
            }
        }
        temp->letter=x.first;
    }
    return tree;
}
void Huffman::Decompressed(string infile, string outfile)
{
    Storage * storage = new Storage();
    if (!storage->open(infile, "read"))
    {
        std::cout << "There was an error opening the file." << std::endl;
        exit(0);
    }
    //get the header containing letter+its code to rebuild huffman tree for decoding process
    string header = storage->getHeader();
    // rebuild the table
    istringstream iss(header);
    string word;
    unordered_map<char,string> table;

    while (getline(iss, word,'\4'))
    {
        char c=word[0];
        string x =word.substr(1);
        table[c]=x;
    }
    // rebuild the tree
    Node * tree =RebuildTree(table);
    string result="";
    string binary="";
    ofstream out;
    out.open(outfile);
    // extract the binary string from binary file
    while (storage->extract(result))
    {
        binary+=result;
    }
    // the binary string after extracting might contain unnecessary '0' at the end
    // read until character '\3' (the end of text) and then stop
    string str = table['\3'];
    int pos = binary.rfind(str);
    string substring = binary.substr(0,pos);

    // with the binary string extracted above, now we go to decompress it
    Node *temp=tree;
    for (char c:substring)
    {
        if (c == '0')
        {
            temp=temp->zero;
        }
        else
        {
            temp=temp->one;
        }
        if (temp->zero==nullptr && temp->one==nullptr) // is leaf
        {
            out<<temp->letter;
            temp = tree;
        }
    }
    out.close();
}
