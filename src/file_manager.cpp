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

        if(string.length() > 8){
            log << "[Erro] Numero de bits maior que o esperado\n";
            log << "============================================================\n";
            break;
        }

        ula.executa(string_to_byte(string));
        
        log << "PC = " << int(ula.PC) << std::endl;
        log << "IR = " << byte_to_string(ula.IR) << std::endl;
        log << "A = " << byte_to_string(ula.A) << std::endl;
        log << "B = " << byte_to_string(ula.B) << std::endl;
        log << "INVA = " << byte_to_string(ula.INVA) << std::endl;
        log << "INC = " << byte_to_string(ula.INC) << std::endl;
        log << "SAIDA = " << byte_to_string(ula.saida) << std::endl;
        log << "VAI_UM = " << byte_to_string(ula.vai_um) << std::endl;

        log << "============================================================\n";
        c++;
    }

    log << "FIM DO PROGRAMA";

    log.close();
    file.close();
}

byte FileManager::string_to_byte(std::string string){
    byte result = 0;

    for(int i = 0; i < 8; i++){
        result <<= 1;

        if(string[i] == '1'){
            result |= 1;
        }
    }

    return result;
}

std::string FileManager::byte_to_string(byte b){
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