/*
 * File:   Test_LZ77.cpp
 * Author: Michael Horn
 *
 * Created on 8. November 2015, 12:12
 */

#include "Test_LZ77.h"

Test_LZ77::Test_LZ77(unsigned short winSize) {
    windowSize = winSize;
    clearSize = 2 * winSize;
}

Test_LZ77::~Test_LZ77() {
}

void Test_LZ77::decode(const std::string& inFileName, const std::string& outFileName) {
    std::ifstream inputFile(inFileName, std::ifstream::binary);
    std::ofstream outFile(outFileName, std::ofstream::binary);

    std::deque< char > text;

    while (!inputFile.eof()) {
        unsigned short index = 0;
        unsigned short length = 0;
        char symbol = '\0';
        inputFile.read((char*) &index, sizeof (index));
        inputFile.read((char*) &length, sizeof (length));
        inputFile.read((char*) &symbol, sizeof (symbol));

        if (length > 0) {
            for (auto j = 0; j < length; j++) {
                //- 1 da index 0, laenge 1 moeglich
                text.push_back(text[text.size() - index - 1]);
            }
        }
        text.push_back(symbol);

        //Leere Buffer um volllaufen zu verhindern
        if (text.size() > clearSize) {
            const unsigned long to_Write = text.size() - windowSize;
            for (auto i = 0; i < to_Write; i++) {
                outFile << text[i];
            }
            text.erase(text.begin(), text.begin() + to_Write);
        }
        inputFile.peek();
        //Triggert eof und beendet while
    }

    //Speichere Text
    for (auto it = text.begin(); it < text.end(); ++it) {
        //Ende Symbol EOF, kommt immer als letztes! Muss ignoriert werden
        if (!(*it == '\0' && it == text.end() - 1)) {
            outFile << *it;
        }
    }

    text.clear();
    inputFile.close();
    outFile.close();
}
