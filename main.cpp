/*
 * File:   main.cpp
 * Author: Michael Horn
 *
 * Created on 8. November 2015, 11:59
 */


#include "main.h"

int main() {

    //Keine überprüfung ob Ordner vorhanden sind...
    std::string timeFilePath = "Test/Testfiles/Laufzeit.csv";

    std::ofstream timeFile(timeFilePath, std::ofstream::binary | std::ofstream::trunc);
    timeFile << "LZ77:;" << std::endl << "IdenticalSymbol;" << std::endl;
    timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;

    //Test_File_Generator file_Gen = Test_File_Generator(2000, 100000, 8000);

    std::string fileName = "Test/Testfiles/generatedFiles/IdenticalSymbol_";

    LZ77 lz77 = LZ77(true);
    for (int i = 0; i < 2; i++) {

        if (i == 1) {
            fileName = "Test/Testfiles/generatedFiles/RandomSymbol_";
            timeFile << "RandomSymbol;" << std::endl;
            timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;
        }
        //250000
        double eX = 0;
        for (unsigned long k = 2000; k <= 250000; k += 8000) {
            timeFile << k << ";";

            eX = 0;
            for (int i = 0; i < 1; i++) {
                std::string tempFileName = fileName + std::to_string(k);
                double timeReturned = 0.0;
                timeReturned = lz77.encode(tempFileName, tempFileName + ".lz77.encode");
                timeFile << std::setprecision(10) << timeReturned << ";";
                eX += timeReturned;

                //Test_LZ77 test_lz77 = Test_LZ77();
                //test_lz77.decode(tempFileName + ".lz77.encode",tempFileName+"lol");
            }
            eX = eX / 10;
            timeFile << ";" << std::setprecision(10) << eX << std::endl;

        }
        timeFile << std::endl << std::endl;

    }

    fileName = "Test/Testfiles/generatedFiles/IdenticalSymbol_";
    Huffman huffman = Huffman(true);
    timeFile << "Huffman:;" << std::endl << "IdenticalSymbol;" << std::endl;
    timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;
    for (int i = 0; i < 2; i++) {

        if (i == 1) {
            fileName = "Test/Testfiles/generatedFiles/RandomSymbol_";
            timeFile << "RandomSymbol;" << std::endl;
            timeFile << "Anzahl;1;2;3;4;5;6;7;8;9;10;;E(X);" << std::endl;
        }
        //250000
        double eX = 0;
        for (unsigned long k = 2000; k <= 2000; k += 8000) {
            timeFile << k << ";";

            eX = 0;
            for (int i = 0; i < 1; i++) {
                std::string tempFileName = fileName + std::to_string(k);
                double timeReturned = 0.0;
                timeReturned = huffman.compressFile(tempFileName, tempFileName + ".huff.encode");
                timeFile << std::setprecision(10) << timeReturned << ";";
                eX += timeReturned;
            }

            eX = eX / 10;
            timeFile << ";" << std::setprecision(10) << eX << std::endl;
        }
        timeFile << std::endl << std::endl;
    }
    timeFile.close();
    return 0;
}

