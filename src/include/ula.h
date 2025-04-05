#ifndef ULA_H
#define ULA_H

#include "data_types.h"
#include <iostream>

class ULA{
    public:
        byte IR, PC; // Registradores
        byte vai_um, saida, N, Z; // Saída da ULA

        bool A, B, INVA, INC, AXOR, SSL8, SRA1; // Entrada da ULA 

        ULA();

        void executa(byte inst); // Executa uma instrução
};

void print_byte(byte b);

#endif
