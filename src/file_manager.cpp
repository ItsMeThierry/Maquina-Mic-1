#include "include/file_manager.h"
#include "include/ula.h"

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
    ULA ula;

    log << "Comeco do programa\n";
    log << "============================================================\n";

    int c = 1;

    while (std::getline(file, string)) {
        log << "Ciclo " << c << std::endl;

        if(string.length() != 8){
            log << "[Erro] Numero de bits invalido\n";
            log << "============================================================\n";
            break;
        }

        ula.executa(string_to_binary(string));
        
        log << "PC = " << int(ula.PC) << std::endl;
        log << "IR = " << binary_to_string(ula.IR) << std::endl;
        log << "A = " << binary_to_string(ula.H) << std::endl;
        log << "B = " << binary_to_string(ula.OPC) << std::endl;
        log << "SAIDA = " << binary_to_string(ula.saida) << std::endl;
        log << "N = " << ((ula.N) ? 1 : 0) << std::endl;
        log << "Z = " << ((ula.Z) ? 1 : 0) << std::endl;
        log << "VAI_UM = " << ((ula.vai_um) ? 1 : 0) << std::endl;

        log << "============================================================\n";
        c++;
    }

    log << "FIM DO PROGRAMA";

    log.close();
    file.close();
}

bits_32 FileManager::string_to_binary(std::string string){
    bits_32 result = 0;

    for(int i = 0; i < 8; i++){
        result <<= 1;

        if(string[i] == '1'){
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