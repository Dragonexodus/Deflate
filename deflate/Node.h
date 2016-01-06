/*
 * File:   Node.h
 * Author: Michael Horn
 *
 * Created on 23. December 2015, 09:45
 */
#pragma once
#include <cstdlib>

class Node {
public:
    Node(const char, const unsigned long);
    virtual ~Node();

    char& getSymbol();
    Node* getLeftNode();
    Node* getRightNode();
    unsigned long& getWeight();

    void setWeight(const unsigned long count);
    void setChildNodes(Node*,Node*);

private:
    char symbol;
    Node* leftNode;
    Node* rightNode;
    unsigned long weight;
};

