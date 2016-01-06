/* 
 * File:   Test_LZ77.h
 * Author: Michael Horn
 *
 * Created on 8. November 2015, 12:12
 */

#pragma once
#include <deque>
#include <string>
#include <fstream>

class Test_LZ77 {
public:
    Test_LZ77(const unsigned short winSize =32*1024);
    virtual ~Test_LZ77();

    void decode(const std::string&, const std::string&);
private:
    unsigned short windowSize; //Fenstergröße beträgt 32kByte
    unsigned long clearSize; // Groeße Bufferbereinigung
};


