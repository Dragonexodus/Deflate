/*
 * File:   LZ77.h
 * Author: dragonexodus
 *
 * Created on 8. November 2015, 12:01
 */

#pragma once

#include "Huffman.h"
#include <deque>
#include <fstream>
#include <time.h>
#include <iomanip>

#define LAUFZEIT
/*
 * Fuehrt das LZ77 kompressions verfahren aus
 * Parameter: Fenstergroeße fuer Vergleiche, Anzahl maximaler uebereinstimmender Zeichen
 */
class LZ77 {
public:
    LZ77(const unsigned short winSize =32*1024,const unsigned short maxLength = 256);
    virtual ~LZ77();

    double encode(const std::string&, const std::string&);

private:

    unsigned short windowSize; //Fenstergröße beträgt 32kByte
    unsigned short maxLength; //Maximale uebereinstimmende Bytes
    unsigned long bufferLength; //Datenbuffer
};


