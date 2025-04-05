#include "include/ula.h"

ULA::ULA(){
    PC = 0;
    IR = 0;
    vai_um = 0;
    saida = 0;
    Z = 0;
    N = 0;
}

void ULA::executa(byte inst){

    IR = inst;
    byte op = 0b00110000 & IR; // TODO: mudar a configuração dos bits quando usar todos os 8
    A = (IR >> 3) & 1;
    B = (IR >> 2) & 1;
    INVA = (IR >> 1) & 1;
    INC = IR & 1;
    AXOR = A ^ INVA;
    SSL8 = (IR >> 7) & 1;
    SRA1 = (IR >> 6) & 1;
    
    //print_byte(op);

    switch(op){
        case 0b00000000: // A AND B
            saida = AXOR & B;
            vai_um = INC;
            break;
        case 0b00010000: // A OR B
            saida = AXOR | B;
            vai_um = INC;
            break;
        case 0b00100000: // NOT B
            saida = ~B;
            vai_um = INC;
            break;
        case 0b00110000: // A + B
            saida = (AXOR ^ B) | (B & INC);
            vai_um = INC | (AXOR & B);
            break;

    }

    
    // TESTA O SSL8 E SRA1
    if (op == 0b10000000){
       saida = (saida >> 8);
    
    }else if(op == 0b01000000){

        saida = (saida >> 1);
    }

    // SETA AS SAÍDAS Z E N
    if (saida == 0b00000000){
        Z = 1;
    }
    if (saida == '???'){
        N = 1;
    }

    PC += 1; 
}

void print_byte(byte b){
    for(int i = 7; i >= 0; i--){
        int bit = (b >> i) & 1;
        std::cout << bit;
    }
}