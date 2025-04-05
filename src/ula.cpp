#include "include/ula.h"

ULA::ULA(){
    PC = 0;
    IR = 0;
    vai_um = 0;
    saida = 0;
}

void ULA::executa(byte inst){

    IR = inst;
    byte op = 0b00110000 & IR; // TODO: mudar a configuração dos bits quando usar todos os 8
    bool A = (IR >> 3) & 1;
    bool B = (IR >> 2) & 1;
    bool INVA = (IR >> 1) & 1;
    bool INC = IR & 1;
    bool AXOR = A | INVA;
    
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

    // Debug
    std::cout << "IR = ";
    print_byte(IR);
    std::cout << " , PC = ";
    print_byte(PC);
    std::cout << " , A = ";
    print_byte(A);
    std::cout << " , B = ";
    print_byte(B);
    std::cout << " , S = ";
    print_byte(saida);
    std::cout << " , Vai_um = ";
    print_byte(vai_um);
    std::cout << std::endl;

// teste
    PC += 1; 
}

void print_byte(byte b){
    for(int i = 5; i >= 0; i--){ // Temporariamente vai ficar 5
        int bit = (b >> i) & 1;
        std::cout << bit;
    }
}