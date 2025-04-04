#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include "data_types.h"
#include "interpreter.h"

class FileManager{
    public:
        void read_file();
        byte string_to_byte(std::string string);
        //void print_byte(byte b);

    private:
        Interpreter interpreter;
};
#endif