#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "data_types.h"
#include "binary_manipulator.h"

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

    private:
        std::ofstream log;
};

#endif