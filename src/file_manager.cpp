#include "include/file_manager.h"
#include "include/ula.h"

void read_file(){
    std::ifstream file("files/input.txt");

    if(!file.is_open()){
        std::cerr << "[Erro] Nao foi possivel abrir o input.txt" << std::endl;
        return;
    }

    std::string string;
    ULA ula;

    while (std::getline(file, string)) {
        if(string.length() > 6){ // Temporariamente vai ficar 6
            std::cerr << "[Erro] Numero de bits maior que o esperado" << std::endl;
            break;
        }

        ula.executa(string_to_byte(string));
        std::cout << std::endl;
    }

    file.close();
}

byte string_to_byte(std::string string){
    byte result = 0;

    for(int i = 0; i < 6; i++){ // Temporariamente vai ficar 6
        result <<= 1;

        if(string[i] == '1'){
            result |= 1;
        }
    }

    return result;
}