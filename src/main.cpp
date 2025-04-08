#include <iostream>
#include "file_manager.h"
#include "mic1.h"
#include "compiler.h"
#include "binary_manipulator.h"

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

std::string decode_op(bits_32 inst){
    bits_8 op = 0b00110000 & (inst >> 15);

    switch(op){
        case 0b00000000:
            return "AND";
        case 0b00010000:
            return "OR";
        case 0b00100000:
            return "NOT";
        case 0b00110000:
            return "+";
        default:
            return "X";
    }
}

int main() {
    FileManager f_manager;
    Compiler compiler;
    MIC_1 mic1;

    std::vector<bits_32> instrucoes;

    try{
        std::string isa_inst = f_manager.ler_instrucoes();
        instrucoes = compiler.check_line(isa_inst);

        bits_32 dados[8];
        bits_32 registradores[10];

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
        f_manager.print_log("IR = " + binary_to_string(inst, 23) + "\n\n");

        f_manager.print_log("BAR_B : " + decode_b(inst) + '\n');
        f_manager.print_log("BAR_C : " + decode_c(inst) + '\n');
        f_manager.print_log("OP : " + decode_op(inst) + "\n\n");

        f_manager.print_log("> Registradores antes da instrucao\n");
        f_manager.print_log("MAR = " + binary_to_string(mic1.MAR) + "\n");
        f_manager.print_log("MDR = " + binary_to_string(mic1.MDR) + "\n");
        f_manager.print_log("PC = " + binary_to_string(mic1.PC) + "\n");
        f_manager.print_log("MBR = " + binary_to_string(mic1.MBR) + "\n");
        f_manager.print_log("SP = " + binary_to_string(mic1.SP) + "\n");
        f_manager.print_log("LV = " + binary_to_string(mic1.LV) + "\n");
        f_manager.print_log("CPP = " + binary_to_string(mic1.CPP) + "\n");
        f_manager.print_log("TOS = " + binary_to_string(mic1.TOS) + "\n");
        f_manager.print_log("OPC = " + binary_to_string(mic1.OPC) + "\n");
        f_manager.print_log("H = " + binary_to_string(mic1.H) + "\n\n");

        try{
            bits_8 r_w = inst & 0b110000;

            if(r_w == 0b110000){
                mic1.fetch(inst);
            } else{
                mic1.executa_ula(inst);
                mic1.read_or_write(inst);
            }
        }catch(std::string e){
            f_manager.print_log(e + '\n');
            break;
        }   

        f_manager.print_log("> Registradores depois da instrucao\n");
        f_manager.print_log("MAR = " + binary_to_string(mic1.MAR) + "\n");
        f_manager.print_log("MDR = " + binary_to_string(mic1.MDR) + "\n");
        f_manager.print_log("PC = " + binary_to_string(mic1.PC) + "\n");
        f_manager.print_log("MBR = " + binary_to_string(mic1.MBR) + "\n");
        f_manager.print_log("SP = " + binary_to_string(mic1.SP) + "\n");
        f_manager.print_log("LV = " + binary_to_string(mic1.LV) + "\n");
        f_manager.print_log("CPP = " + binary_to_string(mic1.CPP) + "\n");
        f_manager.print_log("TOS = " + binary_to_string(mic1.TOS) + "\n");
        f_manager.print_log("OPC = " + binary_to_string(mic1.OPC) + "\n");
        f_manager.print_log("H = " + binary_to_string(mic1.H) + "\n\n");

        f_manager.print_log("> Memoria depois da instrucao\n");
        
        for(bits_32 b : mic1.memoria){
            f_manager.print_log(binary_to_string(b) + '\n');
        }

        f_manager.print_log("=====================================================\n");

        c++;
    }

    f_manager.print_log("FIM DO PROGRAMA");
    f_manager.close_log_file();
}