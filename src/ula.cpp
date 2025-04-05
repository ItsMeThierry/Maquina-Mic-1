#include "include/ula.h"

ULA::ULA(){
    H = 0b00000011; // Isso daqui vai ser temporário
    OPC = 0b00000010; // Isso daqui vai ser temporário

    PC = 0;
    IR = 0;
    vai_um = 0;
    saida = 0;
    Z = 0;
    N = 0;
}

void ULA::executa(byte inst){

    IR = inst;
    byte op = 0b00110000 & IR;
    bool SSL8 = (IR >> 7) & 1;
    bool SRA1 = (IR >> 6) & 1;
    bool ENA = (IR >> 3) & 1;
    bool ENB = (IR >> 2) & 1;
    bool INVA = (IR >> 1) & 1;
    bool INC = IR & 1;

    bits_32 A = ((ENA) ? H : 0) ^ ((INVA) ? 0xFFFFFFFF : 0);
    bits_32 B = (ENB) ? OPC : 0; // Por enquanto vai ser OPC, mas na tarefa 2 vai mudar

    switch(op){
        case 0b00000000: // A AND B
            saida = A & B;
            vai_um = 0;
            break;
        case 0b00010000: // A OR B
            saida = A | B;
            vai_um = 0;
            break;
        case 0b00100000: // NOT B
            saida = ~B;
            vai_um = 0;
            break;
        case 0b00110000: // A + B
            vai_um = 0;

            somador_completo(A, B);
            // std::cout << "Normal: ";
            // print_binary(saida);
            break;
    }

    if(INC){
        somador_completo(saida, 1);
        // std::cout << "Incrementada: ";
        // print_binary(saida);
    }

    
    // TESTA O SSL8 E SRA1
    // if (op == 0b10000000){
    //    saida = (saida >> 8);
    
    // }else if(op == 0b01000000){

    //     saida = (saida >> 1);
    // }

    // // SETA AS SAÍDAS Z E N
    // if (saida == 0b00000000){
    //     Z = 1;
    // }
    // if (saida == '???'){
    //     N = 1;
    // }

    PC += 1; 
}

void ULA::somador_completo(bits_32 a, bits_32 b){
    saida = 0;

    for(int i = 0; i < 32; i++){
        bool opA = (a >> i) & 1;
        bool opB = (b >> i) & 1;

        saida |= (opA ^ opB ^ vai_um) << i;
        vai_um = (opA & opB) | ((opA ^ opB) & vai_um);
        // print_binary(saida);
        // std::cout << "VAIUM  " << vai_um << std::endl;
    }
}

void ULA::print_binary(byte b){
    for(int i = 7; i >= 0; i--){
        int bit = (b >> i) & 1;
        std::cout << bit;
    }
}

void ULA::print_binary(bits_32 b){
    for(int i = 31; i >= 0; i--){
        int bit = (b >> i) & 1;
        std::cout << bit;
    }

    std::cout << std::endl;
}