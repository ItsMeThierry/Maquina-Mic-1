#include "interpreter.h"

Interpreter::Interpreter(){
    l = 0;
}

void Interpreter::check_line(std::string line){
    l++;

    lexic.start();
    syntax.start();

    for(char c : line){
        lexic.transition(c);
    }

    try{
        lexic.end();
        syntax.program(lexic.table);
    } catch(std::string e){
        std::cout << "Linha " << l << ": ";
        std::cout << e << std::endl;
        throw -1;
    }
    
}

