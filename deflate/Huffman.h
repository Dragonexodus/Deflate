/*
 * File:   Huffman.h
 * Author: Michael Horn
 *
 * Created on 27. November 2015, 09:45
 */
#pragma once
#include "Node.h"
#include <unordered_map>
#include <cstdlib>
#include <iostream>
#include <deque>
#include <assert.h>
#include <fstream>
#include <iterator>
#include <time.h>
#include <iomanip>

#define LAUFZEIT
class Huffman {
public:
    Huffman();
    virtual ~Huffman();

    double compressFile(const std::string&, const std::string&);

private:

    Node* buildTree(std::unordered_map<char, unsigned long> &);
    void codeGenerator(Node*,std::unordered_map<char,std::deque<bool>>&);
    void compressText();
    void getSymbolsCount(const std::deque<char> &, std::unordered_map<char, unsigned long>&);
};
