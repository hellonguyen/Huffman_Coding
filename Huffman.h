#include<string>
#include <queue>
#include <fstream>
#include <unordered_map>
#include "Node.h"
#include "Storage.h"
using namespace std;
#ifndef HUFFMAN_REVIEW_HUFFMAN_H
#define HUFFMAN_REVIEW_HUFFMAN_H
class Huffman
{
private:
    Node * root=nullptr;
public:
    /**
     * The function reads the input file, then tokenizes each character in each word
     * from each line to count the frequency of each character in file.
     * @param filename - name of input file
     * @return table containing character as a key and its frequency
     */
     unordered_map<char,int> frequency(string filename);
    /**
     * The function takes input file, and then create a frequency table for characters in
     * the file. Next, it will put nodes (containing a character and its frequency) into a
     * priority queue.
     * @param filename - name of input file
     * @return the priority queue having nodes that put in order. Nodes with smaller
     * frequency are put at the front of queue
     */
     priority_queue<Node*, vector<Node*>,compareWeights>createQueue(string filename);
    /**
     * The function build a Huffman tree by a group of trees. Combining trees by picking
     * two trees (popping first two elements off in the priority queue), and making a new
     * tree from these two.
     * @param Q - a priority queue that stores Huffman nodes in order based on
     * their frequency
     * @return a root node of Huffman tree
     */
     Node * buildTree(priority_queue<Node*, vector<Node*>, compareWeights> &Q);
    /**
     * The function will receive a huffman tree, and then follow the path of the tree
     * to create a binary code for each character. After that, storing all data into a table
     * @param root - a root of Huffman tree
     * @param s - a string will receive a binary code to present the character.
     * @param table - containing characters and binary strings represent them
     */
     void GiveCode(Node *tree,string s,unordered_map<char,string> &table);
    /**
     * The function will compress data from input file and then store them in the binary file
     * @param infile - name of input file
     * @param outfile - name of output file, where users want to store the compress file.
     */
     void Compressed(string infile,string outfile);
    /**
     * The function takes a table with characters and their binary codes, then re-create
     * a Huffman tree from the data.
     * @param table - containing characters and binary strings represent them
     * @return a root node of Huffman tree
     */
     Node * RebuildTree(unordered_map<char,string>& table);
    /**
     * The function will decompress data to return its origin (not in binary file) and store in
     * the uncompress file
     * @param infile - a compressed file as binary file
     * @param outfile - a uncompressed file which is similar to the origin
     */
     void Decompressed(string infile, string outfile);

};
#endif //HUFFMAN_REVIEW_HUFFMAN_H
