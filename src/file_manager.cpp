#include "file_manager.h"

void FileManager::read_file(){
    std::ifstream file("files/input.txt");

    if(!file.is_open()){
        std::cerr << "[Erro] Nao foi possivel abrir o input.txt" << std::endl;
        return;
    }

    std::string string;

    while (std::getline(file, string)) {
        try{
            interpreter.check_line(string);
        }catch(...){
            break;
        }
    }

    file.close();
}

byte FileManager::string_to_byte(std::string string){
    byte result = 0;

    for(int i = 0; i < 6; i++){ // Temporariamente vai ficar 6
        result <<= 1;

        if(string[i] == '1'){
            result |= 1;
        }
    }

    return result;
}