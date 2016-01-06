cmake_minimum_required(VERSION 3.3)
project(AlgorithmEngineering)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    deflate/Huffman.cpp
    deflate/Huffman.h
    deflate/LZ77.cpp
    deflate/LZ77.h
    Test/Test_File_Generator.cpp
    Test/Test_File_Generator.h
    Test/Test_LZ77.cpp
    Test/Test_LZ77.h
    main.cpp
    main.h deflate/Node.cpp deflate/Node.h)

add_executable(AlgorithmEngineering ${SOURCE_FILES})
