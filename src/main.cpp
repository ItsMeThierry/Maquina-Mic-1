#include <iostream>
#include "file_manager.h"
#include "mic1.h"

std::string decode_c(bits_32 inst){
    bits_9 code = inst & 0b111111111000000;
    std::string out;

    if((code >> 14) & 1) out += "H ";
    if((code >> 13) & 1) out += "OPC ";
    if((code >> 12) & 1) out += "TOS ";
    if((code >> 11) & 1) out += "CPP ";
    if((code >> 10) & 1) out += "LV ";
    if((code >> 9) & 1) out += "SP ";
    if((code >> 8) & 1) out += "PC ";
    if((code >> 7) & 1) out += "MDR ";
    if((code >> 6) & 1) out += "MAR ";

    return out;
}

std::string decode_b(bits_32 inst){
    bits_8 code = inst & 0b1111;

    switch(code){
        case 0b0000:
            return "MDR";
        case 0b0001:
            return "PC";
        case 0b0010:
            return "MBR";
        case 0b0011:
            return "MBRU";
        case 0b0100:
            return "SP";
        case 0b0101:
            return "LV";
        case 0b0110:
            return "CPP";
        case 0b0111:
            return "TOS";
        case 0b1000:
            return "OPC";
        default:
            return "X";
    }
}

int main() { 
    FileManager f_manager;
    MIC_1 mic1;

    std::vector<bits_32> instrucoes;

    try{
        bits_32 dados[8];
        bits_32 registradores[10];

        instrucoes = f_manager.ler_microinstrucoes();
        f_manager.ler_dados(dados);
        f_manager.ler_registradores(registradores);
        f_manager.create_log_file();
        
        mic1.setup(dados, registradores);
    }catch(std::string e){
        std::cerr << e << std::endl;
        return -1;
    }

    f_manager.print_log("=====================================================\n");
    f_manager.print_log("Comeco do programa\n");
    f_manager.print_log("=====================================================\n");

    int c = 1;
    for(bits_32 inst : instrucoes){
        f_manager.print_log("Ciclo " + std::to_string(c) + "\n");
        f_manager.print_log("IR = " + f_manager.binary_to_string(inst, 23) + "\n\n");

        f_manager.print_log("BAR_B : " + decode_b(inst) + '\n');
        f_manager.print_log("BAR_C : " + decode_c(inst) + "\n\n");

        f_manager.print_log("> Registradores antes da instrucao\n");
        f_manager.print_log("MAR = " + f_manager.binary_to_string(mic1.MAR) + "\n");
        f_manager.print_log("MDR = " + f_manager.binary_to_string(mic1.MDR) + "\n");
        f_manager.print_log("PC = " + f_manager.binary_to_string(mic1.PC) + "\n");
        f_manager.print_log("MBR = " + f_manager.binary_to_string(mic1.MBR) + "\n");
        f_manager.print_log("SP = " + f_manager.binary_to_string(mic1.SP) + "\n");
        f_manager.print_log("LV = " + f_manager.binary_to_string(mic1.LV) + "\n");
        f_manager.print_log("CPP = " + f_manager.binary_to_string(mic1.CPP) + "\n");
        f_manager.print_log("TOS = " + f_manager.binary_to_string(mic1.TOS) + "\n");
        f_manager.print_log("OPC = " + f_manager.binary_to_string(mic1.OPC) + "\n");
        f_manager.print_log("H = " + f_manager.binary_to_string(mic1.H) + "\n\n");

        try{
            mic1.executa_ula(inst);
            mic1.read_or_write(inst);
        }catch(std::string e){
            f_manager.print_log(e + '\n');
            break;
        }   

        f_manager.print_log("> Registradores depois da instrucao\n");
        f_manager.print_log("MAR = " + f_manager.binary_to_string(mic1.MAR) + "\n");
        f_manager.print_log("MDR = " + f_manager.binary_to_string(mic1.MDR) + "\n");
        f_manager.print_log("PC = " + f_manager.binary_to_string(mic1.PC) + "\n");
        f_manager.print_log("MBR = " + f_manager.binary_to_string(mic1.MBR) + "\n");
        f_manager.print_log("SP = " + f_manager.binary_to_string(mic1.SP) + "\n");
        f_manager.print_log("LV = " + f_manager.binary_to_string(mic1.LV) + "\n");
        f_manager.print_log("CPP = " + f_manager.binary_to_string(mic1.CPP) + "\n");
        f_manager.print_log("TOS = " + f_manager.binary_to_string(mic1.TOS) + "\n");
        f_manager.print_log("OPC = " + f_manager.binary_to_string(mic1.OPC) + "\n");
        f_manager.print_log("H = " + f_manager.binary_to_string(mic1.H) + "\n\n");

        f_manager.print_log("> Memoria depois da instrucao\n");
        
        for(bits_32 b : mic1.memoria){
            f_manager.print_log(f_manager.binary_to_string(b) + '\n');
        }

        f_manager.print_log("=====================================================\n");

        c++;
    }

    f_manager.print_log("FIM DO PROGRAMA");
    f_manager.escrever_dados(mic1.memoria);
    f_manager.close_log_file();
}