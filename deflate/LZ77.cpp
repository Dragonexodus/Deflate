/*
 * File:   LZ77.cpp
 * Author: Michael Horn
 *
 * Created on 8. November 2015, 12:01
 */
#include "LZ77.h"

LZ77::LZ77(bool time, unsigned short winSiz, unsigned short maxLeng) {
    windowSize = winSiz; //Fenstergröße
    maxLength = maxLeng; //maximale Laenge zum Vergleichen
    bufferLength = maxLength * maxLength; //64kB bei maximaler laenge von 256
    timeMeasurement = time;
}

LZ77::~LZ77() {
}

double LZ77::encode(const std::string& inFileName, const std::string& outFileName) {

    std::ifstream inputFile(inFileName, std::ifstream::binary);
    if (!inputFile.good()) {
        inputFile.close();
        return -1;
    }

    std::ofstream outFile(outFileName, std::ofstream::binary | std::ofstream::trunc);

    double time1 = 0.0;
    double tStart = 0.0;
    if (timeMeasurement) {
        tStart = clock();
    }

    //Wäre mit Pointer vermutlich deutlich schneller....
    std::deque<char> dictonary;
    //Vorschau Fenster enthält pointer zu memBuf
    std::deque<char> preBuffer;
    char* convPreBuffer = new char[bufferLength];

    while (!inputFile.eof()) {
        ///NICHT aendern, std::char::traits<char>::length, liefert nicht die richtige groeße!

        auto bytesReaded = inputFile.readsome(convPreBuffer, bufferLength);
        for (auto i = 0; i < bytesReaded; i++) {
            preBuffer.push_back(convPreBuffer[i]);
        }
        //check for eof
        inputFile.peek();

        while (!preBuffer.empty()) {

            unsigned short index = 0;
            unsigned short length = 0;

            //Suche im Woerterbuch nach einer folge von Uebereinstimmungen...
            for (auto dictPos = 0; dictPos < dictonary.size(); dictPos++) {
                unsigned short tempIndex = 0;
                unsigned short tempLength = 0;

                //...in dem die Stellen im Suchpuffer verglichen werden
                for (auto prePos = 0; prePos < preBuffer.size(); prePos++) {
                    //Uebereinstimmung gefunden!
                    if ((long) dictPos - (long) prePos < 0) {
                        //Verhindere das pos negativ wird
                        break;
                    } else if (dictonary[dictPos - prePos] == preBuffer[prePos]) {

                        tempLength = prePos;
                        tempIndex = dictPos;
                        //Wenn maximale Laenge erreicht,dann abbruch
                        if (tempLength == maxLength - 1) {
                            break;
                        }
                    } else { //Zeichen stimmen nicht ueber ein! Abbruch!
                        break;
                    }
                }

                if (tempLength > length) {
                    index = tempIndex;
                    length = tempLength;
                    //Wenn maximale laenge gefunden,
                    //dann weiteres durchsuchen nicht noetig
                    if (tempLength == maxLength - 1) {
                        break;
                    }
                }
            }

            if (length > 0) { //Zeichenkette hatte uebereinstimmungen

                if(!timeMeasurement){
                    outFile.write((char*) &index, sizeof (index));
                    outFile.write((char*) &length, sizeof (length));
                    if (inputFile.eof() && (preBuffer.size() - length == 0)) {
                        //Ende Symbol, falls letztes Element nicht existiert
                        const char end = '\0';
                        outFile.write((char*) &end, sizeof (end));
                    } else {
                        outFile.write(&preBuffer[length], sizeof (preBuffer[length]));
                    }
                }

                for (auto i = 0; i < length + 1; i++) {
                    // Packe erstes Zeichen des Strings in das Woerterbuch
                    // Entferne erstes Zeichen aus String
                    dictonary.push_front(preBuffer[0]);
                    preBuffer.pop_front();
                    //Woerterbuch ist voll, entferne letztes Element
                    if (dictonary.size() > windowSize) {
                        dictonary.pop_back();
                    }
                }
            } else {
                if(!timeMeasurement) {
                    outFile.write((char *) &index, sizeof(index));
                    outFile.write((char *) &length, sizeof(length));
                    outFile.write(&preBuffer[0], sizeof(preBuffer[0]));
                }
                // Entferne erstes Zeichen
                // Packe erstes Zeichen in das Woerterbuch
                dictonary.push_front(preBuffer[0]);
                preBuffer.pop_front();
                //Woerterbuch ist voll, entferne letztes Element
                if (dictonary.size() > windowSize) {
                    dictonary.pop_back();
                }
            }

        if(!timeMeasurement) {
            if (preBuffer.empty() && length == 0 && inputFile.eof()) {
                // Schreibe Ende zeichen
                outFile.write((char *) &index, sizeof(index));
                outFile.write((char *) &length, sizeof(length));
                const char end = '\0';
                outFile.write((char *) &end, sizeof(end));
            }
        }
            //Buffer wieder auffuellen, falls noch Daten vorhanden
            if (preBuffer.size() < maxLength && !inputFile.eof()) {
                break;
            }
        }

    }

    if(timeMeasurement) {
        time1 += clock() - tStart;
        time1 = time1 / CLOCKS_PER_SEC;
    }

    delete[] convPreBuffer;
    dictonary.clear();
    preBuffer.clear();
    inputFile.close();
    outFile.close();

    return time1;
}
