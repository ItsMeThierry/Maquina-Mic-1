#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include "data_types.h"

class FileManager{
    public:
        void read_file();
        
        bits_32 string_to_binary(std::string string);

        std::string binary_to_string(byte b);
        std::string binary_to_string(bits_32 b);
};

#endif