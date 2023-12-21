#ifndef NODE_H
#define NODE_H
using namespace std;

struct Node {

    char letter;
    int fre;
    Node * zero;
    Node * one;
    string code; // binary code for element using huffman tree
    Node (char letter)
    {
        this->letter = letter;
        this->zero = nullptr;
        this->one = nullptr;
    }
    Node (char letter, int fre)
    {
        this->letter = letter;
        this->fre= fre;
        this->zero = nullptr;
        this->one = nullptr;
        this->code = "";
    }
    Node(char letter, int fre, Node *zero, Node *one)
    {
        this->letter = letter;
        this->fre=fre;
        this->zero = zero;
        this->one = one;
        this->code = "";
    }
};


#endif //NODE_H


#ifndef COMPARE_WEIGHTS
#define COMPARE_WEIGHTS
/**
 * Class needed for the to compare Nodes in the priority queue
 * @see https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
 */
struct compareWeights
{
    bool operator()(Node* const& lhs, Node* const& rhs)
    {
        return lhs->fre > rhs->fre;
    }
};
#endif // COMPARE_WEIGHTS
