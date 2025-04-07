#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "data_types.h"

class FileManager{
    public:
        std::string ler_instrucoes();
        std::vector<bits_32> ler_microinstrucoes();
        void ler_registradores(bits_32* dados);
        void ler_dados(bits_32* dados);
        void escrever_dados(bits_32* dados);

        void create_log_file();
        void close_log_file();
        void print_log(std::string line);

        bits_32 string_to_binary(std::string string);

        std::string binary_to_string(bits_8 b);
        std::string binary_to_string(bits_32 b);
        std::string binary_to_string(bits_32 b, int size);

    private:
        std::ofstream log;
};

#endif