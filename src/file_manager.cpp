#include "include/file_manager.h"
#include "include/mic1.h"
#include <string>

void FileManager::read_file(){
    std::ifstream file("files/input.txt");

    if(!file.is_open()){
        std::cerr << "[Erro] Nao foi possivel abrir o input.txt" << std::endl;
        return;
    }

    std::ofstream log("files/log.txt");

    if(!log.is_open()){
        std::cerr << "[Erro] Nao foi possivel criar o log.txt" << std::endl;
        return;
    }

    std::string string;
    MIC_1 mic1;

    log << "Comeco do programa\n";
    log << "============================================================\n";

    int c = 1;

    while (std::getline(file, string)) {
        log << "Ciclo " << c << std::endl;

        if(string.length() != 21){
            log << "[Erro] Numero de bits invalido\n";
            log << "============================================================\n";
            break;
        }

        try{
            log << "IR = " << string << std::endl;

            log << std::endl;

            log << "> Registradores antes da operacao\n";
            log << "MAR = " << binary_to_string(mic1.MAR) << std::endl;
            log << "MDR = " << binary_to_string(mic1.MDR) << std::endl;
            log << "PC = " << binary_to_string(mic1.PC) << std::endl;
            log << "MBR = " << binary_to_string(mic1.MBR) << std::endl;
            log << "SP = " << binary_to_string(mic1.SP) << std::endl;
            log << "LV = " << binary_to_string(mic1.LV) << std::endl;
            log << "CPP = " << binary_to_string(mic1.CPP) << std::endl;
            log << "TOS = " << binary_to_string(mic1.TOS) << std::endl;
            log << "OPC = " << binary_to_string(mic1.OPC) << std::endl;
            log << "H = " << binary_to_string(mic1.H) << std::endl;

            log << std::endl;

            mic1.executa_ula(string_to_binary(string));

            // log << "SAIDA = " << binary_to_string(mic1.saida) << std::endl;
            // log << "SD = " << binary_to_string(mic1.sd) << std::endl;
            // log << "N = " << ((mic1.N) ? 1 : 0) << std::endl;
            // log << "Z = " << ((mic1.Z) ? 1 : 0) << std::endl;
            // log << "VAI_UM = " << ((mic1.vai_um) ? 1 : 0) << std::endl;

            log << std::endl;

            log << "> Registradores depois da operacao\n";
            log << "MAR = " << binary_to_string(mic1.MAR) << std::endl;
            log << "MDR = " << binary_to_string(mic1.MDR) << std::endl;
            log << "PC = " << binary_to_string(mic1.PC) << std::endl;
            log << "MBR = " << binary_to_string(mic1.MBR) << std::endl;
            log << "SP = " << binary_to_string(mic1.SP) << std::endl;
            log << "LV = " << binary_to_string(mic1.LV) << std::endl;
            log << "CPP = " << binary_to_string(mic1.CPP) << std::endl;
            log << "TOS = " << binary_to_string(mic1.TOS) << std::endl;
            log << "OPC = " << binary_to_string(mic1.OPC) << std::endl;
            log << "H = " << binary_to_string(mic1.H) << std::endl;

            log << "============================================================\n";
        }catch(std::string e){
            log << "PC = " << int(mic1.PC) << std::endl;
            log << "IR = " << binary_to_string(mic1.IR) << std::endl;
            log << e;
        }
        
        c++;
    }

    log << "FIM DO PROGRAMA";

    log.close();
    file.close();
}

bits_32 FileManager::string_to_binary(std::string string){
    bits_32 result = 0;

    for(char c : string){
        result <<= 1;

        if(c == '1'){
            result |= 1;
        }
    }

    return result;
}

std::string FileManager::binary_to_string(byte b){
    std::string out;

    for(int i = 7; i >= 0; i--){
        int bit = (b >> i) & 1;

        if(bit){
            out += '1';
            continue;
        }

        out += '0';
    }

    return out;
}

std::string FileManager::binary_to_string(bits_32 b){
    std::string out;

    for(int i = 31; i >= 0; i--){
        int bit = (b >> i) & 1;

        if(bit){
            out += '1';
            continue;
        }

        out += '0';
    }

    return out;
}