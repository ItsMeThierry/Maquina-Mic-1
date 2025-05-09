#include "file_manager.h"

std::string FileManager::ler_instrucoes(){
    std::ifstream file("files/input.txt");

    if(!file.is_open()){
        throw std::string("[Erro] Nao foi possivel abrir o input.txt");
    }

    std::string string;
    std::string aux;

    while(!file.eof()){
        file >> aux;
        string += aux;
        string += '\n';
    }

    file.close();

    return string;
}

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
            throw "[Erro] Em input.txt, o numero de bits esta invalido na linha " + std::to_string(c);
        }

        inst.push_back(string_to_binary(string));
    
        c++;
    }

    file.close();

    return inst;
}

void FileManager::ler_registradores(bits_32* dados){
    std::ifstream file("files/registradores.txt");

    if(!file.is_open()){
        throw std::string("[Erro] Nao foi possivel abrir o registradores.txt");
    }

    std::string string;

    for(int i = 0; i < 10; i++){
        if(!getline(file, string)){
            throw std::string("[Erro] Registradores insuficientes!");
        }

        size_t pos = string.find('=');

        if(pos == std::string::npos){
            throw std::string("[Erro] Registradores invalidos!");
        }

        std::string input = string.substr(pos + 2);

        if(input.length() != ((i == 3) ? 8 : 32)){
            throw "[Erro] Em registradores.txt, o numero de bits esta invalido na linha " + std::to_string(i+1);
        }
        
        dados[i] = string_to_binary(input);
    }

}

void FileManager::ler_dados(bits_32* dados){
    std::ifstream file("files/dados.txt");

    if(!file.is_open()){
        throw std::string("[Erro] Nao foi possivel abrir o dados.txt");
    }

    std::string string;
    int c = 0;

    while (std::getline(file, string)) {
        if(c == 8){
            throw std::string("[Erro] Ha mais dados do que o necessario no arquivo dados.txt");
        }

        if(string.length() != 32){
            throw "[Erro] Em dados.txt, o numero de bits esta invalido na linha " + std::to_string(c+1);
        }

        dados[c] = string_to_binary(string);
    
        c++;
    }

    file.close();
}

void FileManager::escrever_dados(bits_32* dados){
    std::ofstream file("files/dados.txt");

    if(!file.is_open()){
        throw std::string("[Erro] Nao foi possivel abrir o dados.txt");
    }

    for(int i = 0; i < 8; i++){
        file << binary_to_string(dados[i]) << std::endl;
    }

    file.close();
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