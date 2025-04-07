#include "include/mic1.h"

MIC_1::MIC_1(){
    IR = 0;
    vai_um = 0;
    saida = 0;
    sd = 0;
    Z = 0;
    N = 0;
    MBR = 0b10000001;
    H = 1;
    OPC = 0;
    TOS = 2;
    CPP = 0;
    LV = 0;
    SP = 0;
    PC = 0;
    MDR = 0;
    MAR = 0;
}

void MIC_1::executa_ula(bits_32 inst){

    IR = inst;
    byte op = 0b00110000 & (IR >> 13);
    bool SSL8 = (IR >> 20) & 1;
    bool SRA1 = (IR >> 19) & 1;
    bool ENA = (IR >> 16) & 1;
    bool ENB = (IR >> 15) & 1;
    bool INVA = (IR >> 14) & 1;
    bool INC = (IR >> 13) & 1;

    bits_32 A = ((ENA) ? H : 0) ^ ((INVA) ? 0xFFFFFFFF : 0);
    bits_32 B = (ENB) ? set_barramento_B(IR) : 0;

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

    if(sd != 0){
        set_barramento_C(IR, sd);
    } else{
        set_barramento_C(IR, saida);
    }
 
    Z = (saida == 0) ? 1 : 0;
    N = (saida >> 31) & 1;
}

void MIC_1::somador_completo(bits_32 a, bits_32 b){
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

bits_32 MIC_1::set_barramento_B(bits_21 inst){
    byte entrada = inst & 0b1111;

   switch(entrada){
        case 0b0000:
            return MDR;
            break;
        case 0b0001:
            return PC;
            break;
        case 0b0010:
            bits_32 extendido;
            
            if((MBR >> 7) & 1){               
                extendido = 0xFFFFFF00;      
            }

            return extendido | MBR;
            break;
        case 0b0011:
            return MBR;
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

    return 0;
}

void MIC_1::set_barramento_C(bits_21 inst, bits_32 dados){
    bits_9 entrada = inst & 0b000000001111111110000;

    H = ((entrada >> 12) & 1) ? dados : H;
    OPC = ((entrada >> 11) & 1) ? dados : OPC;
    TOS = ((entrada >> 10) & 1) ? dados : TOS;
    CPP = ((entrada >> 9) & 1) ? dados : CPP;
    LV = ((entrada >> 8) & 1) ? dados : LV;
    SP = ((entrada >> 7) & 1) ? dados : SP;
    PC = ((entrada >> 6) & 1) ? dados : PC;
    MDR = ((entrada >> 5) & 1) ? dados : MDR;
    MAR = ((entrada >> 4) & 1) ? dados : MAR;

}

void MIC_1::print_binary(byte b){
    for(int i = 7; i >= 0; i--){
        int bit = (b >> i) & 1;
        std::cout << bit;
    }
}

void MIC_1::print_binary(bits_32 b){
    for(int i = 31; i >= 0; i--){
        int bit = (b >> i) & 1;
        std::cout << bit;
    }

    std::cout << std::endl;
}
