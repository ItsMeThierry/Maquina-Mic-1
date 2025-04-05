#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include "data_types.h"

class FileManager{
    public:
        void read_file();
        byte string_to_byte(std::string string);
        std::string byte_to_string(byte b);
};

#endif