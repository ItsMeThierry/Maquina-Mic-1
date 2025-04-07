#include "include/file_manager.h"

std::vector<bits_32> FileManager::ler_microinstrucoes(){
    std::ifstream file("files/input.txt");

    if(!file.is_open()){
        throw std::string("[Erro] Nao foi possivel abrir o input.txt");
    }

    std::vector<bits_32> inst;
    std::string string;

    int c = 1;

    while (std::getline(file, string)) {
        if(string.length() != 23){
            throw "[Erro] Numero de bits invalido na linha " + std::to_string(c);
        }

        inst.push_back(string_to_binary(string));
    
        c++;
    }

    file.close();

    return inst;
}

void FileManager::create_log_file(){
    log.open("files/log.txt");

    if(!log.is_open()){
        throw std::string("[Erro] Nao foi possivel criar o log.txt");
    }
}

void FileManager::close_log_file(){
    log.close();
}

void FileManager::print_log(std::string line){
    log << line;
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

std::string FileManager::binary_to_string(bits_8 b){
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

std::string FileManager::binary_to_string(bits_32 b, int size){
    std::string out;

    for(int i = size-1; i >= 0; i--){
        int bit = (b >> i) & 1;

        if(bit){
            out += '1';
            continue;
        }

        out += '0';
    }

    return out;
}