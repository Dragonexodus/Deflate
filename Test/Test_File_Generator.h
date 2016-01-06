/* 
 * File:   Test_File_Generator.h
 * Author: Michael Horn
 *
 * Created on 27. November 2015, 09:45
 */
#pragma once

#include <fstream>

class Test_File_Generator {
public:
    Test_File_Generator(unsigned long start, unsigned long stop, unsigned long stepWidth);
    virtual ~Test_File_Generator();

private:
    int generateFiles(unsigned long start, unsigned long stop, unsigned long stepWidth);
};


