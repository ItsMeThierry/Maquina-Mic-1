#include "mic1.h"

void MIC_1::setup(bits_32* memoria, bits_32* registradores){
    for(int i = 0; i < 8; i++){
        this->memoria[i] = memoria[i];
    }

    IR = 0;
    MBR = 0;

    MAR = registradores[0];
    MDR = registradores[1];
    PC = registradores[2];
    MBR = registradores[3];
    SP = registradores[4];
    LV = registradores[5];
    CPP = registradores[6];
    TOS = registradores[7];
    OPC = registradores[8];
    H = registradores[9];

    saida = 0;
    sd = 0;
    vai_um = 0;
    N = 0;
    Z = 0;
}

void MIC_1::executa_ula(bits_32 inst){

    IR = inst;
    bool SSL8 = (IR >> 22) & 1;
    bool SRA1 = (IR >> 21) & 1;
    bits_8 op = 0b00110000 & (IR >> 15);
    bool ENA = (IR >> 18) & 1;
    bool ENB = (IR >> 17) & 1;
    bool INVA = (IR >> 16) & 1;
    bool INC = (IR >> 15) & 1;

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
        throw std::string("[Erro] Sinal de entrada SSL8/SRA1 inválido");
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

void MIC_1::read_or_write(bits_32 inst){
    bool R = (inst >> 4) & 1;
    bool W = (inst >> 5) & 1;

    if(R && W){
        throw std::string("[Erro] Sinal de entrada R/W inválido");
    }

    if(R){
        MDR = memoria[MAR];
    }

    if(W){
        memoria[MAR] = MDR;
    }
}

void MIC_1::somador_completo(bits_32 a, bits_32 b){
    saida = 0;

    for(int i = 0; i < 32; i++){
        bool opA = (a >> i) & 1;
        bool opB = (b >> i) & 1;

        saida |= (opA ^ opB ^ vai_um) << i;
        vai_um = (opA & opB) | ((opA ^ opB) & vai_um);
    }
}

bits_32 MIC_1::set_barramento_B(bits_21 inst){
    bits_8 entrada = inst & 0b1111;

    switch(entrada){
        case 0b0000:
            return MDR;
        case 0b0001:
            return PC;
        case 0b0010:
            bits_32 extendido;
            
            if((MBR >> 7) & 1){               
                extendido = 0xFFFFFF00;      
            }

            return extendido | MBR;
        case 0b0011:
            return MBR;
        case 0b0100:
            return SP;
        case 0b0101:
            return LV;
        case 0b0110:
            return CPP;
        case 0b0111:
            return TOS;
        case 0b1000:
            return OPC;
    }

    return 0;
}

void MIC_1::set_barramento_C(bits_21 inst, bits_32 dados){
    bits_9 entrada = inst & 0b111111111000000;

    H = ((entrada >> 14) & 1) ? dados : H;
    OPC = ((entrada >> 13) & 1) ? dados : OPC;
    TOS = ((entrada >> 12) & 1) ? dados : TOS;
    CPP = ((entrada >> 11) & 1) ? dados : CPP;
    LV = ((entrada >> 10) & 1) ? dados : LV;
    SP = ((entrada >> 9) & 1) ? dados : SP;
    PC = ((entrada >> 8) & 1) ? dados : PC;
    MDR = ((entrada >> 7) & 1) ? dados : MDR;
    MAR = ((entrada >> 6) & 1) ? dados : MAR;
    
}

void MIC_1::print_binary(bits_8 b){
    for(int i = 7; i >= 0; i--){
        int bit = (b >> i) & 1;
        std::cout << bit;
    }

    std::cout << std::endl;
}

void MIC_1::print_binary(bits_32 b){
    for(int i = 31; i >= 0; i--){
        int bit = (b >> i) & 1;
        std::cout << bit;
    }

    std::cout << std::endl;
}
