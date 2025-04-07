#include "syntax.h"

std::vector<bits_32> Syntax::program(std::vector<token> &table){
    table_size = table.size();
    this->table = &table;

    try{
        execute();
    } catch(std::string e){
        throw e;
    }

    if(i < table_size){
        throw "[ERRO] Sintaxe invalida no token " + table[i].content;
    }
    
    return binaries;
}

void Syntax::execute(){
    if(get_current_token(i).content == "BIPUSH"){
        i++;

        if(get_current_token(i).classifier != "BYTE"){
            throw std::string("[ERRO] Nao ha um byte apos o BIPUSH!");
        }

        std::cout << "0x10" << std::endl;
        i++;
        execute();
    }

    if(get_current_token(i).content == "DUP"){
        binaries.push_back(0b00110101000001001000100); // MAR = SP = SP+1;
        binaries.push_back(0b00010100000000010100111); // MDR = TOS; wr
        i++;
        execute();
    }

    if(get_current_token(i).content == "ILOAD"){
        i++;
        
        if(get_current_token(i).classifier != "NUMBER"){
            throw std::string("[ERRO] Nao ha um numero apos o ILOAD!");
        }

        // binaries.push_back(0b00000000000000000000000000000000);
        i++;
        execute();
    }
}

token Syntax::get_current_token(int i){
    if(i < table_size){
        return (*table)[i];
    }

    token t;
    t.classifier = "NULL";
    t.content = "NULL";
    return t;
}

void Syntax::start(){
    i = 0;
    table_size = 0;
    table = nullptr;
}