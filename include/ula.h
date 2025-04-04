#ifndef ULA_H
#define ULA_H

#include "data_types.h"
#include <iostream>

class ULA{
    public:
        ULA();

        void executa(byte inst); // Executa uma instrução
        //void log(); // Gera log

    private:
        byte IR, PC; // Registradores
        //byte N, Z;
        byte vai_um, saida; // Saída da ULA
};

void print_byte(byte b);

#endif
