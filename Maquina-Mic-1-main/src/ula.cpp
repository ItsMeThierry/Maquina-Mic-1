#include "include/ula.h"

ULA::ULA(){
   // H = 0b00000011; // Isso daqui vai ser temporário
   // OPC = 0b00000010; // Isso daqui vai ser temporário

    IR = 0;
    vai_um = 0;
    saida = 0;
    sd = 0;
    Z = 0;
    N = 0;
    MBR = 0;
    H = 0;
    OPC = 0;
    TOS = 0;
    CPP = 0;
    LV = 0;
    SP = 0;
    PC = 0;
    MDR = 0;
    MAR = 0;
    MBRU = 0;
}

bits_32 ULA::Set_BarramentoB(bits_21 inst){
    byte entrada = inst & 1111;

    switch(entrada){
        case 0b0000:
            return MDR;
            break;
        case 0b0001:
            return PC;
            break;
        case 0b0010:
            return MBR; //Alterar para preencher depois
            break;
        case 0b0011:
            return MBRU; //Alterar para preencher depois
            break;
        case 0b0100:
            return SP;
            break;
        case 0b0101:
            return LV;
            break;
        case 0b0110:
            return CPP;
            break;
        case 0b0111:
            return TOS;
            break;
        case 0b1000:
            return OPC;
            break;
    }
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
    bits_32 B = (ENB) ? Set_BarramentoB(inst) : 0;

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
            break;
    }

    if(INC){
        somador_completo(saida, 1);
    }

    if(SSL8 && SRA1){
        throw std::string("[Erro] Sinal de entrada inválido\n");
    }

    sd = (SSL8) ? (saida << 8) : 0;
    sd = (SRA1) ? (saida >> 1) : 0;
 
    Z = (saida == 0) ? 1 : 0;
    N = (saida >> 31) & 1;

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

bits_32 ULA::Set_BarramentoC(bits_21 inst){
    bits_9 entrada = inst & 0b000000001111111110000;

    H = (entrada >> 12) ? saida : H;
    OPC = (entrada >> 11) ? saida : OPC;
    TOS = (entrada >> 10) ? saida : TOS;
    CPP = (entrada >> 9) ? saida : CPP;
    LV = (entrada >> 8) ? saida : LV;
    SP = (entrada >> 7) ? saida : SP;
    PC = (entrada >> 6) ? saida : PC;
    MDR = (entrada >> 5) ? saida : MDR;
    MAR = (entrada >> 4) ? saida : MAR;

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