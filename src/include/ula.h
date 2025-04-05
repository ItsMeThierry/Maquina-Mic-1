#ifndef ULA_H
#define ULA_H

#include "data_types.h"
#include <iostream>

class ULA{
    public:
        byte IR, PC; // Registradores de 8 bits
        bits_32 H, OPC; // Registradores de 32 bits

        bits_32 saida; // Saída da ULA em 32 bits
        bool vai_um, N, Z; // Saída da ULA em 8 bits;

        ULA();

        void executa(byte inst); // Executa uma instrução
        void somador_completo(bits_32 a, bits_32 b); // Adiciona dois bits

    private:
        void print_binary(byte b); // Apenas pra debug
        void print_binary(bits_32 b); // Apenas pra debug
};

#endif
