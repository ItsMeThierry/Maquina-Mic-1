#include "compiler.h"

Compiler::Compiler(){
}

std::vector<bits_32> Compiler::check_line(std::string line){
    std::vector<bits_32> instrucoes;

    lexic.start();
    syntax.start();

    for(char c : line){
        lexic.transition(c);
    }

    try{
        lexic.end();
        instrucoes = syntax.program(lexic.table);
    } catch(std::string e){
        throw e;
    }
    
    return instrucoes;
}

