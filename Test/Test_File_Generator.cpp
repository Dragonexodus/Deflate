/*
 * File:   Test_File_Generator.cpp
 * Author: Michael Horn
 *
 * Created on 27. November 2015, 12:12
 */

#include "Test_File_Generator.h"

Test_File_Generator::Test_File_Generator(unsigned long start, unsigned long stop, unsigned long stepWidth) {
    generateFiles(start, stop, stepWidth);
}

Test_File_Generator::~Test_File_Generator() {

}

int Test_File_Generator::generateFiles(unsigned long start, unsigned long stop, unsigned long stepWidth) {

    for (auto i = start; i <= stop; i += stepWidth) {
        std::ofstream symbolAFile("Test/Testfiles/generatedFiles/IdenticalSymbol_" + std::to_string(i), std::ofstream::binary);
        std::ofstream rndFile("Test/Testfiles/generatedFiles/RandomSymbol_" + std::to_string(i), std::ofstream::binary);
        for (auto k = 0; k < i; k++) {
            rndFile << (char) rand();
            symbolAFile << "a";
        }
        rndFile.close();
        symbolAFile.close();
    }
    return 0;
}
