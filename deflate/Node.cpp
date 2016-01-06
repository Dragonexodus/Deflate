/*
 * File:   Node.h
 * Author: Michael Horn
 *
 * Created on 23. December 2015, 09:45
 */

#include "Node.h"
//TODO Besser wäre mit Vererbung-> Unterscheidung Knoten/Wurzel von Blättern!

Node::Node(const char symb, const unsigned long count) {
    symbol = symb;
    weight = count;
    leftNode = NULL;
    rightNode = NULL;
}

Node::~Node() {
    if(leftNode != NULL){
        delete leftNode;
    }
    if(rightNode != NULL){
        delete  rightNode;
    }
}

char & Node::getSymbol(){
    return symbol;
}
Node* Node::getLeftNode(){
    return leftNode;
}
Node* Node::getRightNode(){
    return rightNode;
}
unsigned long& Node::getWeight(){
    return weight;
}
void Node::setWeight(const unsigned long count){
    weight = count;
}

void Node::setChildNodes(Node* left,Node* right){
    leftNode = left;
    rightNode = right;
}
