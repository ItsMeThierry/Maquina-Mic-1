#ifndef ULA_H
#define ULA_H

#include "data_types.h"
#include <iostream>

class MIC_1{
    public:
        byte MBR, MBRU; //Registradores de 8 bits
        bits_32 IR, H, OPC, TOS, CPP, LV, SP, PC, MDR, MAR; // Registradores de 32 bits

        bits_32 saida, sd; // Saída da ULA em 32 bits
        bool vai_um, N, Z; // Saída da ULA em 8 bits

        MIC_1();

        void executa_ula(bits_32 inst); // Executa uma instrução
        void somador_completo(bits_32 a, bits_32 b); // Adiciona dois bits
        bits_32 set_barramento_B(bits_21 entrada); // Seleciona o registrador para o barramento B
        void set_barramento_C(bits_21 entrada, bits_32 saida); //Seleciona os registradores para o barramento C

    private:
        void print_binary(byte b); // Apenas pra debug
        void print_binary(bits_32 b); // Apenas pra debug
};

#endif
