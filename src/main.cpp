#include <iostream>
#include "include/file_manager.h"
#include "include/mic1.h"

int main() { 
    FileManager f_manager;

    std::vector<bits_32> instrucoes;
    bits_32 dados[8];
    MIC_1 mic1;
    
    try{
        instrucoes = f_manager.ler_microinstrucoes();
        f_manager.ler_dados(dados);
        f_manager.create_log_file();
    }catch(std::string e){
        std::cerr << e << std::endl;
        return -1;
    }

    f_manager.print_log("> Memoria inicial\n");

    for(bits_32 b : dados){
        f_manager.print_log(f_manager.binary_to_string(b) + '\n');
    }

    f_manager.print_log("=====================================================\n");
    f_manager.print_log("Comeco do programa\n");
    f_manager.print_log("=====================================================\n");

    int c = 1;
    for(bits_32 inst : instrucoes){
        f_manager.print_log("Ciclo " + std::to_string(c) + "\n");
        f_manager.print_log("IR = " + f_manager.binary_to_string(inst, 23) + "\n\n");

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
            mic1.read_or_write(inst, dados);
            f_manager.escrever_dados(dados);
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
        
        for(bits_32 b : dados){
            f_manager.print_log(f_manager.binary_to_string(b) + '\n');
        }

        f_manager.print_log("=====================================================\n");

        c++;
    }

    f_manager.print_log("FIM DO PROGRAMA");

    f_manager.close_log_file();
}