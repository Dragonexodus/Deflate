/*
 * File:   main.cpp
 * Author: Michael Horn
 *
 * Created on 8. November 2015, 11:59
 */


#include "main.h"

int main() {

    std::ofstream timeFile("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::trunc);
    timeFile << "LZ77:;" << std::endl << "IdenticalSymbol;" << std::endl;
    timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;
    timeFile.close();

    //Test_File_Generator file_Gen = Test_File_Generator(2000, 100000, 8000);

    std::string fileName = "Test/Testfiles/generatedFiles/IdenticalSymbol_";

    LZ77 lz77 = LZ77();
    for (int i = 0; i < 1; i++) {

        if (i == 1) {
            fileName = "Test/Testfiles/generatedFiles/RandomSymbol_";
            timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
            timeFile << "RandomSymbol;" << std::endl;
            timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;
            timeFile.close();
        }
        //250000
        double eX = 0;
        for (unsigned long k = 2000; k <= 250000; k += 8000) {
            timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
            timeFile << k << ";";
            timeFile.close();

            eX = 0;
            for (int i = 0; i < 10; i++) {
                eX += lz77.encode(fileName + std::to_string(k), fileName + std::to_string(k) + ".lz77.encode");
            }
            eX = eX / 10;
            timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
            timeFile << ";" << std::setprecision(10) << eX << std::endl;
            timeFile.close();
        }
        timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
        timeFile << std::endl << std::endl;
        timeFile.close();

    }

    fileName = "Test/Testfiles/generatedFiles/IdenticalSymbol_";
    Huffman huffman = Huffman();
    timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
    timeFile << "Huffman:;" << std::endl << "IdenticalSymbol;" << std::endl;
    timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;
    timeFile.close();
    for (int i = 0; i < 2; i++) {

        if (i == 1) {
            fileName = "Test/Testfiles/generatedFiles/RandomSymbol_";
            timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
            timeFile << "RandomSymbol;" << std::endl;
            timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;
            timeFile.close();
        }
        //250000
        double eX = 0;
        for (unsigned long k = 2000; k <= 250000; k += 8000) {
            timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
            timeFile << k << ";";
            timeFile.close();

            eX = 0;
            for (int i = 0; i < 10; i++) {
                eX += huffman.compressFile(fileName + std::to_string(k), fileName + std::to_string(k) + ".huff.encode");
            }
            eX = eX / 10;
            timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
            timeFile << ";" << std::setprecision(10) << eX << std::endl;
            timeFile.close();
        }
        timeFile.open("Test/Testfiles/Laufzeit.csv", std::ofstream::binary | std::ofstream::app);
        timeFile << std::endl << std::endl;
        timeFile.close();
    }

    return 0;
}

